#include "MetroLine.h"

// Default constructor
MetroLine::MetroLine() {

}


// Constructor for MetroLine
MetroLine::MetroLine(int lineId, const std::vector<std::tuple<std::string, int, double, bool>> &terminusData,
                     const std::vector<std::tuple<std::string, std::tuple<int, int>, bool, std::tuple<double, double>, double>> &stationData,
                     int trainNumber) : lineId(lineId) {

    // Create the terminus
    for (const auto &data: terminusData) {
        Termini.emplace_back(std::get<0>(data), std::get<1>(data), std::get<2>(data), std::get<3>(data));
    }

    // Create the stations
    for (const auto &data: stationData) {
        Stations.emplace_back(std::get<0>(data), std::get<1>(data), std::get<2>(data), std::get<3>(data),
                              std::get<4>(data));
    }

    // Init the trains
    initTrains(Trains, Termini,
               trainNumber);

    // Set each train's neighbour to each other
    setVoisinList(Trains);

    // Set each station next station to each other
    initNextStation(Stations, &Termini[1]);

    // Initialise the first station of each train
    for (auto &train: Trains) {
        setStation(Stations, train, true);
    }

    //Set the next Terminus of each other
    Termini[1].setNextTerminus(&Termini[0]);
    Termini[0].setNextTerminus(&Termini[1]);
}


std::vector<Train> &MetroLine::getTrains() {
    return Trains;
}


int MetroLine::getLineId() const {
    return this->lineId;
}

// Finds the neighbor of each train in the list
void MetroLine::setVoisinList(std::vector<Train> &Trains) {
    try {
        const int numTrains = Trains.size();
        for (int i = 0; i < numTrains; ++i) {
            if (i == 0) {
                Trains[i].setVoisin(&Trains.at(numTrains - 1)); // Sets neighbor for the first train
            } else {
                Trains[i].setVoisin(&Trains.at(i - 1)); // Sets neighbor for other trains
            }
        }
    } catch (const std::exception &e) {
        std::cerr << "Exception in setVoisinList: " << e.what() << std::endl;
    }
}

// Sets the station for a train based on its direction
void MetroLine::setStation(std::vector<Station> &Stations, Train &train, bool first) {
    try {
        if (train.getTerminus()->getDirection()) {
            train.setStation(&Stations[1]); // Sets station for a train based on direction

        } else {
            train.setStation(&Stations[Stations.size() - 2]); // Sets station for a train based on direction
        }
    } catch (const std::exception &e) {
        std::cerr << "Exception in setStation: " << e.what() << std::endl;
    }
}

// Initializes the next and previous stations for each station
void MetroLine::initNextStation(std::vector<Station> &Stations, Terminus *myTerminus) {
    for (int i = 0; i < Stations.size(); i++) {
        if (myTerminus->getDirection()) {
            Stations[i].setNeighbour(&Stations[i + 1]); // Sets next station in forward direction
            Stations[i].setPreviousNeighbour(&Stations[i - 1]); // Sets previous station in forward direction
        } else {
            Stations[i].setNeighbour(&Stations[i - 1]); // Sets next station in backward direction
            Stations[i].setPreviousNeighbour(&Stations[i + 1]); // Sets previous station in backward direction
        }
    }
}

// Initializes a specified number of trains on the provided Line
void MetroLine::initTrains(std::vector<Train> &Trains, std::vector<Terminus> &Line, int n) {
    for (int i = 1; i <= n; i++) {
        if (i == n) {
            Train myTrain(i, 0.0, 0.0, &Line[0], 0.0, 0.0, 10, false); // Creates the last train on Line[0]
            Trains.push_back(myTrain);
        } else {
            Train myTrain(i, 0.0, 0.0, &Line[1], 0.0, 0.0, 10, false); // Creates the last train on Line[1]
            Trains.push_back(myTrain);
        }
    }
}


// Updates the state of a train based on time and station conditions
void
MetroLine::updateTrainState(std::vector<Train> &Trains, Train &train, std::vector<Station> &Stations, Heure &temps) {
    try {
        // Checks and updates station status based on time
        if (temps.getHeures() == 7 and temps.getMinutes() < 1 and temps.getSecondes() < 1) {
            if (PRINT) {
                std::cout << "On ouvre les stations !" << std::endl;
            }
            isOpen = true; // Updates station status to open

            // Clears emergency stops for all trains
            for (auto &train: Trains) {
                train.isNight = false;
            }
        }

        // Checks and updates station status based on time
        if (temps.getHeures() >= 1 and temps.getHeures() < 7) {
            if (PRINT) {
                std::cout << "On ferme les stations et on les vides" << std::endl;
            }
            isOpen = false; // Updates station status to closed
        }

        // Updates train state based on arrival and passengers at the next station
        if (train.trainStationArrived() &&
            round(train.getNextStation()->getCoordX(train.getTerminus()->getDirection())) !=
            round(train.getTerminus()->getCoordT())) {
            train.setWait();

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

        // Empties passengers at the reserve station
        if (train.getNextStation()->getNom() == "RESERVE") {
            train.emptyPassengers();
        }

        // Handles actions when a train arrives at a reserve
        if (train.trainArrived()) {
            // Activates emergency stop if all stations are empty and it's not open
            if (allPassengersEmpty(Stations) and !isOpen) {
                train.isNight = true;
            }

            train.swapTerminus(); // Swaps terminus for the train
            setStation(Stations, train, false); // Sets station for the train
        }
    } catch (const std::exception &e) {
        std::cerr << "Exception in updateTrainMove: " << e.what() << std::endl;
    }

}


// Updates the movement of a train based on security distance and wait time
void MetroLine::updateTrainMove(Train &train) {

    // Vérifie si le train doit s'arrêter en raison d'une distance de sécurité non respectée
    if (!train.checkSecurityDistance() or train.getEmergencyStop() and train.getSpeed() > 0) {
        train.stopX();
    }

    // Sinon, si le train n'a pas besoin d'attendre, il peut se déplacer
    if (train.getWait() <= 0 and train.checkSecurityDistance() and !train.getEmergencyStop() and moving and
        !train.isNight) {
        train.moveX();

    }

    // Si le train doit encore attendre, décrémentez son temps d'attente
    if (train.getWait() > 0) {
        train.decreaseWait(REFRESH);
    }
}


// Checks if all station passengers are empty
bool MetroLine::allPassengersEmpty(const std::vector<Station> &Stations) {
    for (const auto &station: Stations) {
        if (station.getPassengers(0) != 0) {
            return false; // If any station has non-zero passengers, returns false
        }
        if (station.getPassengers(1) != 0) {
            return false; // If any station has non-zero passengers, returns false
        }
    }
    return true; // If all stations have zero passengers, returns true
}

// Controls the main subway system, manages train actions, and shared data updates

void MetroLine::manageSubway(Train &train, std::vector<Train> &Trains, std::vector<Station> &Stations,
                             std::mutex &mtx_, Heure &temps) {
    if (PRINT) {
        mtx_.lock(); // Locks mutex to print train details
        train.print(); // Prints details of the train
        mtx_.unlock(); // Unlocks mutex after printing
    }

    updateTrainState(Trains, train, Stations, temps); // Updates train state based on conditions
    updateTrainMove(train); // Updates train movement based on conditions

}


// Manages the line
void
MetroLine::manageLine(Train &actualTrain, SharedData &sharedData, std::mutex &mtx, bool &stopWorking, Heure &temps) {
    while (!stopWorking) {
        if (PRINT) {
            mtx.lock(); // Locks mutex to print train details
            /* PRINT TRAIN'S DETAILS */
            actualTrain.print(); // Prints details of the train
            /* ===================== */
            mtx.unlock(); // Unlocks mutex after printing
        }

        manageSubway(actualTrain, Trains, Stations, mtx, temps);

        sharedData.updateData(getLineId(), isOpen, Trains, Stations, temps.getTime());

        std::this_thread::sleep_for(std::chrono::milliseconds(1)); // Pauses thread execution for a short time
    }


}




