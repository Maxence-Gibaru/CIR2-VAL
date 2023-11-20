#include "Train.h"
#include "Station.h"

#include <vector>

#ifndef CIR2_VAL_TRAINCONTROLFUNCTION_H
#define CIR2_VAL_TRAINCONTROLFUNCTION_H

/**
 * @brief Trouve le voisin d'un train
 * @param myList : liste des trains
 * @return 0 si bien récupéré
*/
void setVoisinList(std::vector<Train> &myList);

void setNearestStation(std::vector<Station> &Stations, std::vector<Train> &myList);

#endif //CIR2_VAL_TRAINCONTROLFUNCTION_H
