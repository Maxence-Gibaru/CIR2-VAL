#include <iostream>
#include "include/Train.h"
#include <array>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include <algorithm>
#include "include/Terminus.h"

using namespace std::chrono_literals;

int distance = 2000;

// va falloir faire des proportionnalité de fou malade

void fillTab(std::vector<Train> &myList, Train &train) {
    myList.push_back(train);
}

int main()
{
    std::mutex mtx_;

    std::vector<std::thread> threads(10);
    std::vector<Train> myList;

    Terminus Ugo("Ugo", 0);
    Terminus Maxence("Maxence", 0);


    Train myTrain1(0.0, Maxence, 0.0, 10, "none");
    Train myTrain2(0.0, Maxence, 0.0, 10, "none");
    Train myTrain3(0.0, Maxence, 0.0, 10, "none");
    Train myTrain4(0.0, Maxence, 0.0, 10, "none");


    myList.push_back(myTrain1);
    myList.push_back(myTrain2);
    myList.push_back(myTrain3);
    myList.push_back(myTrain4);


    // number max of threads

    bool stopping = false;

    for(int i = 0; i < myList.size(); i++)
    {
        threads.emplace_back(
                [&mtx_,&myList, i, &stopping, &Maxence]() mutable -> auto {
                    while(!stopping) {
                        if(i == 0) {
                            myList[i].setSpeed(108); // 108 m/s soit 30 km/h
                            myList[i].setCoordX(108);
                        }

                        else if(i != 0  and std::abs(myList[i-1].getCoordX() - myList[i].getCoordX()) >= 1000) {
                            myList[i].setCoordX(108);
                        }

                        else if(myList[i].getCoordX() >= distance) {
                            myList[i].getTerminus().addTrainNumber();
                            myList[i].setSpeed(0);
                            //std::cout << "Le metro n°"<< i << " viens d'arriver au terminus" << myList[i].getTerminus().getNom() << std::endl;
                        }

                        /*else if(Maxence.getTrainNumber() == myList.size()) {
                            std::cout <<"Tous les metros sont arrivés ! " << std::endl;
                            stopping = true;
                        }*/



                        mtx_.lock();
                        std::cout <<  i << " : |" << myList[i].getCoordX()<< "|" << " ARRIVES : " << Maxence.getTrainNumber() << std::endl;
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