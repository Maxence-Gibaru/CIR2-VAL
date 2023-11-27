
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

#define DISTANCE_TOT 15000
#define TRAIN_NUMBER 1


using namespace std::chrono_literals;

/*
 * TODO
 * - [ ] Gérer l'accélération d'une station à une autre
 * - [ ] Implémenter les passagers avec temps d'arrêts aux stations
 * - [ ] Optimisation et cleanage du code
 * - [ ] adaptation des vitesses et temps d'arrêt en fonction de la distance de sécurité
 * - [ ] création du visuel avec la lib SFML
 * - [ ] adapter la structure pour le visuel
 */




int main() {

    //display();

    // Vector definition
    std::mutex mtx_;
    std::vector<std::thread> threads;
    std::vector<Train> Trains;
    std::vector<Station> Stations;
    std::vector<Terminus> Line;

    // make function that globalises the process

    // Implementation of Terminus
    Terminus CHU("CHU-Eurasanté", 0, DISTANCE_TOT);
    Terminus CANTONS("4 Cantons", 0, DISTANCE_TOT);
    Line.push_back(CHU);
    Line.push_back(CANTONS);

    // Implementation of Stations
    Station LilleFlandres("Lille FLandres", 1, 10, false, 100); // gérer le cas où elle est à 100
    Station LilleEurope("Lille Europe", 2, 10, false, 25000);
    Stations.push_back(LilleFlandres);
    Stations.push_back(LilleEurope);

    // Definition of trains
    initTrains(Trains, CHU, TRAIN_NUMBER);

    // Set each train's neighbour to each other
    setVoisinList(Trains);

    // Set each station next station to each other
    initNextStation(Stations);

    // Initialise the first station of each train
    setFirstStation(Stations, Trains);

    //Set the next Terminus of each other
    CANTONS.setNextTerminus(&CHU);
    CHU.setNextTerminus(&CANTONS);

    bool stopping = false; // gérer la boucle while en fonction du temps

    // launch a thread for each train
    for (auto &train: Trains) {
        threads.emplace_back(
                [&mtx_, &train, &Trains, &stopping, &Stations]() mutable -> auto {
                    while (!stopping) {
                        // mettre tout ça ailleurs
                        double time1 = MAX_SPEED / COEFF_SPEED;
                        double time2 = train.getNextStation()->getCoordX() / MAX_SPEED;

                        /* ===== MOVE ===== */

                        // make those 2 "if" one
                        if (train.getId() == 1) {
                            train.moveX(train.getAccelerationDistance(), time1, time2);

                        }
                        // faire en sorte que le cas getId == Trains.size() soit enlevé, c'est nul à chier
                        if (train.checkSecurityDistance() and train.getId() != Trains.size()) {
                            train.getVoisin()->moveX(train.getAccelerationDistance(), time1, time2);
                        }

                        /* ===== SPEED ===== */

                        // find a way to stop using many "if" conditional statements
                        if (train.fullSpeed()) {
                            std::cout << "HIGH" << std::endl;
                            if (train.getCoordX() < train.getAccelerationDistance()) {
                                train.addSpeed(REFRESH);
                            }
                            if (train.getCoordX() >= train.getNextStation()->getCoordX() - train.getAccelerationDistance() and
                                train.getSpeed() > 0) {
                                train.subSpeed(REFRESH);
                            }
                        } else {
                            std::cout << "LOW" << std::endl;
                            if (train.getCoordX() < train.getAccelerationDistance() and train.getSpeed() < MAX_SPEED) {
                                train.addSpeed(REFRESH);
                            }
                            if (train.getCoordX() >= train.getNextStation()->getCoordX() - train.getAccelerationDistance() and
                                train.getSpeed() > 0) {
                                train.subSpeed(REFRESH);
                            }
                        }


                        /* ===== MANAGE ===== */

                        // find a way to swap the stations and continue driving with accelerations
                        if (train.trainStationArrived()) {
                            train.setNextStation();
                        }

                        // When a train arrive, it swaps to another terminus in the other way
                        if (train.trainArrived()) {
                            train.swapTerminus();
                            setFirstStation(Stations, Trains);
                        }

                        /* ===== DETAILS ===== */

                        mtx_.lock();
                        train.print();
                        mtx_.unlock();

                        // delay between threads
                        std::this_thread::sleep_for(1s);
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