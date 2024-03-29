#ifndef CIR2_VAL_METROLINE_H
#define CIR2_VAL_METROLINE_H

#include <vector>
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <cmath>
#include <string>
#include <ctime>
#include "Terminus.h"
#include "Train.h"
#include "Station.h"
#include "TrainGraphics.h"
#include "Heure.h"



class MetroLine {
private:
    int lineId;
    std::vector<Train> Trains;
    std::vector<Station> Stations;
    std::vector<Terminus> Termini;
public:

    /**
     * @brief Constructor of MetroLine class
    */
    MetroLine();

    /**
     * @brief Constructor of MetroLine class
     * @param lineId : id of the line
     * @param terminusData : data of the terminus
     * @param stationData : data of the stations
     * @param trainNumber : number of trains
     */
    MetroLine(int lineId, const std::vector<std::tuple<std::string, int, double, bool>> &terminusData,
              const std::vector<std::tuple<std::string,
                      std::tuple<int, int>, bool, std::tuple<double, double>, double>>

              &stationData,
              int trainNumber
    );

    /**
     * @brief Get the id of the line
     * @return int : id of the line
     */
    int getLineId() const;

    std::vector<Train> &getTrains();


    /**
     * @brief Finds the neighbor of a train
     * @param Trains: list of trains
     * @return 0 if retrieved successfully
    */
    void setVoisinList(std::vector<Train> &Trains);

    /**
     * @brief Finds the neighbor of a train
     * @param Stations: list of stations
     * @param train: train
     * @param first: boolean to know if it's the first train
     */
    void setStation(std::vector<Station> &Stations, Train &train, bool first);

    /**
     * @brief Initializes the list of stations
     * @param Stations: list of stations
     */
    void initNextStation(std::vector<Station> &Stations, Terminus *myTerminus);

    /**
     * @brief Initializes the list of trains
     * @param Trains: list of trains
     * @param Line: terminus line
     * @param n: number of trains
     */
    void initTrains(std::vector<Train> &Trains, std::vector<Terminus> &Line, int n);

    /**
     * @biref Function that updates the state of the train
     * @param Trains : list of trains
     * @param train : train
     * @param Stations : list of stations
     * @param temps : time variable from the Heure class
     */
    void updateTrainState(std::vector<Train> &Trains, Train &train, std::vector<Station> &Stations, Heure &temps);

    /**
     * @brief Function that updates the move of the train
     * @param train : train
     */
    static void updateTrainMove(Train &train);

    bool allPassengersEmpty(const std::vector<Station> &Stations);

    /**
     * @brief Manages all functionalities of the trains
     * @param sharedData: shared data
     * @param train: train
     * @param Trains: list of trains
     * @param Stations: list of stations
     * @param mtx_: mutex
     * @param stop_working: boolean to know if the train should stop
     */
    void manageSubway(Train &train, std::vector<Train> &Trains, std::vector<Station> &Stations,
                      std::mutex &mtx_, Heure &temps);


    /**
     * @breif Manage the line (trains, stations, terminus)
     * @param sharedData : data shared between threads
     * @param mtx : mutex
     * @param stopWorking : boolean to stop the thread
     * @param temps : time
     */
    void manageLine(Train &actualTrain, SharedData &sharedData, std::mutex &mtx, bool &stopWorking, Heure &temps);

    /**
     * @brief Set the trains of the line
     * @param newTrains : new trains
     */
    void setTrains(std::vector<Train> &newTrains);

    std::vector<Station> getStations();

    /**
     * @brief Set the stations of the line
     * @param newStations : new stations
     */
    void setStations(std::vector<Station> &newStations);

};

#endif //CIR2_VAL_METROLINE_H
