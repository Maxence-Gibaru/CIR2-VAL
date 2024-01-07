#include "MetroLine.h"

MetroLine::MetroLine(const std::vector<std::tuple<std::string, int, double, bool>> &terminusData,
                     const std::vector<std::tuple<std::string, int, std::tuple<int, int>, bool, std::tuple<double, double>, double>> &stationData,
                     int trainNumber) {

    // Création des terminus
    for (const auto &data: terminusData) {
        Termini.emplace_back(std::get<0>(data), std::get<1>(data), std::get<2>(data), std::get<3>(data));
    }

    // Création des stations
    for (const auto &data: stationData) {
        Stations.emplace_back(std::get<0>(data), std::get<1>(data), std::get<2>(data), std::get<3>(data),
                              std::get<4>(data), std::get<5>(data));
    }

    // Initialisation des trains
    initTrains(Trains, Termini,
               trainNumber);
}

void MetroLine::manageLine(SharedData &sharedData, std::mutex &mtx, bool &stopWorking, Heure &temps) {
    while (!stopWorking) {
        for (auto& train : Trains) {
            if (PRINT) {
                mtx.lock(); // Locks mutex to print train details
                /* PRINT TRAIN'S DETAILS */
                train.print(); // Prints details of the train
                /* ===================== */
                mtx.unlock(); // Unlocks mutex after printing
            }

            sharedData.heure = temps.getTime(); // Updates shared data with current time
            ManageTime(train, temps, Stations); // Manages time for the train and related stations
            updateTrainState(Trains, train, Stations, temps, sharedData); // Updates train state based on conditions
            sharedData.Trains = &Trains; // Updates shared data with train information
            sharedData.Stations = Stations; // Updates shared data with station information
            updateTrainMove(train); // Updates train movement based on conditions
            std::this_thread::sleep_for(std::chrono::milliseconds(1)); // Pauses thread execution for a short time
        }
    }
}

