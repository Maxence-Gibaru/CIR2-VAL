#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <cmath>
#include "Terminus.h"
#include "Train.h"
#include "Station.h"
#include "TrainControlFunction.h"
#include "TrainGraphics.h"
#include <string>
#include <ctime>


#define TRAIN_NUMBER 1
#define MAX_PASSENGERS_STATION 50

/*
 * TODO
 * 🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆
 * - [ ] Implémenter les heures de la journée
 * - [ ] Optimisation et cleanage du code
 * - [ ] gérer freinage en fonction de distance de sécurité -> méthode stop
 * - [ ] gérer le problème de boucle
 * - [ ] faire une interface pour gérer les paramètres et ne plus avoir à le faire dans le code
 * 🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆🚆
*/

int main() {
    Heure actualHour;
    SharedData sharedData;
    bool stop_working = false; // gérer la boucle while en fonction du temps

    //sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Train Simulator");

    //std::thread renderThread(renderVisuals, std::ref(window), std::ref(sharedData));




    // Vector definition
    std::mutex mtx_;
    std::vector<std::thread> threads;
    std::vector<Train> Trains;
    std::vector<Station> Stations;
    std::vector<Terminus> Line;


    // Implementation of Terminus
    std::vector<std::tuple<std::string, int, double, bool>> dataTerminus = {
            {"CHU-Eurasanté", 0, DISTANCE_TOT, 0},
            {"4 Cantons",     0, DISTANCE_TOT, 1}
    };

    Line.reserve(dataTerminus.size());
    for (auto &data: dataTerminus) {
        Line.emplace_back(std::get<0>(data), std::get<1>(data), std::get<2>(data), std::get<3>(data));
    }

    std::vector<std::tuple<std::string, int, std::tuple<int, int>, bool, std::tuple<double, double>, double>> dataStations = {
            {"Terminus CHU",                     2, {0,                               0},                      false, {0,     DISTANCE_TOT}, 1.1},
            {"CHR Oscar Lambret",                1, {rand() % MAX_PASSENGERS_STATION, rand() %
                                                                                      MAX_PASSENGERS_STATION}, false, {DISTANCE_TOT -
                                                                                                                       11000, 11000},        1.1},
            {"Porte des Postes",                 1, {rand() % MAX_PASSENGERS_STATION, rand() %
                                                                                      MAX_PASSENGERS_STATION}, false, {DISTANCE_TOT -
                                                                                                                       10500, 10500},        1.1},
            {"Wazemmes",                         1, {rand() % MAX_PASSENGERS_STATION, rand() %
                                                                                      MAX_PASSENGERS_STATION}, false, {DISTANCE_TOT -
                                                                                                                       9000,  9000},         1.1},
            {"Gambetta",                         1, {rand() % MAX_PASSENGERS_STATION, rand() %
                                                                                      MAX_PASSENGERS_STATION}, false, {DISTANCE_TOT -
                                                                                                                       8100,  8100},         1.1},
            {"République Beaux-Arts",            1, {rand() % MAX_PASSENGERS_STATION, rand() %
                                                                                      MAX_PASSENGERS_STATION}, false, {DISTANCE_TOT -
                                                                                                                       7200,  7200},         1.1},
            {"Rihour",                           2, {rand() % MAX_PASSENGERS_STATION, rand() %
                                                                                      MAX_PASSENGERS_STATION}, false, {DISTANCE_TOT -
                                                                                                                       6500,  6500},         1.1},
            {"Lille FLandres",                   2, {rand() % MAX_PASSENGERS_STATION, rand() %
                                                                                      MAX_PASSENGERS_STATION}, false, {DISTANCE_TOT -
                                                                                                                       5500,  5500},         2},
            {"Caulier",                          2, {rand() % MAX_PASSENGERS_STATION, rand() %
                                                                                      MAX_PASSENGERS_STATION}, false, {DISTANCE_TOT -
                                                                                                                       5000,  5000},         2},
            {"Fives",                            2, {rand() % MAX_PASSENGERS_STATION, rand() %
                                                                                      MAX_PASSENGERS_STATION}, false, {DISTANCE_TOT -
                                                                                                                       4500,  4500},         2},
            {"Marbrerie",                        2, {rand() % MAX_PASSENGERS_STATION, rand() %
                                                                                      MAX_PASSENGERS_STATION}, false, {DISTANCE_TOT -
                                                                                                                       4000,  4000},         2},
            {"Hellemmes",                        2, {rand() % MAX_PASSENGERS_STATION, rand() %
                                                                                      MAX_PASSENGERS_STATION}, false, {DISTANCE_TOT -
                                                                                                                       3500,  3500},         2},
            {"Lezennes",                         2, {rand() % MAX_PASSENGERS_STATION, rand() %
                                                                                      MAX_PASSENGERS_STATION}, false, {DISTANCE_TOT -
                                                                                                                       2500,  2500},         2},
            {"Pont de Bois",                     2, {rand() % MAX_PASSENGERS_STATION, rand() %
                                                                                      MAX_PASSENGERS_STATION}, false, {DISTANCE_TOT -
                                                                                                                       2100,  2100},         2},
            {"Villeneuve d'Ascq Hôtel de Ville", 2, {rand() % MAX_PASSENGERS_STATION, rand() %
                                                                                      MAX_PASSENGERS_STATION}, false, {DISTANCE_TOT -
                                                                                                                       1900,  1900},         2},
            {"Cité Scientifique",                2, {rand() % MAX_PASSENGERS_STATION, rand() %
                                                                                      MAX_PASSENGERS_STATION}, false, {DISTANCE_TOT -
                                                                                                                       500,   500},          2},
            {"Terminus CANTONS",                 2, {0,                               0},                      false, {DISTANCE_TOT, 0},     1.1}
    };

    // Implementation of Stations
    Stations.reserve(dataStations.size());
    for (auto &data: dataStations) {
        Stations.emplace_back(std::get<0>(data), std::get<1>(data), std::get<2>(data), std::get<3>(data),
                              std::get<4>(data), std::get<5>(data));
    }


    // Call these somewhere else

    // Definition of trains
    initTrains(Trains, Line[1], TRAIN_NUMBER);

    // Set each train's neighbour to each other
    setVoisinList(Trains);

    // Set each station next station to each other
    initNextStation(Stations, &Line[1]);

    // Initialise the first station of each train
    for (auto &train: Trains) {
        setStation(Stations, train, 1);
    }

    //Set the next Terminus of each other
    Line[1].setNextTerminus(&Line[0]);
    Line[0].setNextTerminus(&Line[1]);


    // print time

    // launch a thread for each train
    threads.reserve(Trains.size());
    for (auto &train: Trains) {
        threads.emplace_back(manageTrain, std::ref(sharedData), std::ref(train), std::ref(Trains), std::ref(Stations),
                             std::ref(mtx_), std::ref(stop_working));
    }

    //renderThread.join();
    for (auto &thread: threads) {
        if (thread.joinable())
            thread.join();
    }

    return 0;
}