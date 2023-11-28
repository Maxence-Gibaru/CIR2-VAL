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

void setStation(std::vector<Station> &Stations, std::vector<Train> &myList, bool first) {
    // à changer, ne marche que pour un seul train
    for (auto &train: myList) {
        if (train.getTerminus()->getDirection()) {
            train.setStation(&Stations[1]);
            if (!first) {
                for (auto &station: Stations) {
                    station.setCoordX(DISTANCE_TOT - station.getCoordX());
                }
            }
        } else {
            train.setStation(&Stations[Stations.size() - 2]);
            for (auto &station: Stations) {
                station.setCoordX(DISTANCE_TOT - station.getCoordX());
            }
        }
    }

}

void initNextStation(std::vector<Station> &Stations, Terminus *myTerminus) {
    for (int i = 0; i < Stations.size(); i++) {
        if (myTerminus->getDirection()) {
            Stations[i].setNeighbour(&Stations[i + 1]);
        } else {
            Stations[i].setNeighbour(&Stations[i - 1]);
        }
    }
}


void initTrains(std::vector<Train> &Trains, Terminus &myTerminus, int n) {
    for (int i = 1; i <= n; i++) {
        Train myTrain(i, 0.0, 0.0, &myTerminus, 0.0, 0.0, 10, false);
        Trains.push_back(myTrain);
    }
}



