#include "../include/Train.h"

Train::Train(int id, double speed, float time, Terminus *terminus, double coordX, int passengersNumber, bool arrived)
        : id(id), speed(speed), time(time), terminus(terminus), coordX(coordX), passengersNumber(passengersNumber),
          arrived(arrived), passengersCapacity(MAX_PASSENGERS_CAPACITY) {
}

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

Terminus *Train::getTerminus() const {
    return this->terminus;
}

Train *Train::getVoisin() const {
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

Station *Train::getNextStation() const {
    return this->station;
}

double Train::getDistanceStation() const {
    double distance = getNextStation()->getCoordX() - this->coordX;
    return std::abs(distance);
}

double Train::getAccelerationDistance() {
    if (fullSpeed()) {
        this->accelerationDistance = pow(MAX_SPEED, 2) / (2 * COEFF_SPEED);
    } else {
        this->accelerationDistance = pow(sqrt(getNextStation()->getCoordX() * COEFF_SPEED), 2) / (2 * COEFF_SPEED);
    }
    return this->accelerationDistance;
}

/* ==== SETTERS ==== */

void Train::setCoordX(const double &newCoordX) {
    this->coordX = newCoordX;
}

void Train::setVoisin(Train *neighbor) {
    voisin = neighbor;
}

void Train::setTerminus(Terminus *newTerminus) {
    this->terminus = newTerminus;
}

void Train::setSpeed(const double &newSpeed) {
    this->speed = newSpeed;
}

void Train::setState(const bool &newState) {
    this->arrived = newState;
}

void Train::setPassengers(const int &deltaPassengers) {
    this->passengersNumber += deltaPassengers;
    if (this->passengersNumber < 0) {
        std::cerr << "Passengers negatif" << std::endl;
        this->passengersNumber = 0;
    }
}

void Train::setNextStation() {
    this->station = getNextStation()->getNeighbour();
}

void Train::setStation(Station *nextStation) {
    this->station = nextStation;
}

/* ==== OTHER ==== */

// globalise args
void Train::moveX(double d1, double t1, double t2) {
    this->time += REFRESH;
    double NEW_MAX_SPEED = sqrt(getNextStation()->getCoordX() * COEFF_SPEED);


    if(fullSpeed()) {
        if (coordX <= d1) {
            std::cout << "ACCELERATION" << std::endl;
            this->coordX = 0.5 * COEFF_SPEED * pow(this->time, 2);
        }

        if (coordX > d1 and getCoordX() < getNextStation()->getCoordX()) {
            std::cout << "CONSTANT" << std::endl;
            this->coordX = MAX_SPEED * (this->time - t1) + 0.5 * COEFF_SPEED * pow(t1, 2);
        }

        if (coordX >= getNextStation()->getCoordX() - d1) {
            std::cout << "DECELERATION" << std::endl;
            this->coordX =
                    -0.5 * COEFF_SPEED * pow(this->time - t2, 2) + MAX_SPEED * (this->time - t2) + MAX_SPEED * (t2 - t1) +
                    0.5 * COEFF_SPEED * pow(t1, 2);
        }
    } else {
        t1 = NEW_MAX_SPEED / COEFF_SPEED;
        if (coordX < d1) {
            std::cout << "ACCELERATION" << std::endl;
            this->coordX = 0.5 * COEFF_SPEED * pow(this->time, 2);
        }

        if (coordX >= getNextStation()->getCoordX() - d1) {
            std::cout << "DECELERATION" << std::endl;
            this->coordX = -0.5 * COEFF_SPEED * pow(this->time - t1, 2) + NEW_MAX_SPEED * (this->time - t1) + 0.5 * COEFF_SPEED * pow(t1, 2);
        }
    }

}

void Train::addSpeed(double refresh) {
    this->speed += COEFF_SPEED * refresh;
    if (this->speed < 0.0) {
        std::cerr << "Vitesse negatif" << std::endl;
        this->speed = 0.0;
    }
}

void Train::subSpeed(double refresh) {
    this->speed -= COEFF_SPEED * refresh;
    if (this->speed < 0.0) {
        std::cerr << "Vitesse negatif" << std::endl;
        this->speed = 0.0;
    }
}

bool Train::trainArrived() const {
    if (getCoordX() == getTerminus()->getCoordT()) {
        return true;
    }
    return false;
}

bool Train::checkSecurityDistance() const {
    if (getDistance() >= DISTANCE_SECURITY) {
        return true;
    }
    return false;
}

void Train::swapTerminus() {
    setTerminus(getTerminus()->getNextTerminus());
    setCoordX(0);
}

bool Train::trainStationArrived() const {
    if (round(getCoordX()) == getNextStation()->getCoordX()) {
        std::cout << "Arrêt du train " << getId() << " à la gare " << getNextStation()->getNom() << std::endl;
        return true;
    }
    return false;
}

bool Train::fullSpeed() const {
    if (highestDistance <= getNextStation()->getCoordX()) {
        return true;
    }
    return false;
}

void Train::print() const {

    std::cout << "------------------------------------------------------------------------" << std::endl;
    std::cout << "SECONDS : " << time << std::endl;
    std::cout << "Arrive dans : " << getDistanceStation() << " m " << "à la station " << getNextStation()->getNom()
              << std::endl;
    std::cout << "Speed : " << getSpeed() << " m/s " << std::endl;
    std::cout << "Train n°" << getId() << " : distance |" << getCoordX() << " m |" << std::endl;
    std::cout << "Voisin : " << getVoisin()->getId() << std::endl;
    std::cout << "Terminus : " << getTerminus()->getNom() << std::endl;
}



















