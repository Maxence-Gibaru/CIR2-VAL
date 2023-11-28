#include <vector>

#include "Train.h"
#include "Station.h"

#ifndef CIR2_VAL_TRAINCONTROLFUNCTION_H
#define CIR2_VAL_TRAINCONTROLFUNCTION_H

/**
 * @brief Trouve le voisin d'un train
 * @param myList : liste des trains
 * @return 0 si bien récupéré
*/
void setVoisinList(std::vector<Train> &Trains);


void setStation(std::vector<Station> &Stations, std::vector<Train> &myList, bool first);

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

#endif //CIR2_VAL_TRAINCONTROLFUNCTION_H
