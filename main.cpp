
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <algorithm>
#include "Terminus.h"
#include "Train.h"
#include "Station.h"
#include "TrainControlFunction.h"

#define DISTANCE_TOT 3000
#define DISTANCE_SECURITY 1000
#define MIN_SPEED 122.4
#define MAX_SPEED 280
#define COEFF_SPEED 100



using namespace std::chrono_literals;

int main()
{
    std::mutex mtx_;

    std::vector<std::thread> threads;
    std::vector<Train> Trains;
    std::vector<Station> Stations;

    // mettre toutes ces lignes sous la forme d'une fonction

    Terminus CHU("CHU-Eurasanté", 0, 0);
    Terminus CANTONS("4 Cantons", 0, DISTANCE_TOT);


    initTrains(Trains, CANTONS, 45);

    Station LilleFlandres("Lille FLandres", 1,  10, false, 500);
    Station LilleEurope("Lille Europe", 2, 10, false, 1800);
    Stations.push_back(LilleFlandres);
    Stations.push_back(LilleEurope);


    setVoisinList(Trains);
    setNearestStation(Stations, Trains);
    setNextStation(Stations);
    bool stopping = false;

    for(auto &train: Trains)
    {
        threads.emplace_back(
                [&mtx_,&train, &Trains, &stopping, &CANTONS, &CHU, &Stations]() mutable -> auto {
                    while(!stopping) {
                        train.setSpeed(COEFF_SPEED);
                        if(train.getCoordX() == train.getNextStation()->getCoordX() or train.getCoordX() == DISTANCE_TOT*2 - train.getNextStation()->getCoordX()){
                            mtx_.lock();
                            std::cout << "Arrêt du train " << train.getId() << " à la gare " << train.getNextStation()->getNom() << std::endl;
                            mtx_.unlock();
                        }

                        // mettre les deux conditions suivantes en une
                        if(train.getId() == 1 and !train.getState()) {
                            train.moveX(train.getSpeed());
                        }

                        if(train.checkSecurityDistance(DISTANCE_SECURITY) and train.getId() != Trains.size()) {
                            train.getVoisin()->moveX(train.getSpeed());
                        }


                        // faire une méthode next terminus
                        if(train.getCoordX() >= CANTONS.getCoordT() ) {
                            train.setTerminus(CHU);
                        }

                        if(train.getCoordX() >= CANTONS.getCoordT()*2) { // C'est nul à chier de faire x 2
                            train.setTerminus(CANTONS);
                            train.setCoordX(0);
                        }

                        mtx_.lock();
                        if(train.getCoordX() > 0) {
                            std::cout <<  train.getId() << " : |" << train.getCoordX()<< " | " << train.getTerminus().getNom() <<  std::endl;
                        }
                        mtx_.unlock();
                        std::this_thread::sleep_for(0.5s);

                    }
                    std::cout << std::endl;
                });
    }

    for (auto& thread : threads) {
        if(thread.joinable())
            thread.join();
    }
}