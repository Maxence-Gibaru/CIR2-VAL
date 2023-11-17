//
// Created by maxence on 15/11/23.
//

#include "../include/Train.h"

Train::Train(double vitesse, const Terminus& terminus, double distanceTerminus, int nombrePassagers, const std::string& assetVisuel)
        : vitesse(vitesse), terminus(terminus), distanceTerminus(distanceTerminus), nombrePassagers(nombrePassagers), assetVisuel("") {}

double Train::getVitesse() const {
    return this->vitesse;
}

void Train::setVitesse(double nouvelleVitesse) {
    this->vitesse = nouvelleVitesse;
}

Terminus Train::getTerminus() const {
    return this->terminus;
}

void Train::ajusterPassagers(int deltaPassagers) {
    this->nombrePassagers += deltaPassagers;
    if (this->nombrePassagers < 0) {
        std::cerr << "Passengers negatif" << std::endl;
        this->nombrePassagers = 0;
    }
}

void Train::ajusterVitesse(double deltaVitesse) {
    this->vitesse += deltaVitesse;
    if (this->vitesse < 0.0) {
        std::cerr << "Vitesse negatif" << std::endl;
        this->vitesse = 0.0;
    }
}