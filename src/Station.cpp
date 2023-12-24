#include "../include/Station.h"
#include <string>

Station::Station(const std::string &nom, int id, std::tuple<int, int> passengers, bool presence,
                 std::tuple<double, double> coordX,
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

const int Station::getPassengers(bool direction) const {
    if (direction) {
        return std::get<0>(this->passengers);
    } else {
        return std::get<1>(this->passengers);
    }
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

void Station::setPassengers(const int &newPassengers,bool direction) {
    if (direction) {
        std::get<0>(this->passengers) = newPassengers;
    } else {
        std::get<1>(this->passengers) = newPassengers;
    }

}

void Station::reducePassengers(const int &newPassengers,bool direction) {
    if (direction) {
        std::get<0>(this->passengers) -= newPassengers;
    }

    else {
        std::get<1>(this->passengers) -= newPassengers;
    }

}


void Station::addPassengers(bool direction) {
    int random = rand() % 20;
    if (direction) {
        std::get<0>(this->passengers) += random * coefficientPopularite;
    } else {
        std::get<1>(this->passengers) += random * coefficientPopularite;
    }
    std::cout << random << "ont été ajoutés à la station " << this->getNom() << std::endl;

}

void Station::setNeighbour(Station *newNeighbour) {
    this->neighbour = newNeighbour;
}

void Station::setPreviousNeighbour(Station *newNeighbour) {
    this->previousNeighbour = newNeighbour;
}


double Station::getCoefficientPopularite() const {
    return coefficientPopularite;
}

void Station::emptyPassengers() {

    std::get<0>(this->passengers) = 0;
    std::get<1>(this->passengers) = 0;

}

