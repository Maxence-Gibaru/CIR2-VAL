//
// Created by Ugo WAREMBOURG on 17/11/2023.
//

#include "../include//TrainControlFunction.h"

int setVoisinList(std::vector<Train> &myList) {
    for (int i = 0; i < myList.size(); ++i) {
        if (i > 0) {
            myList[i].setVoisin(&myList[i - 1]);
        } else {

            myList[i].setVoisin(&myList[myList.size() - 1]);
        }
    }
}