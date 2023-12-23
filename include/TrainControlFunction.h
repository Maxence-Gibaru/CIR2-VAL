#define CIR2_VAL_TRAINCONTROLFUNCTION_H

#include <vector>
#include <iostream>
#include "Train.h"
#include <thread>
#include "Station.h"
#include <chrono>
#include <vector>
#include <cmath>
#include "Terminus.h"
#include <string>
#include <ctime>
#include "TrainGraphics.h"
#include "Heure.h"

using namespace std::chrono_literals;


/**
 * @brief Trouve le voisin d'un train
 * @param myList : liste des trains
 * @return 0 si bien récupéré
*/
void setVoisinList(std::vector<Train> &Trains);


void setStation(std::vector<Station> &Stations, Train &train, bool first);

void setLastStation(std::vector<Station> &Stations, std::vector<Train> &myList);

/**
 * @brief Initialise la liste des stations
 * @param Stations : liste des stations
*/
void initNextStation(std::vector<Station> &Stations, Terminus *myTerminus);

/**
 * @brief Initialise la liste des trains
 * @param Trains : liste des trains
 * @param myTerminus : terminus
 * @param n : nombre de trains
*/
void initTrains(std::vector<Train> &Trains, Terminus &myTerminus, int n);

/**
 * @brief Initialise la liste des terminus
 * @param Line : liste des terminus
*/
void initNextTerminus(std::vector<Terminus> &Line);

void manageTrain(SharedData &sharedData, Train &train, std::vector<Train> &Trains, std::vector<Station> &Stations,
                 std::mutex &mtx_, bool &stop_working);

void manageTime(Heure &heureActuelle, SharedData &sharedData, bool &stopping);