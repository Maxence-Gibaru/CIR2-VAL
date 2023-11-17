//
// Created by Ugo WAREMBOURG on 17/11/2023.
//

#include "../include/Train.h"

#include <vector>

#ifndef CIR2_VAL_TRAINCONTROLFUNCTION_H
#define CIR2_VAL_TRAINCONTROLFUNCTION_H

/**
 * @brief Trouve le voisin d'un train
 * @param myList : liste des trains
 * @return 0 si bien récupéré
*/
int setVoisinList(std::vector<Train> &myList);

#endif //CIR2_VAL_TRAINCONTROLFUNCTION_H
