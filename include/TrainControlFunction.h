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

/**
 * @brief Trouve le voisin d'un train
 * @param Stations : liste des stations
 * @param train : train
 * @param first : booléen pour savoir si c'est le premier train
 */
void setStation(std::vector<Station> &Stations, Train &train, bool first);

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
void initTrains(std::vector<Train> &Trains, std::vector<Terminus> &Line, int n);

/**
 * @brief Initialise la liste des terminus
 * @param Line : liste des terminus
*/
void initNextTerminus(std::vector<Terminus> &Line);

/**
 * @brief Toute les fonctionnalités des trains
 * @param sharedData : données partagées
 * @param train : train
 * @param Trains : liste des trains
 * @param Stations : liste des stations
 * @param mtx_ : mutex
 * @param stop_working : booléen pour savoir si le train doit s'arrêter
*/
void manageSubway(SharedData &sharedData, Train &train, std::vector<Train> &Trains, std::vector<Station> &Stations,
                  std::mutex &mtx_, bool &stop_working, Heure &temps);

void updateRefresh(double &refresh, double &newValue);