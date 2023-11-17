//
// Created by maxence on 15/11/23.
//

#include "../include/Train.h"

Train::Train(double vitesse, const Terminus& terminus, double distanceTerminus, int nombrePassagers, const std::string& assetVisuel)
        : vitesse(vitesse), terminus(terminus), distanceTerminus(distanceTerminus), nombrePassagers(nombrePassagers), assetVisuel("") {}

double Train::getVitesse() const {
    return vitesse;
}

void Train::setVitesse(double nouvelleVitesse) {
    vitesse = nouvelleVitesse;
}

Terminus Train::getTerminus() const {
    return terminus;
}

void Train::ajusterPassagers(int deltaPassagers) {
    nombrePassagers += deltaPassagers;
    if (nombrePassagers < 0) {
        std::cerr << "Bro bouge" << std::endl;
        nombrePassagers = 0;
    }
}

void Train::ajusterVitesse(double deltaVitesse) {
    vitesse += deltaVitesse;
    if (vitesse < 0.0) {
        std::cerr << "Tu forces" << std::endl;
        vitesse = 0.0;
    }
}