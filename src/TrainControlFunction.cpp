#include "TrainControlFunction.h"
#include "Heure.h"

void setVoisinList(std::vector<Train> &Trains) {
    const int numTrains = Trains.size();
    for (int i = 0; i < numTrains; ++i) {
        if (i == 0) {
            Trains[i].setVoisin(&Trains[numTrains - 1]);
        } else {
            Trains[i].setVoisin(&Trains[i - 1]);
        }
        std::cout << "Train " << Trains[i].getId() << " voisin : " << Trains[i].getVoisin()->getId() << std::endl;
    }
}

void setStation(std::vector<Station> &Stations, Train &train, bool first) {
    if (train.getTerminus()->getDirection()) {
        train.setStation(&Stations[1]);
    } else {
        train.setStation(&Stations[Stations.size() - 2]);
    }
}

void initNextStation(std::vector<Station> &Stations, Terminus *myTerminus) {
    for (int i = 0; i < Stations.size(); i++) {
        if (myTerminus->getDirection()) {
            Stations[i].setNeighbour(&Stations[i + 1]);
            Stations[i].setPreviousNeighbour(&Stations[i - 1]);
        } else {
            Stations[i].setNeighbour(&Stations[i - 1]);
            Stations[i].setPreviousNeighbour(&Stations[i + 1]);
        }
    }
}

void initTrains(std::vector<Train> &Trains, Terminus &myTerminus, int n) {
    for (int i = 1; i <= n; i++) {
        Train myTrain(i, 0.0, 0.0, &myTerminus, 0.0, 0.0, 10, false, false);
        Trains.push_back(myTrain);
    }
}

void updateTrainState(Train &train, std::vector<Station> &Stations) {
    if (train.trainStationArrived() && round(train.getNextStation()->getCoordX(train.getTerminus()->getDirection())) != round(train.getTerminus()->getCoordT())) {
        train.addPassengers();
        train.reducePassengers();
        train.getNextStation()->addPassengers(train.getTerminus()->getDirection());
        train.setNextStation();
        train.updateTotalCoordX();
        train.setCoordX(0);
        train.setTime(0.0);
        std::this_thread::sleep_for(REFRESH * 0.5s);
    }

    if (train.trainArrived()) {
        train.swapTerminus();
        setStation(Stations, train, 0);
        train.setPassengers(-train.getPassengers());
    }
}

void updateTrainMove(Train &train, SharedData &sharedData) {
    if (train.checkSecurityDistance() && !train.getEmergencyStop()) {
        if (train.getTerminus()->getDirection()) {
            train.setCoordY(400);
        } else {
            train.setCoordY(550);
        }
        train.moveX();
    }
}

void manageSubway(SharedData &sharedData, Train &train, std::vector<Train> &Trains, std::vector<Station> &Stations,
                 std::mutex &mtx_, bool &stop_working) {
    Heure temps;
    while (!stop_working) {

        mtx_.lock();
        // A optimiser pour tout print ensemble
        train.print();
        mtx_.unlock();


        updateTrainState(train, Stations);

        temps.incrementerTemps(REFRESH);
        sharedData.Trains = &Trains;
        sharedData.Stations = Stations;
        updateTrainMove(train, sharedData);
        std::this_thread::sleep_for( 0.1s);

    }
}

