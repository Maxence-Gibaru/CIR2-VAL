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
bool allPassengersEmpty(const std::vector<Station> &Stations) {
    for (const auto &station : Stations) {
        if (station.getPassengers(0) != 0) {
            return false; // S'il y a des passagers dans une station, retourne faux
        }
        if (station.getPassengers(1) != 0) {
            // print le nombre de personne dans la station
            return false;
        }
    }
    return true;
}



bool isOpen = true;

void updateTrainState(Train &train, std::vector<Station> &Stations, Heure &temps) {

    if (temps.getHeures() == 1 && temps.getMinutes() == 0 && temps.getSecondes() == 0 && temps.getMillisecondes() == 0 && temps.getMicrosecondes() == 0) {
        std::cout << "On ferme les stations et on les vides" << std::endl;
        isOpen = false;
    }

    // si il est 07:00:00:000:000
    if (temps.getHeures() == 7 && temps.getMinutes() == 0 && temps.getSecondes() == 0 && temps.getMillisecondes() == 0 && temps.getMicrosecondes() == 0) {
        isOpen = true;
    }

    if (train.trainStationArrived() && round(train.getNextStation()->getCoordX(train.getTerminus()->getDirection())) != round(train.getTerminus()->getCoordT())) {
        train.addPassengers();
        train.reducePassengers();
        train.setNextStation();
        train.reducePassengers();
        train.updateTotalCoordX();
        train.setCoordX(0);
        train.setTime(0.0);


        //allPassengersEmpty


        if (isOpen) {
            train.getNextStation()->addPassengers(train.getTerminus()->getDirection());
        }

    }
    // ajouter allPassengersEmpty(Stations)
    if (train.trainArrived()) {
        train.swapTerminus();
        setStation(Stations, train, 0);
        train.emptyPassengers();
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

void ManageTime(Heure &temps, std::vector<Station> &Stations) {
    temps.incrementerTemps(REFRESH);
    /* PRINT TIME */
        //temps.afficherHeure();
    /* ========== */
}

void manageSubway(SharedData &sharedData, Train &train, std::vector<Train> &Trains, std::vector<Station> &Stations,
                 std::mutex &mtx_, bool &stop_working, Heure &temps) {

    while (!stop_working) {
        mtx_.lock();
        /* PRINT TRAIN'S DETAILS */
            //train.print();
        /* ===================== */
        mtx_.unlock();

        ManageTime(temps,Stations);
        updateTrainState(train, Stations, temps);

        sharedData.Trains = &Trains;
        sharedData.Stations = Stations;
        updateTrainMove(train, sharedData);
        std::this_thread::sleep_for( 0.01s);
    }
}

