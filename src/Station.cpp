#include "../include/Station.h"
#include <string>

Station::Station(const std::string &nom, int id, int passengers, bool presence, std::tuple<double, double> coordX,
                 double coefficientPopularite) : nom(nom), id(id), passengers(passengers), presence(presence),
                                                 coordX(coordX), coefficientPopularite(coefficientPopularite) {}

/* ==== GETTERS ==== */

const double Station::getCoordX(bool direction) const {
    if (direction) {
        return std::get<0>(this->coordX);
    } else {
        return std::get<1>(this->coordX);
    }
}

const int Station::getPassengers() const {
    return this->passengers;
}

const std::string Station::getNom() const {
    return this->nom;
}

Station *Station::getNeighbour() const {
    return this->neighbour;
}

Station *Station::getPreviousNeighbour() const {
    return this->previousNeighbour;
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

void Station::setPreviousNeighbour(Station *newNeighbour) {
    this->previousNeighbour = newNeighbour;
}
