
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <algorithm>
#include "Terminus.h"
#include "Train.h"
#include "Station.h"
#include "TrainControlFunction.h"

#define DISTANCE_TOT 2000
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

    Terminus CHU("CHU-Eurasanté", 0, DISTANCE_TOT);
    Terminus CANTONS("4 Cantons", 0, DISTANCE_TOT);


    initTrains(Trains, CANTONS, 1);


    // faire une fonction qui globalise
    Station LilleFlandres("Lille FLandres", 1,  10, false, 500);
    Station LilleEurope("Lille Europe", 2, 10, false, 1800);
    Stations.push_back(LilleFlandres);
    Stations.push_back(LilleEurope);



    setVoisinList(Trains);
    setNextStation(Stations);
    setNearestStation(Stations, Trains);

    bool stopping = false;

    for(auto &train: Trains)
    {
        threads.emplace_back(
                [&mtx_,&train, &Trains, &stopping, &CANTONS, &CHU, &Stations]() mutable -> auto {
                    while(!stopping) {
                        train.setSpeed(COEFF_SPEED);
                        /*if(train.getSpeed() <MAX_SPEED and train.getCoordX() <= 4000) {
                            train.addSpeed(COEFF_SPEED);
                        }

                        if(train.getCoordX() >= 5000 and train.getSpeed() > 0) {
                            train.subSpeed(COEFF_SPEED);
                        }*/

                        if(train.getCoordX() == train.getNextStation()->getCoordX()){
                            mtx_.lock();
                            std::cout << "Arrêt du train " << train.getId() << " à la gare " << train.getNextStation()->getNom() << std::endl;
                            mtx_.unlock();
                            train.setStation(train.getNextStation()->getNeighbour());
                        }

                        std::cout << train.getDistanceStation(train.getNextStation()) << std::endl;

                        // mettre les deux conditions suivantes en une
                        if(train.getId() == 1 and !train.getState()) {
                            train.moveX(train.getSpeed());
                        }

                        if(train.checkSecurityDistance(DISTANCE_SECURITY) and train.getId() != Trains.size()) {
                            train.getVoisin()->moveX(train.getSpeed());
                        }


                        // faire une méthode next terminus
                        if(train.getCoordX() == train.getTerminus().getCoordT() and train.getTerminus().getNom() == CANTONS.getNom()) {
                            train.setTerminus(CHU);
                            setNearestStation(Stations, Trains);
                            train.setCoordX(0);
                        }

                        if(train.getCoordX() == train.getTerminus().getCoordT() and train.getTerminus().getNom() == CHU.getNom()) {
                            setNearestStation(Stations, Trains);
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