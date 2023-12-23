#include "TrainControlFunction.h"
#include "Heure.h"

void setVoisinList(std::vector<Train> &Trains) {
    for (int i = 0; i < Trains.size(); ++i) {
        if (i == 0) {
            Trains[i].setVoisin(&Trains[Trains.size() - 1]);
        } else {
            Trains[i].setVoisin(&Trains[i - 1]);
        }
    }
    for (const auto &i: Trains) {
        std::cout << "Train " << i.getId() << " voisin : " << i.getVoisin()->getId() << std::endl;
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

void manageTrain(SharedData &sharedData, Train &train, std::vector<Train> &Trains, std::vector<Station> &Stations,
                 std::mutex &mtx_, bool &stop_working) {
    Heure temps;
    while (!stop_working) {

        /* ===== DETAILS ===== */

        mtx_.lock();
        train.print();
        temps.afficherHeure();
        mtx_.unlock();

        /* ===== MANAGE ===== */
        temps.incrementerTemps(REFRESH);
        //  !!! put everything in a single function
        if (train.trainStationArrived() and
            round(train.getNextStation()->getCoordX(train.getTerminus()->getDirection())) !=
            round(train.getTerminus()->getCoordT())) {
            train.addPassengers();
            train.reducePassengers();
            train.getNextStation()->addPassengers(train.getTerminus()->getDirection());
            train.setNextStation();
            train.updateTotalCoordX();
            // make a reset function
            train.setCoordX(0);
            train.setTime(0.0);
            std::this_thread::sleep_for(REFRESH * 0.5s);
        }

        // When a train arrive, it swaps to another terminus in the other direction
        if (train.trainArrived()) {
            train.swapTerminus();
            setStation(Stations, train, 0);
            train.setPassengers(-train.getPassengers());
        }

        /* ===== MOVE ===== */
        sharedData.Trains = &Trains;
        sharedData.Stations = Stations;

        if (train.checkSecurityDistance() and !train.getEmergencyStop()) {
            // graphics data
            if (train.getTerminus()->getDirection()) {
                train.setCoordY(400);
            } else {
                train.setCoordY(550);

            }
            train.moveX();
        }



/*        if(!train.checkSecurityDistance() and train.getSpeed() != 0  and train.getId() != 1) {

            train.stopX();
        }
*/




        // delay between threads
        std::this_thread::sleep_for( 0.1s);

    }
}

