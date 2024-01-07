#include "TrainControlFunction.h"

bool isOpen = true;
bool moving = true;

// Finds the neighbor of each train in the list
void setVoisinList(std::vector<Train> &Trains) {
    const int numTrains = Trains.size();
    for (int i = 0; i < numTrains; ++i) {
        if (i == 0) {
            Trains[i].setVoisin(&Trains[numTrains - 1]); // Sets neighbor for the first train
        } else {
            Trains[i].setVoisin(&Trains[i - 1]); // Sets neighbor for other trains
        }
    }
}

// Sets the station for a train based on its direction
void setStation(std::vector<Station> &Stations, Train &train, bool first) {
    if (train.getTerminus()->getDirection()) {
        train.setStation(&Stations[1]); // Sets station for a train based on direction

    } else {
        train.setStation(&Stations[Stations.size() - 2]); // Sets station for a train based on direction
    }
}

// Initializes the next and previous stations for each station
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
            Train myTrain(i, 0.0, 0.0, &Line[0], 0.0, 0.0, 10, false);
            Trains.push_back(myTrain);
        } else {
            Train myTrain(i, 0.0, 0.0, &Line[1], 0.0, 0.0, 10, false);
            Trains.push_back(myTrain);
        }
    }
}

bool allPassengersEmpty(const std::vector<Station> &Stations) {
    for (const auto &station: Stations) {
        if (station.getPassengers(0) != 0) {
            return false;
        }
        if (station.getPassengers(1) != 0) {
            return false;
        }
    }
    return true;
}

// Updates the state of a train based on time and station conditions
void updateTrainState(std::vector<Train> &Trains, Train &train, std::vector<Station> &Stations, Heure &temps) {
    // Checks and updates station status based on time
    if (temps.getHeures() == 7 and temps.getMinutes() < 1 and temps.getSecondes() < 1) {
        if (PRINT) {
            std::cout << "On ouvre les stations !" << std::endl;
        }
        isOpen = true;

        for (auto &train: Trains) {
            std::cout << "SEXE" << std::endl;
            train.setEmergencyStop(0);
        }
    }

    if (temps.getHeures() >= 1 and temps.getHeures() < 7) {
        if (PRINT) {
            std::cout << "On ferme les stations et on les vides" << std::endl;
        }
        isOpen = false;
    }



    // Updates train state based on arrival and passengers at the next station
    if (train.trainStationArrived() && round(train.getNextStation()->getCoordX(train.getTerminus()->getDirection())) !=
                                       round(train.getTerminus()->getCoordT())) {
        train.setWait(
                (train.getPassengers() + train.getNextStation()->getPassengers(train.getTerminus()->getDirection())) /
                2);

        train.addPassengers();
        train.reducePassengers();
        train.setNextStation();
        train.reducePassengers();
        train.updateTotalCoordX();
        train.setCoordX(0);
        train.setTime(0.0);

        // Adds passengers to the next station if it's not a terminus or a reserved station
        if (isOpen and !train.getNextStation()->isTerminus() and train.getNextStation()->getNom() != "RESERVE") {
            train.getNextStation()->addPassengers(train.getTerminus()->getDirection());
        }
    }

    if (train.getNextStation()->getNom() == "RESERVE") {
        train.emptyPassengers();
    }

    if (train.trainArrived()) {
        if (allPassengersEmpty(Stations) and !isOpen) {
            train.setEmergencyStop(true);
        }

        train.swapTerminus();
        setStation(Stations, train, false);
    }


}

// Updates the movement of a train based on security distance and wait time
void updateTrainMove(Train &train) {
    /*
        if (!train.checkSecurityDistance() || train.getEmergencyStop()) {
            train.stopX();
        }
    */

    if (train.checkSecurityDistance() and moving and !train.getEmergencyStop() and train.getWait() <= 0) {
        train.moveX();
    }
}

void ManageTime(Train &train, Heure &temps, std::vector<Station> &Stations) {
    if (train.getId() == 1) {
        temps.incrementerTemps(REFRESH);
    }

    if (train.getWait() > 0) {
        train.decreaseWait(REFRESH);
    }

    if (PRINT) {
        temps.afficherHeure(); // Prints the current time
    }
}


// Controls the main subway system, manages train actions, and shared data updates
/*
void manageSubway(SharedData &sharedData, Train &train, std::vector<Train> &Trains, std::vector<Station> &Stations,
                  std::mutex &mtx_, bool &stop_working, Heure &temps) {
    while (!stop_working) {

        if (PRINT) {
            mtx_.lock(); // Locks mutex to print train details
            train.print(); // Prints details of the train
            mtx_.unlock(); // Unlocks mutex after printing
        }

        sharedData.heure = temps.getTime(); // Updates shared data with current time
        ManageTime(train, temps, Stations); // Manages time for the train and related stations
        updateTrainState(Trains, train, Stations, temps, sharedData); // Updates train state based on conditions
        sharedData.Trains = &Trains; // Updates shared data with train information
        sharedData.Stations = Stations; // Updates shared data with station information
        updateTrainMove(train); // Updates train movement based on conditions
        std::this_thread::sleep_for(0.001s); // Pauses thread execution for a short time
    }
}*/

