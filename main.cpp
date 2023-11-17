#include <SFML/Graphics.hpp>
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
    std::vector<std::thread> threads(10);
    std::vector<Train> myList;

    Terminus Ugo("Ugo");
    Terminus Maxence("Maxence");

    Train myTrain1(0.0, Ugo, 0.0, 10, "sexe");
    Train myTrain2(0.0, Maxence, 0.0, 10, "sexe");

    myList.push_back(myTrain1);
    myList.push_back(myTrain2);


    // number max of threads

    bool stopping = false;

    for(auto &train : myList) {
        threads.emplace_back(
                [&train, &stopping](){
                    while(!stopping) {
                        if(train.getTerminus().getNom() == "Ugo") {
                            train.ajusterVitesse(0.5);
                        } else {
                            train.ajusterVitesse(1);
                        }
                        std::cout << "Train de " << train.getTerminus().getNom() << " de vitesse : " << train.getVitesse() << std::endl;
                        std::this_thread::sleep_for(1s);
                    }
                });
    }


    for (auto& thread : threads) {
        if(thread.joinable())
            thread.join();
    }







}