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


std::vector<Train>& MetroLine::getTrains() {
    return Trains;
}


int MetroLine::getLineId() const {
    return this->lineId;
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




