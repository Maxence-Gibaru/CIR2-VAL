
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

#define DISTANCE_TOT 3000
#define TRAIN_NUMBER 1


using namespace std::chrono_literals;

/*
 * TODO
 * - [x] Gérer l'accélération d'une station à une autre
 * - [X] Gérer les distance parcourues entre chaque train
 * - [ ] Mixer Terminus et Station
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
    Line.push_back(CANTONS);
    Line.push_back(CHU);

    // Implementation of Stations
    Station PorteDesPostes("Porte des Postes", 1, 10, false, 100);
    Station Wazemmes("Wazemmes", 1, 10, false, 500);
    Station Gambetta("Gambetta", 1, 10, false, 1100);
    Station Republique("République Beaux-Arts", 1, 10, false, 1900);
    Station Rihour("Rihour", 2, 10, false, 2500);
    Station LilleFlandres("Lille FLandres", 2, 10, false, DISTANCE_TOT);
    Stations.push_back(PorteDesPostes);
    Stations.push_back(Wazemmes);
    Stations.push_back(Gambetta);
    Stations.push_back(Republique);
    Stations.push_back(Rihour);
    Stations.push_back(LilleFlandres);


    // Definition of trains
    initTrains(Trains, CANTONS, TRAIN_NUMBER);

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

                        // find a way to swap the stations and continue driving with accelerations
                        if (train.trainStationArrived() and round(train.getNextStation()->getCoordX()) != round(train.getTerminus()->getCoordT())) {
                            train.setNextStation();
                            train.updateTotalCoordX();
                            train.setCoordX(0);
                            train.setTime(0.0);


                        }

                        // When a train arrive, it swaps to another terminus in the other way

                        // ça marche pas pour l'instant
                        if (train.trainArrived()) {
                            train.swapTerminus();
                            setFirstStation(Stations, Trains);
                        }

                        /* ===== DETAILS ===== */

                        mtx_.lock();
//                        std::cout << "DISTANCE : " << train.getDistance()  << std::endl;
                        train.print();
                        mtx_.unlock();

                        // delay between threads
                        std::this_thread::sleep_for(0.1s);
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