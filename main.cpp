
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
#define COEFF_SPEED 10



using namespace std::chrono_literals;

int main()
{
    std::mutex mtx_;

    std::vector<std::thread> threads;
    std::vector<Train> myList;
    std::vector<Station> Stations;

    // mettre toutes ces lignes sous la forme d'une fonction

    Terminus CHU("Lille CHU-Eurasanté", 0, 0);
    Terminus CANTONS("Villeneuve d'Ascq 4 Cantons Stade Pierre Mauroy", 0, DISTANCE_TOT);

    Train myTrain1(1,0.0, CANTONS, 0.0, 10, false);
    Train myTrain2(2,0.0, CANTONS, 0.0, 10, false);
    Train myTrain3(3,0.0, CANTONS, 0.0, 10, false);
    Train myTrain4(4,0.0, CANTONS, 0.0, 10, false);
    myList.push_back(myTrain1);
    myList.push_back(myTrain2);
    myList.push_back(myTrain3);
    myList.push_back(myTrain4);

    //Station LilleFlandres("Lille FLandres", 10, false, 1500);
    Station LilleEurope("Lille Europe", 10, false, 1500);
    //tations.push_back(LilleFlandres);
    Stations.push_back(LilleEurope);


    setVoisinList(myList);
    setNearestStation(Stations, myList);

    bool stopping = false;

    for(auto &train: myList)
    {
        threads.emplace_back(
                [&mtx_,&train, &myList, &stopping, &CANTONS, &CHU, &Stations]() mutable -> auto {
                    while(!stopping) {
                        setNearestStation(Stations, myList);

                        for(auto &station : Stations) {
                            if(train.getCoordX() == train.getStation()->getCoordX() or train.getCoordX() == (train.getStation()->getCoordX() + 2*(DISTANCE_TOT - train.getStation()->getCoordX())) and !train.getStation()->isTrain()){
                                train.getStation()->setPresence(true);
                                train.setSpeed(0);
                                std::cout << "Arrêt du train " << train.getId() << " à la gare " << train.getStation()->getNom() << std::endl;
                            }
                            if (train.getSpeed() <= MAX_SPEED) {
                                train.addSpeed(COEFF_SPEED);
                            }
                        }

                        if(train.getId() == 1 and !train.getState()) {
                            train.moveX(train.getSpeed());
                        }

                        if(train.checkSecurityDistance(DISTANCE_SECURITY) and train.getId() != myList.size()) {
                            train.getVoisin()->moveX(train.getSpeed());
                        }





                        // faire une méthode swap terminus
                        if(train.getCoordX() >= CANTONS.getCoordT() ) {
                            train.setTerminus(CHU);
                            train.setCoordX(0);
                        }

                        if(train.getCoordX() >= CANTONS.getCoordT() * 2.0) {
                            train.setTerminus(CANTONS);
                            train.setCoordX(0);
                        }

                        mtx_.lock();

                        if(train.getId() == 1) {
                            std::cout <<  train.getId() << " : |" << train.getCoordX()<< " | " << train.getTerminus().getNom() << std::endl;
                        }
                        mtx_.unlock();
                        std::this_thread::sleep_for(1s);

                    }
                    std::cout << std::endl;
                });
    }

    for (auto& thread : threads) {
        if(thread.joinable())
            thread.join();
    }
}