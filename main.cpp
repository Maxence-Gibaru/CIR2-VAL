
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <cmath>
#include "Terminus.h"
#include "Train.h"
#include "Station.h"
#include "TrainControlFunction.h"

#define DISTANCE_TOT 30000
#define TRAIN_NUMBER 1
#define REFRESH 1

using namespace std::chrono_literals;

/*
 *
 * - [ ] On cleanera tout le code avant de commencer à faire le SFML
 * - [ ] Il faudra aussi gérer toutes les exceptions dans les méthodes
 *
 *
 */

int main() {


    std::mutex mtx_;
    std::vector<std::thread> threads;
    std::vector<Train> Trains;
    std::vector<Station> Stations;
    std::vector<Terminus> Line;

    // make function that globalises the process

    Terminus CHU("CHU-Eurasanté", 0, DISTANCE_TOT);
    Terminus CANTONS("4 Cantons", 0, DISTANCE_TOT);
    Line.push_back(CHU);
    Line.push_back(CANTONS);
    Station LilleFlandres("Lille FLandres", 1, 10, false, 2000);
    Station LilleEurope("Lille Europe", 2, 10, false, 25000);
    Stations.push_back(LilleFlandres);
    Stations.push_back(LilleEurope);
    initTrains(Trains, CHU, TRAIN_NUMBER);
    setVoisinList(Trains);
    initNextStation(Stations);
    setFirstStation(Stations, Trains);

    initNextTerminus(Line);
    CANTONS.setNextTerminus(&CHU);
    CHU.setNextTerminus(&CANTONS);

    float time = 0.0;


    bool stopping = false;

    for (auto &train: Trains) {
        threads.emplace_back(
                [&time, &mtx_, &train, &Trains, &stopping, &Stations]() mutable -> auto {
                    while (!stopping) {
                        double highestDistance = pow(MAX_SPEED, 2) / COEFF_SPEED;
                        double accelerationDistance = pow(MAX_SPEED, 2) / (2 * COEFF_SPEED);
                        double V0 = sqrt(train.getNextStation()->getCoordX()* COEFF_SPEED) ;
                        double accelerationDistance0 = pow(V0, 2) / (2 * COEFF_SPEED);
                        double time1 = MAX_SPEED / COEFF_SPEED;
                        double time2 = train.getNextStation()->getCoordX() / MAX_SPEED;

                        //train.setHighestDistance();
                        std::cout << "------------------------------------------------------------------------"
                                  << std::endl;

                        //std::cout << train.getHighestDistance() << std::endl;

                        time += REFRESH;
                        // find a way to stop using many "if" conditional statements

                        std::cout << "SECONDS: " << time << std::endl;

                        std::cout << accelerationDistance0 << std::endl;

                        /*
                        if (highestDistance <= train.getNextStation()->getCoordX()) {
                            if (train.getCoordX() < accelerationDistance) {
                                train.addSpeed(REFRESH);
                            }
                            if (train.getCoordX() >= train.getNextStation()->getCoordX() - accelerationDistance and
                                train.getSpeed() > 0) {
                                train.subSpeed(REFRESH);
                            }
                        }
*/

                        if (train.getCoordX() < accelerationDistance0) {
                            train.addSpeed(REFRESH);
                        }
                        if (train.getCoordX() >= train.getNextStation()->getCoordX() - accelerationDistance0 and
                            train.getSpeed() > 0) {
                            train.subSpeed(REFRESH);
                         }


                        mtx_.lock();
                        std::cout << "Arrivée dans : " << train.getDistanceStation() << std::endl;
                        std::cout << "Vitesse du train : " << train.getSpeed() << std::endl;
                        mtx_.unlock();



                        // make those 2 "if" one
                        if (train.getId() == 1 and !train.getState()) {
                            train.moveX(accelerationDistance0, time1, time2, time);
                        }

                        // find a way to swap the stations and continue driving with accelerations
                        if (train.trainStationArrived()) {
                            mtx_.lock();
                            std::cout << "Arrêt du train " << train.getId() << " à la gare "
                                      << train.getNextStation()->getNom() << std::endl;
                            mtx_.unlock();
                            train.setStation(train.getNextStation()->getNeighbour());

                            time = 0.0;
                        }

                        // faire en sorte que le cas getId == Trains.size() soit enlevé, c'est nul à chier
                        if (train.checkSecurityDistance() and train.getId() != Trains.size()) {

                            train.moveX(accelerationDistance0, time1, time2, time);
                        }




                        // When a train arrive, it swaps to another terminus in the other way
                        if (train.trainArrived()) {
                            train.swapTerminus();
                            setFirstStation(Stations, Trains);

                        }




                        mtx_.lock();
                        std::cout << train.getId() << " : |" << train.getCoordX() << " | "
                                  << train.getTerminus()->getNom() << std::endl;
                        mtx_.unlock();

                        // delay between threads

                        std::this_thread::sleep_for(0.01s);
                    }
                    std::cout << std::endl;
                });
    }

    for (auto &thread: threads) {
        if (thread.joinable())
            thread.join();
    }

    return EXIT_SUCCESS;
}