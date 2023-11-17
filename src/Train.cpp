#include "../include/Train.h"

Train::Train(int id,double speed, const Terminus& terminus, double coordX, int nombrePassagers)
        : id(id),speed(speed), terminus(terminus), coordX(coordX), nombrePassagers(nombrePassagers)
{}

/* ==== GETTERS ==== */

double Train::getSpeed() const {
    return this->speed;
}

int Train::getId() const {
    return this->id;
}

double Train::getCoordX() const {
    return this->coordX;
}

Terminus Train::getTerminus() const {
    return this->terminus;
}

Train* Train::getVoisin() const {
    return voisin;
}

double Train::getDistance() const {
    if (getCoordX() == 0) {
        std::cout << "Le train est au terminus" << std::endl;
        return 0;
    }
    return std::abs(this->coordX - this->voisin->getCoordX());
}

/* ==== SETTERS ==== */

void Train::setCoordX(const double &newCoordX) {
    this->coordX += newCoordX;
}

void Train::setVoisin(Train* neighbor) {
    voisin = neighbor;
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

/* ==== OTHER ==== */

void Train::ajusterVitesse(const double &deltaVitesse) {
    this->speed += deltaVitesse;
    if (this->speed < 0.0) {
        std::cerr << "Vitesse negatif" << std::endl;
        this->speed = 0.0;
    }
}





