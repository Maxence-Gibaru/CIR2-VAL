#include "MetroLine.h"

// Constructor for MetroLine
MetroLine::MetroLine(int lineId, const std::vector<std::tuple<std::string, int, double, bool>> &terminusData,
                     const std::vector<std::tuple<std::string, int, std::tuple<int, int>, bool, std::tuple<double, double>, double>> &stationData,
                     int trainNumber) : lineId(lineId) {

    // Create the terminus
    for (const auto &data: terminusData) {
        Termini.emplace_back(std::get<0>(data), std::get<1>(data), std::get<2>(data), std::get<3>(data));
    }

    // Create the stations
    for (const auto &data: stationData) {
        Stations.emplace_back(std::get<0>(data), std::get<1>(data), std::get<2>(data), std::get<3>(data),
                              std::get<4>(data), std::get<5>(data));
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

std::vector<Train> MetroLine::getTrains() {
    return this->Trains;
}

int MetroLine::getLineId() {
    return this->lineId;
}

// Manages the line
void MetroLine::manageLine(SharedData &sharedData, std::mutex &mtx, bool &stopWorking, Heure &temps) {
    while (!stopWorking) {
        for (auto &train: Trains) {
            if (PRINT) {
                mtx.lock(); // Locks mutex to print train details
                /* PRINT TRAIN'S DETAILS */
                train.print(); // Prints details of the train
                /* ===================== */
                mtx.unlock(); // Unlocks mutex after printing
            }

            sharedData.heure = temps.getTime(); // Updates shared data with current time

            ManageTime(train, temps, getLineId()); // Manages time for the train and related stations


            updateTrainState(Trains, train, Stations, temps); // Updates train state based on conditions
            sharedData.isOpen = isOpen; // Updates shared data with station status
            ; // Updates shared data with train information
            if (getLineId() == 0) {
                sharedData.Trains1 = Trains;
                sharedData.Stations1 = Stations;
            } else {
                sharedData.Trains2 = Trains;
                sharedData.Stations2 = Stations;
            }

            updateTrainMove(train); // Updates train movement based on conditions
            std::this_thread::sleep_for(std::chrono::milliseconds(1)); // Pauses thread execution for a short time
        }
    }
}

void MetroLine::setTrains(std::vector<Train> &newTrains) {
    this->Trains = newTrains;
}

std::vector<Station> MetroLine::getStations() {
    return this->Stations;
}

void MetroLine::setStations(std::vector<Station> &newStations) {
    this->Stations = newStations;
}


