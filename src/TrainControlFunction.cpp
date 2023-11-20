//
// Created by Ugo WAREMBOURG on 17/11/2023.
//

#include "../include//TrainControlFunction.h"

void setVoisinList(std::vector<Train> &myList) {
    for (int i = 0; i < myList.size(); ++i) {
        if (i == myList.size() - 1) {
            std::cout << "SEXE" << std::endl;
            myList[i].setVoisin(&myList[0]);
        } else {
            myList[i].setVoisin(&myList[i + 1]);
        }


    }
    for (const auto & i : myList) {
        std::cout << "Train " << i.getId() << " voisin : " << i.getVoisin()->getId() << std::endl;
    }
}

void setNearestStation(std::vector<Station> &Stations, std::vector<Train> &myList) {
    double nearest = Stations[0].getCoordX();

    for(auto &station: Stations) {
        for(auto &train: myList) {
            if(train.getDistanceStation(&station) <= nearest) {
                train.setStation(&station);
            }
        }
    }
}


