#include "../include/Station.h"
#include <string>

// aussi vide que mes poches

Station::Station(const std::string &nom, int passengers, bool presence, double coordX) : nom(nom), passengers(passengers), presence(presence), coordX(coordX) {}

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
