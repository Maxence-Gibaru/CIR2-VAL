#include <iostream>
#include <vector>
#include <tuple>
#include <random>
#include "Train.h"

#ifndef CIR2_VAL_DATA_H
#define CIR2_VAL_DATA_H

// Moteur de nombres aléatoires et distribution
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dis(1, 25); // Pour des nombres entre 1 et 15, par exemple

// Implementation of Terminus
std::vector<std::tuple<std::string, int, double, bool>> dataTerminusLine1 = {
        {"CHU-Eurasante", 0, DISTANCE_TOT, 0},
        {"4 Cantons",     0, DISTANCE_TOT, 1}
};

// Implementation of Terminus
std::vector<std::tuple<std::string, int, double, bool>> dataTerminusLine2 = {
        {"Lomme St Philibert",  0, DISTANCE_TOT, 0},
        {"Tourcoing C.H. Dron", 0, DISTANCE_TOT, 1}
};

// Implementation of Station (name, id, (x, y), isTerminus, (distanceToNext, distanceToPrevious), speed) line 1
std::vector<std::tuple<std::string, std::tuple<int, int>, bool, std::tuple<double, double>, double>> dataStationsLine1 = {
        {"RESERVE",               {0,        0},        false, {0,                    DISTANCE_TOT}, 1},
        {"Terminus CHU",          {dis(gen), 0},        true,  {DISTANCE_TOT - 12000, 12000},        1},
        {"Porte des Postes",      {dis(gen), dis(gen)}, false, {DISTANCE_TOT -
                                                                11000,                11000},        3},
        {"Wazemmes",              {dis(gen), dis(gen)}, false, {DISTANCE_TOT -
                                                                10000,                10000},        2.5},
        {"Republique Beaux-Arts", {dis(gen), dis(gen)}, false, {DISTANCE_TOT -
                                                                8700,                 8700},         3.5},
        {"Rihour",                {dis(gen), dis(gen)}, false, {DISTANCE_TOT -
                                                                7500,                 7500},         2.5},
        {"Lille FLandres",        {dis(gen), dis(gen)}, false, {DISTANCE_TOT -
                                                                6400,                 6400},         5},
        {"Fives",                 {dis(gen), dis(gen)}, false, {DISTANCE_TOT -
                                                                4800,                 4800},         2.5},
        {"Pont de Bois",          {dis(gen), dis(gen)}, false, {DISTANCE_TOT -
                                                                2100,                 2100},         2},
        {"Terminus CANTONS",      {0,        dis(gen)}, true,  {DISTANCE_TOT - 1000,  1000},         1},
        {"RESERVE",               {0,        0},        false, {DISTANCE_TOT,         0},            1}

};

// Implementation of Station (name, id, (x, y), isTerminus, (distanceToNext, distanceToPrevious), speed) line 2
std::vector<std::tuple<std::string, std::tuple<int, int>, bool, std::tuple<double, double>, double>> dataStationsLine2 = {
        {"RESERVE",               {0,        0},        false, {0,                    DISTANCE_TOT}, 1},
        {"Terminus St Philibert", {dis(gen), 0},        true,  {DISTANCE_TOT - 12000, 12000},        1},
        {"Port de Lille",         {dis(gen), dis(gen)}, false, {DISTANCE_TOT -
                                                                10500,                10500},        3},
        {"Cormontaigne",          {dis(gen), dis(gen)}, false, {DISTANCE_TOT -
                                                                9200,                 9200},         2.5},
        {"Porte des Postes",      {dis(gen), dis(gen)}, false, {DISTANCE_TOT -
                                                                8400,                 8400},         3},
        {"Gare Lille Flandres",   {dis(gen), dis(gen)}, false, {DISTANCE_TOT -
                                                                6800,                 6800},         2.5},
        {"Gare Lille Europe",     {dis(gen), dis(gen)}, false, {DISTANCE_TOT -
                                                                5400,                 5400},         5},
        {"Les Pres",              {dis(gen), dis(gen)}, false, {DISTANCE_TOT -
                                                                4300,                 4300},         2.5},
        {"Roubaix Grand Place",   {dis(gen), dis(gen)}, false, {DISTANCE_TOT -
                                                                2400,                 2400},         2},
        {"Terminus C.H. Dron",    {0,        dis(gen)}, true,  {DISTANCE_TOT - 1500,  1500},         1},
        {"RESERVE",               {0,        0},        false, {DISTANCE_TOT,         0},            1}

};

#endif //CIR2_VAL_DATA_H
