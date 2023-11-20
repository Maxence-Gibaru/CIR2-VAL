#include "../include/Train.h"

Train::Train(int id,double speed, const Terminus& terminus, double coordX, int nombrePassagers, bool arrived)
        : id(id),speed(speed), terminus(terminus), coordX(coordX), nombrePassagers(nombrePassagers), arrived(arrived)
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

bool Train::getState() const {
    return this->arrived;
}

double Train::getDistance() const {
    if (getCoordX() == 0) {
        return 0;
    }
    return std::abs(this->coordX - this->voisin->getCoordX());
}

Station * Train::getStation() const {
    return this->nearestStation;
}


/* ==== SETTERS ==== */

void Train::setCoordX(const double &newCoordX) {
    this->coordX = newCoordX;
}

void Train::setVoisin(Train* neighbor) {
    voisin = neighbor;
}

void Train::setTerminus(Terminus &newTerminus) {
    this->terminus = newTerminus;
}

void Train::setSpeed(const double &newSpeed) {
    this->speed = newSpeed;
}

void Train::setState(const bool &newState) {
    this->arrived = newState;
}

void Train::setPassengers(const int &deltaPassagers){
    this->nombrePassagers += deltaPassagers;
    if (this->nombrePassagers < 0) {
        std::cerr << "Passengers negatif" << std::endl;
        this->nombrePassagers = 0;
    }
}

void Train::setStation(Station *nearestStation) {
    this->nearestStation = nearestStation;
}

/* ==== OTHER ==== */

void Train::moveX(const double &newCoordX) {
    this->coordX += newCoordX;
}


void Train::addSpeed(const double &deltaSpeed) {
    this->speed += deltaSpeed;
    if (this->speed < 0.0) {
        std::cerr << "Vitesse negatif" << std::endl;
        this->speed = 0.0;
    }
}

void Train::subSpeed(const double &deltaSpeed) {
    this->speed -= deltaSpeed;
    if (this->speed < 0.0) {
        std::cerr << "Vitesse negatif" << std::endl;
        this->speed = 0.0;
    }
}

double Train::getDistanceStation(const Station* station) const {
    return std::abs(this->coordX - station->getCoordX()); // à finir
}














