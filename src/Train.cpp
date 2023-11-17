#include "../include/Train.h"

Train::Train(double speed, const Terminus& terminus, double coordX, int nombrePassagers, const std::string& assetVisuel)
        : speed(speed), terminus(terminus), coordX(coordX), nombrePassagers(nombrePassagers), assetVisuel("") {}

double Train::getSpeed() const {
    return this->speed;
}

double Train::getCoordX() const {
    return this->coordX;
}

Terminus Train::getTerminus() const {
    return this->terminus;
}


void Train::setSpeed(const double &newSpeed) {
    this->speed = newSpeed;
}

void Train::setPassengers(const int &deltaPassagers){
    this->nombrePassagers += deltaPassagers;
    if (this->nombrePassagers < 0) {
        std::cerr << "Passengers negatif" << std::endl;
        this->nombrePassagers = 0;
    }
}

void Train::ajusterVitesse(const double &deltaVitesse) {
    this->speed += deltaVitesse;
    if (this->speed < 0.0) {
        std::cerr << "Vitesse negatif" << std::endl;
        this->speed = 0.0;
    }
}

void Train::setCoordX(const double &newCoordX) {
    this->coordX += newCoordX;
}

