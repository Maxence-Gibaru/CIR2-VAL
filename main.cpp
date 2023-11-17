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




void fillTab(std::vector<Train> &myList, Train &train) {
    myList.push_back(train);
}

int main()
{
    std::vector<std::jthread> threads(10);
    std::vector<Train> myList;

    Terminus Ugo("Ugo");
    Terminus Maxence("Maxence");
    Terminus Laurine("Laurine");
    Terminus Momo("Momo");

    Train myTrain1(0.0, Ugo, 0.0, 10, "none");
    Train myTrain2(0.0, Maxence, 0.0, 10, "none");
    Train myTrain3(0.0, Laurine, 0.0, 10, "none");
    Train myTrain4(0.0, Momo, 0.0, 10, "none");


    myList.push_back(myTrain1);
    myList.push_back(myTrain2);
    myList.push_back(myTrain3);
    myList.push_back(myTrain4);


    // number max of threads

    bool stopping = false;

    for(int i = 0; i < myList.size(); i++)
    {
        threads.emplace_back(
                [&myList, i, &stopping]() mutable -> auto {
                    while(!stopping) {
                        if(i == 0) {
                            myList[i].setVitesse(1);
                        }

                        else if(i != 0  and myList[i-1].getVitesse() >= 10) {
                            myList[i].setVitesse(1);
                        }
                        std::cout <<  myList[i].getTerminus().getNom() << " : |" << myList[i].getVitesse() << "|" << std::endl;
                        std::this_thread::sleep_for(1s);
                    }
                    std::cout << std::endl;
                });
    }

    std::cout << "Main thread" << std::endl;


    for (auto& thread : threads) {
        if(thread.joinable())
            thread.join();
    }







}