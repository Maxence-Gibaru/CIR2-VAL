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

void initTrains(std::vector<Train> &Trains, std::vector<Terminus> &Line, int n) {
    for (int i = 1; i <= n; i++) {
        if (i == n) {
            Train myTrain(i, 0.0, 0.0, &Line[0], 0.0, 0.0, 10, false, false);
            Trains.push_back(myTrain);
        } else {
            Train myTrain(i, 0.0, 0.0, &Line[1], 0.0, 0.0, 10, false, false);
            Trains.push_back(myTrain);
        }
    }
}

bool allPassengersEmpty(const std::vector<Station> &Stations) {
    for (const auto &station: Stations) {
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

void updateTrainState(std::vector<Train> &Trains, Train &train, std::vector<Station> &Stations, Heure &temps) {


    if (temps.getHeures() == 7 ) {
        //std::cout << "On ferme les stations et on les vides" << std::endl;
        isOpen = true;
        for(auto &train : Trains) {
            train.setEmergencyStop(0);
        }
    }

    if (temps.getHeures() >= 1 and temps.getHeures() < 7) {
        //std::cout << "On ferme les stations et on les vides" << std::endl;
        isOpen = false;
    }
    


    if (train.trainStationArrived() && round(train.getNextStation()->getCoordX(train.getTerminus()->getDirection())) !=
                                       round(train.getTerminus()->getCoordT())) {
        train.addPassengers();
        train.reducePassengers();
        train.setNextStation();
        train.reducePassengers();
        train.updateTotalCoordX();
        train.setCoordX(0);
        train.setTime(0.0);
        //std::this_thread::sleep_for(REFRESH * 1s);


        if (isOpen && train.getNextStation()->getCoordX(train.getTerminus()->getDirection()) != DISTANCE_TOT) {
            train.getNextStation()->addPassengers(train.getTerminus()->getDirection());
        }

    }

    if (train.trainArrived()) {
        if (allPassengersEmpty(Stations) and !isOpen) {
            train.setEmergencyStop(1);
        }

        train.swapTerminus();
        setStation(Stations, train, 0);
        train.getNextStation()->emptyPassengers(train.getTerminus()->getDirection());
        train.emptyPassengers();
    }
}

void updateTrainMove(Train &train, SharedData &sharedData) {
    if (train.checkSecurityDistance() && !train.getEmergencyStop()) {
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

        // Mise à jour de lastTime pour la prochaine itération

        mtx_.lock();
        /* PRINT TRAIN'S DETAILS */
        //train.print();
        /* ===================== */
        mtx_.unlock();

        sharedData.heure = temps.getTime();

        ManageTime(temps, Stations);
        updateTrainState(Trains, train, Stations, temps);

        sharedData.Trains = &Trains;
        sharedData.Stations = Stations;
        updateTrainMove(train, sharedData);
        std::this_thread::sleep_for(0.001s);
    }
}

