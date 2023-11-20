//
// Created by Ugo WAREMBOURG on 17/11/2023.
//

#include "../include//TrainControlFunction.h"

int setVoisinList(std::vector<Train> &myList) {
    for (int i = 0; i < myList.size(); ++i) {
        if (i == myList.size() - 1) {
            std::cout << "SEXE" << std::endl;
            myList[i].setVoisin(&myList[0]);
        } else {
            myList[i].setVoisin(&myList[i + 1]);
        }


    }
    for (int i = 0; i < myList.size(); ++i) {
        std::cout << "Train " << myList[i].getId() << " voisin : " << myList[i].getVoisin()->getId() << std::endl;
    }
}
