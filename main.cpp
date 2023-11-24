
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <algorithm>
#include "Terminus.h"
#include "Train.h"
#include "Station.h"
#include <cmath>
#include "TrainControlFunction.h"

#define DISTANCE_TOT 30000
#define DISTANCE_SECURITY 1000
#define MIN_SPEED 122.4
#define MAX_SPEED 280.0
#define COEFF_SPEED 10.0
#define TRAIN_NUMBER 1
#define REFRESH 0.01


using namespace std::chrono_literals;

int main() {


    std::mutex mtx_;

    std::vector<std::thread> threads;
    std::vector<Train> Trains;
    std::vector<Station> Stations;
    std::vector<Terminus> Line;

    // mettre toutes ces lignes sous la forme d'une fonction

    Terminus CHU("CHU-Eurasanté", 0, DISTANCE_TOT);
    Terminus CANTONS("4 Cantons", 0, DISTANCE_TOT);
    Line.push_back(CHU);
    Line.push_back(CANTONS);





    // faire une fonction qui globalise
    Station LilleFlandres("Lille FLandres", 1, 10, false, 12000);
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
                        std::cout << "------------------------------------------------------------------------"
                                  << std::endl;


                        time += REFRESH;
                        // find a way to stop using many "if" conditional statements
                        double d_ = pow(MAX_SPEED, 2) / COEFF_SPEED;
                        double d1 = pow(MAX_SPEED, 2) / (2 * COEFF_SPEED);
                        double V0 = sqrt(train.getDistanceStation()) * COEFF_SPEED;
                        double d1_V0 = pow(V0, 2) / 2 * COEFF_SPEED;
                        double t1 = MAX_SPEED / COEFF_SPEED;
                        double t2 = train.getNextStation()->getCoordX() / MAX_SPEED;


                        std::cout << "SECONDES: " << time << std::endl;

                        if (train.getCoordX() < d1) {
                            train.addSpeed(COEFF_SPEED * REFRESH);
                        }
                        if (train.getCoordX() >= train.getNextStation()->getCoordX() - d1 and train.getSpeed() > 0) {
                            train.subSpeed(COEFF_SPEED * REFRESH);
                        }


                        /*
                        // put the formula of movement
                        if(d_ <=  train.getDistanceStation()) {


                        }

                        else if(train.getSpeed() <= V0 and train.getCoordX() <= d1_V0) {
                            train.addSpeed(COEFF_SPEED);
                        }
                        else if(train.getCoordX() >= train.getDistanceStation() - d1_V0 and train.getSpeed() > 0) {
                            train.subSpeed(COEFF_SPEED);
                        }*/



                        mtx_.lock();
                        std::cout << "Arrivée dans : " << train.getDistanceStation() << std::endl;
                        std::cout << "Vitesse du train : " << train.getSpeed() << std::endl;
                        mtx_.unlock();

                        // make those 2 "if" one
                        if (train.getId() == 1 and !train.getState()) {
                            train.moveX(d1, t1, t2, time);
                        }

                        if (train.trainStationArrived()) {
                            mtx_.lock();
                            std::cout << "Arrêt du train " << train.getId() << " à la gare "
                                      << train.getNextStation()->getNom() << std::endl;
                            mtx_.unlock();
                            train.setStation(train.getNextStation()->getNeighbour());

                            time = 0.0;
                        }

                        // faire en sorte que le cas getId == Trains.size() soit enlevé, c'est nul à chier
                        if (train.checkSecurityDistance(DISTANCE_SECURITY) and train.getId() != Trains.size()) {
                            train.getVoisin()->moveX(d1, t1, t2, time);
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
}