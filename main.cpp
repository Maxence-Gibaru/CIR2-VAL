#include <SFML/Graphics.hpp>
#include <iostream>
#include "include/Train.h"
#include <array>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include <algorithm>

using namespace std::chrono_literals;




void fillTab(std::vector<Train> &myList, Train &train) {
    myList.push_back(train);
}

int main()
{
    std::vector<std::thread> threads(10);
    std::vector<Train> myList;

    Train myTrain1(1);
    Train myTrain2(2);

    myList.push_back(myTrain1);
    myList.push_back(myTrain2);

    // number max of threads

    bool stopping = false;

    for(int i = 0; i < myList.size(); i++) {
        threads.emplace_back(
                [&myList, i, &stopping](){
                    while(!stopping) {
                        std::cout << myList[i].getIndex() << std::endl;
                        std::this_thread::sleep_for(1s);

                    }
                });
    }


    for (auto& thread : threads) {
        if(thread.joinable())
            thread.join();
    }







}