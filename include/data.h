#include <iostream>
#include <vector>
#include <tuple>
#include "Train.h"



#ifndef CIR2_VAL_DATA_H
#define CIR2_VAL_DATA_H


// Implementation of Terminus
std::vector<std::tuple<std::string, int, double, bool>> dataTerminus = {
        {"CHU-Eurasanté", 0, DISTANCE_TOT, 0},
        {"4 Cantons",     0, DISTANCE_TOT, 1}
};

std::vector<std::tuple<std::string, int, std::tuple<int, int>, bool, std::tuple<double, double>, double>> dataStations = {
        {"RESERVE",                          1, {0,           0},  false, {0,                    DISTANCE_TOT}, 1},
        {"Terminus CHU",                     2, {rand() % 15,           0},  true, {DISTANCE_TOT - 12000, 12000},        1},
        {"Porte des Postes",                 3, {rand() % 15, rand() %
                                                              15}, false, {DISTANCE_TOT -
                                                                           11000,                11000},        3},
        {"Wazemmes",                         4, {rand() % 15, rand() %
                                                              15}, false, {DISTANCE_TOT -
                                                                           10000,                10000},        2.5},
        {"Gambetta",                         5, {rand() % 15, rand() %
                                                              15}, false, {DISTANCE_TOT -
                                                                           9200,                 9200},         3},
        {"République Beaux-Arts",            6, {rand() % 15, rand() %
                                                              15}, false, {DISTANCE_TOT -
                                                                           8700,                 8700},         3.5},
        {"Rihour",                           7, {rand() % 15, rand() %
                                                              15}, false, {DISTANCE_TOT -
                                                                           7500,                 7500},         2.5},
        {"Lille FLandres",                   8, {rand() % 15, rand() %
                                                              15}, false, {DISTANCE_TOT -
                                                                           6400,                 6400},         5},
        {"Fives",                            9, {rand() % 15, rand() %
                                                              15}, false, {DISTANCE_TOT -
                                                                           4800,                 4800},         2.5},
        {"Pont de Bois",                     10, {rand() % 15, rand() %
                                                              15}, false, {DISTANCE_TOT -
                                                                           2100,                 2100},         2},
        {"Terminus CANTONS",                 11, {0,           rand() % 15},  true, {DISTANCE_TOT - 1000,   1000},          1},
        {"RESERVE",                          12, {0,           0},  false, {DISTANCE_TOT, 0},                    1}

};
#endif //CIR2_VAL_DATA_H
