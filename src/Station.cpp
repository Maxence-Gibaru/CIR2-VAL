#include "../include/Station.h"
#include <string>

Station::Station(const std::string &nom, int id,int passengers, bool presence, double coordX) : nom(nom), id(id), passengers(passengers), presence(presence), coordX(coordX) {}

const double Station::getCoordX() const {
    return this->coordX;
}

const int Station::getPassengers() const {
    return this->passengers;
}

const std::string Station::getNom() const {
    return this->nom;
}

void Station::setPassengers(const int &newPassengers) {
    this->passengers = newPassengers;
}

void Station::setPresence(const bool &newPresence) {
    this->presence = newPresence;
}

void Station::setNeighbour(Station *newNeighbour) {
        this->neighbour = newNeighbour;
    }

Station* Station::getNeighbour() const {
    return this->neighbour;
}
