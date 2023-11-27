//
// Created by Ugo WAREMBOURG on 17/11/2023.
//

#include "../include//TrainControlFunction.h"

void setVoisinList(std::vector<Train> &Trains) {
    for (int i = 0; i < Trains.size(); ++i) {
        if (i == Trains.size() - 1) {
            Trains[i].setVoisin(&Trains[0]);
        } else {
            Trains[i].setVoisin(&Trains[i + 1]);
        }


    }
    for (const auto &i: Trains) {
        std::cout << "Train " << i.getId() << " voisin : " << i.getVoisin()->getId() << std::endl;
    }
}

void setFirstStation(std::vector<Station> &Stations, std::vector<Train> &myList) {
    for (auto &train: myList) {
        train.setStation(&Stations[0]);
    }
}

void initNextStation(std::vector<Station> &Stations) {
    for (int i = 0; i < Stations.size(); i++) {
        Stations[i].setNeighbour(&Stations[i + 1]);
    }
}

void initTrains(std::vector<Train> &Trains, Terminus &myTerminus, int n) {
    for (int i = 1; i <= n; i++) {
        Train myTrain(i, 0.0, 0.0, &myTerminus, 0.0, 0.0, 10, false);
        Trains.push_back(myTrain);
    }
}



