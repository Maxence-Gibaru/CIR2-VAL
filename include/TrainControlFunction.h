#ifndef TRAINCONTROLFUNCTION_H

#define TRAINCONTROLFUNCTION_H

#include <vector>
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <cmath>
#include <string>
#include <ctime>

#include "Train.h"
#include "Station.h"
#include "Terminus.h"
#include "TrainGraphics.h"
#include "Heure.h"

using namespace std::chrono_literals;


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
 * @brief Manages all functionalities of the trains
 * @param sharedData: shared data
 * @param train: train
 * @param Trains: list of trains
 * @param Stations: list of stations
 * @param mtx_: mutex
 * @param stop_working: boolean to know if the train should stop
 */
void manageSubway(SharedData &sharedData, Train &train, std::vector<Train> &Trains, std::vector<Station> &Stations,
                  std::mutex &mtx_, bool &stop_working, Heure &temps);


void updateTrainState(std::vector<Train> &Trains, Train &train, std::vector<Station> &Stations, Heure &temps,
                      SharedData &sharedData);

void updateTrainMove(Train &train);

/**
 * @brief Function that manages the passing time
 * @param train: train
 * @param temps: time variable from the Heure class
 * @param Stations: list of stations
 */
void ManageTime(Train &train, Heure &temps, std::vector<Station> &Stations);

#endif // TRAINCONTROLFUNCTION_H
