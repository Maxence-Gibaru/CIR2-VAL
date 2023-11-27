#include "../include/Station.h"
#include <string>

Station::Station(const std::string &nom, int id,int passengers, bool presence, double coordX) : nom(nom), id(id), passengers(passengers), presence(presence), coordX(coordX) {}

/* ==== GETTERS ==== */

const double Station::getCoordX() const {
    return this->coordX;
}

const int Station::getPassengers() const {
    return this->passengers;
}

const std::string Station::getNom() const {
    return this->nom;
}

Station* Station::getNeighbour() const {
    return this->neighbour;
}

const int Station::getId() const {
    return this->id;
}

/* ==== SETTERS ==== */

void Station::setPassengers(const int &newPassengers) {
    this->passengers = newPassengers;
}

void Station::setPresence(const bool &newPresence) {
    this->presence = newPresence;
}

void Station::setNeighbour(Station *newNeighbour) {
        this->neighbour = newNeighbour;
    }

