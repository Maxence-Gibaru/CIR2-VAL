#include "../include/Station.h"
#include <string>

Station::Station(const std::string &nom, std::tuple<int, int> passengers, bool terminusState,
                 std::tuple<double, double> coordX,
                 double coefficientPopularite) : nom(nom), passengers(passengers), terminusState(terminusState),
                                                 coordX(coordX), coefficientPopularite(coefficientPopularite) {}

/* ==== GETTERS ==== */

double Station::getCoordX(bool direction) const {
    if (direction) {
        return std::get<0>(this->coordX);
    } else {
        return std::get<1>(this->coordX);
    }
}

int Station::getPassengers(bool direction) const {
    if (direction) {
        return std::get<0>(this->passengers);
    } else {
        return std::get<1>(this->passengers);
    }
}

std::string Station::getNom() const {
    return this->nom;
}

Station *Station::getNeighbour() const {
    return this->neighbour;
}

Station *Station::getPreviousNeighbour() const {
    return this->previousNeighbour;
}

bool Station::isTerminus() const {
    return this->terminusState;
}

/* ==== SETTERS ==== */

void Station::setPassengers(const int &newPassengers, bool direction) {
    if (direction) {
        std::get<0>(this->passengers) = newPassengers;
    } else {
        std::get<1>(this->passengers) = newPassengers;
    }

}

void Station::reducePassengers(const int &newPassengers, bool direction) {
    if (direction) {
        std::get<0>(this->passengers) -= newPassengers;
    } else {
        std::get<1>(this->passengers) -= newPassengers;
    }

}

void Station::addPassengers(bool direction) {
    int random = rand() % 12;
    if (direction) {
        std::get<0>(this->passengers) += random * coefficientPopularite;
    } else {
        std::get<1>(this->passengers) += random * coefficientPopularite;
    }
    if (PRINT) {
        std::cout << random << " personnes ont rejoient la station !" << this->getNom() << std::endl;
    }

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

void Station::emptyPassengers(bool direction) {
    if (direction) {
        std::get<0>(this->passengers) = 0;

    } else {
        std::get<1>(this->passengers) = 0;
    }
}


