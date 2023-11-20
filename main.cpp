
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <algorithm>
#include "include/Terminus.h"
#include "include/Train.h"
#include "include/TrainControlFunction.h"

#define DISTANCE_SEC 2000

using namespace std::chrono_literals;

int main()
{
    std::mutex mtx_;

    std::vector<std::thread> threads(10);
    std::vector<Train> myList;

    Terminus Ugo("Ugo", 0);
    Terminus Maxence("Maxence", 0);

    Train myTrain1(1,0.0, Maxence, 0.0, 10, false);
    Train myTrain2(2,0.0, Maxence, 0.0, 10, false);
    Train myTrain3(3,0.0, Maxence, 0.0, 10, false);
    Train myTrain4(4,0.0, Maxence, 0.0, 10, false);
    myList.push_back(myTrain1);
    myList.push_back(myTrain2);
    myList.push_back(myTrain3);
    myList.push_back(myTrain4);


    setVoisinList(myList);

    bool stopping = false;

    for(auto &train: myList)
    {
        threads.emplace_back(
                [&mtx_,&train, &stopping, &Maxence]() mutable -> auto {
                    while(!stopping) {
                        if(train.getId() == 1 and !train.getState() ) {

                            train.setSpeed(100); // 108 m/s soit 30 km/h
                            train.setCoordX(100);
                        }

                        if(train.checkSecurityDistance(1000) and !train.getState() ) {
                            train.getVoisin()->setSpeed(100); // 108 m/s soit 30 km/h
                            train.getVoisin()->setCoordX(100);
                        }



                        
                        if(train.getCoordX() >= 2000 ) {
                            train.setSpeed(0);
                            train.setCoordX(0);
                            train.setState(true);
                        }


                        mtx_.lock();

                        std::cout <<  train.getId() << " : |" << train.getCoordX()<< "|" << std::endl;

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