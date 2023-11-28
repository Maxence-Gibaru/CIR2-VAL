
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


using namespace std::chrono_literals;

/*
 * TODO
 * - [x] Gérer l'accélération d'une station à une autre
 * - [X] Gérer les distance parcourues entre chaque train
 * - [ ] Implémenter les heures de la journée
 * - [ ] Mixer Terminus et Station, héritage ??
 *   [ ] lier la vitesse avec la fonction train.move()
 * - [ ] Implémenter les passagers avec temps d'arrêts aux stations
 * - [ ] Optimisation et cleanage du code
 * - [ ] adaptation des vitesses et temps d'arrêt en fonction de la distance de sécurité
 * - [ ] création du visuel avec la lib SFML
 * - [ ] adapter la structure pour le visuel
 */




int main() {

    /*   // current date/time based on current system
   time_t now = time(0);

   cout << "Number of sec since January 1,1970 is:: " << now << endl;

   tm *ltm = localtime(&now);

   // print various components of tm structure.
   cout << "Year:" << 1900 + ltm->tm_year<<endl;
   cout << "Month: "<< 1 + ltm->tm_mon<< endl;
   cout << "Day: "<<  ltm->tm_mday << endl;
   cout << "Time: "<< 5+ltm->tm_hour << ":";
   cout << 30+ltm->tm_min << ":";
   cout << ltm->tm_sec << endl;*/




    //display();

    // Vector definition
    std::mutex mtx_;
    std::vector<std::thread> threads;
    std::vector<Train> Trains;
    std::vector<Station> Stations;
    std::vector<Terminus> Line;

    // make function that globalises the process


    // Implementation of Terminus
    std::vector<std::tuple<std::string, int, double, bool>> dataTerminus = {
            {"CHU-Eurasanté", 0, DISTANCE_TOT, 0},
            {"4 Cantons", 0, DISTANCE_TOT, 1}
    };

    for(auto &data : dataTerminus) {
        Line.emplace_back(std::get<0>(data), std::get<1>(data), std::get<2>(data), std::get<3>(data));
    }

    std::vector<std::tuple<std::string, int, int, bool, double>> dataStations = {
            {"Terminus CHU", 2, 0, false, 0},
            {"Porte des Postes", 1, 10, false, 100},
            {"Wazemmes", 1, 10, false, 500},
            {"Gambetta", 1, 10, false, 1100},
            {"République Beaux-Arts", 1, 10, false, 1900},
            {"Rihour", 2, 10, false, 2500},
            {"Lille FLandres", 2, 10, false, 2900},
            {"Terminus CANTONS", 2, 0, false, DISTANCE_TOT}
    };

    // Implementation of Stations
    for(auto &data : dataStations) {
        Stations.emplace_back(std::get<0>(data),std::get<1>(data),std::get<2>(data),std::get<3>(data),std::get<4>(data));
    }

    // Definition of trains
    initTrains(Trains, Line[1], TRAIN_NUMBER);

    // Set each train's neighbour to each other
    setVoisinList(Trains);

    // Set each station next station to each other
    initNextStation(Stations, &Line[1]);

    // Initialise the first station of each train
    setStation(Stations, Trains, 1);

    //Set the next Terminus of each other
    // !!! OPTI
    Line[1].setNextTerminus(&Line[0]);
    Line[0].setNextTerminus(&Line[1]);

    bool stopping = false; // gérer la boucle while en fonction du temps

    // launch a thread for each train
    for (auto &train: Trains) {
        threads.emplace_back(
                [&mtx_, &train, &Trains, &stopping, &Stations]() mutable -> auto {
                    while (!stopping) {
                        /* ===== MOVE ===== */

                        // make those 2 "if" one
                        if (train.getId() == 1) {
                            train.moveX();
                        }

                        // faire en sorte que le cas getId == Trains.size() soit enlevé, c'est nul à chier
                        if (train.checkSecurityDistance() and train.getId() != Trains.size()) {
                            train.getVoisin()->moveX();
                        }

                        /* ===== SPEED ===== */

                        // en vrai c'est totalement indépendant mdrr
                        train.updateSpeed();


                        /* ===== MANAGE ===== */

                        //  !!! put everything in a single function

                        if (train.trainStationArrived() and round(train.getNextStation()->getCoordX()) != round(train.getTerminus()->getCoordT())) {
                            train.setNextStation();
                            train.updateTotalCoordX();
                            // make a reset function
                            train.setCoordX(0);
                            train.setTime(0.0);
                        }

                        // When a train arrive, it swaps to another terminus in the other direction
                        if (train.trainArrived()) {
                            train.swapTerminus();
                            setStation(Stations, Trains, 0);
                            initNextStation(Stations, train.getTerminus());
                        }

                        /* ===== DETAILS ===== */

                        mtx_.lock();
                        train.print();
                        mtx_.unlock();

                        // delay between threads
                        std::this_thread::sleep_for(-1s);
                        std::cout << std::endl;
                    }
                });
    }

    for (auto &thread: threads) {
        if (thread.joinable())
            thread.join();
    }

    return 0;
}