#include "Train.h"

Train::Train(int id, double speed, float time, Terminus *terminus, double coordX, double totalCoordX,
             int passengersNumber, bool arrived)
        : id(id), speed(speed), time(time), terminus(terminus), coordX(coordX), totalCoordX(totalCoordX),
          passengersNumber(passengersNumber),
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

double Train::getCoordY() const {
    return this->coordY;
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
    return std::abs((this->voisin->getCoordX()) + this->voisin->getTotalCoordX() - ((this->coordX) + getTotalCoordX()));
}

Station *Train::getNextStation() const {
    return this->station;
}

double Train::getDistanceStation() const {
    double distance = getNextStation()->getCoordX(getTerminus()->getDirection()) - getTotalCoordX() - this->coordX;
    return std::abs(distance);
}

double Train::getAccelerationDistance() {
    if (fullSpeed()) {
        this->accelerationDistance = pow(MAX_SPEED, 2) / (2 * COEFF_SPEED);
    } else {
        this->accelerationDistance =
                pow(sqrt((getNextStation()->getCoordX(getTerminus()->getDirection()) - getTotalCoordX()) * COEFF_SPEED),
                    2) / (2 * COEFF_SPEED);
    }
    return this->accelerationDistance;
}

double Train::getTotalCoordX() const {
    return this->totalCoordX;
}

/* ==== SETTERS ==== */

void Train::setCoordX(const double &newCoordX) {
    this->coordX = newCoordX;
}

void Train::setCoordY(const double &newCoordY) {
    this->coordY = newCoordY;
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
    if (getTerminus()->getDirection()) {
        this->station = getNextStation()->getNeighbour();
    } else {
        this->station = getNextStation()->getPreviousNeighbour();
    }

}

void Train::setStation(Station *nextStation) {
    this->station = nextStation;
}

void Train::setTime(const double &newTime) {
    this->time = newTime;
}

void Train::updateTotalCoordX() {
    this->totalCoordX += this->coordX;
}

/* ==== OTHER ==== */

// globalise args
void Train::moveX() {
    // fonction super important à optimiser !!!!
    this->time += REFRESH;
    double NEW_MAX_SPEED = sqrt(
            (getNextStation()->getCoordX(getTerminus()->getDirection()) - getTotalCoordX()) * COEFF_SPEED);
    double time1 = MAX_SPEED / COEFF_SPEED;
    double time2 = (getNextStation()->getCoordX(getTerminus()->getDirection()) - getTotalCoordX()) / MAX_SPEED;

    if (fullSpeed()) {
        if (coordX <= getAccelerationDistance()) {
            //std::cout << "ACCELERATION" << std::endl;
            this->coordX = 0.5 * COEFF_SPEED * pow(this->time, 2);
        }

        if (coordX > getAccelerationDistance() and
            getCoordX() < getNextStation()->getCoordX(getTerminus()->getDirection()) - getTotalCoordX()) {
            //std::cout << "CONSTANT" << std::endl;
            this->coordX = MAX_SPEED * (this->time - time1) + 0.5 * COEFF_SPEED * pow(time1, 2);
        }

        if (coordX >= (getNextStation()->getCoordX(getTerminus()->getDirection()) - getTotalCoordX()) -
                      getAccelerationDistance()) {
            //std::cout << "DECELERATION" << std::endl;
            this->coordX =
                    -0.5 * COEFF_SPEED * pow(this->time - time2, 2) + MAX_SPEED * (this->time - time2) +
                    MAX_SPEED * (time2 - time1) +
                    0.5 * COEFF_SPEED * pow(time1, 2);
        }
    } else {
        time1 = NEW_MAX_SPEED / COEFF_SPEED;
        if (coordX < getAccelerationDistance()) {
            //std::cout << "ACCELERATION" << std::endl;
            this->coordX = 0.5 * COEFF_SPEED * pow(this->time, 2);
        }

        if (coordX >= (getNextStation()->getCoordX(getTerminus()->getDirection()) - getTotalCoordX()) -
                      getAccelerationDistance()) {
            //std::cout << "DECELERATION" << std::endl;
            this->coordX = -0.5 * COEFF_SPEED * pow(this->time - time1, 2) + NEW_MAX_SPEED * (this->time - time1) +
                           0.5 * COEFF_SPEED * pow(time1, 2);
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
    if (round(getCoordX() + getTotalCoordX()) == getTerminus()->getCoordT()) {
        std::cout << "Train terminus" << std::endl;
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
    setTime(0.0);
    this->totalCoordX = 0.0;
}

bool Train::trainStationArrived() const {
    if (round(getCoordX() + getTotalCoordX()) == getNextStation()->getCoordX(getTerminus()->getDirection())) {
        std::cout << "Arrêt du train " << getId() << " à la gare " << getNextStation()->getNom() << std::endl;
        return true;
    }
    return false;
}

bool Train::fullSpeed() const {
    if (highestDistance <= (getNextStation()->getCoordX(getTerminus()->getDirection()) - getTotalCoordX())) {
        return true;
    }
    return false;
}

void Train::updateSpeed() {
    if (fullSpeed()) {
        if (getCoordX() < getAccelerationDistance()) {
            addSpeed(REFRESH);
        }
        if (getCoordX() >= (getNextStation()->getCoordX(getTerminus()->getDirection()) - getTotalCoordX()) -
                           getAccelerationDistance() and
            getSpeed() > 0) {
            subSpeed(REFRESH);
        }
    } else {
        {
            if (getCoordX() < getAccelerationDistance() and getSpeed() < MAX_SPEED) {
                addSpeed(REFRESH);
            }
            if (getCoordX() >= (getNextStation()->getCoordX(getTerminus()->getDirection()) - getTotalCoordX()) -
                               getAccelerationDistance() and
                getSpeed() > 0) {
                subSpeed(REFRESH);
            }
        }
    }
}


void Train::print() const {

    std::cout << "------------------------------------------------------------------------" << std::endl;
    std::cout << "SECONDS : " << time << std::endl;
    std::cout << "Arrive dans : " << getDistanceStation() << " m " << "à la station " << getNextStation()->getNom()
              << std::endl;
    std::cout << "Speed : " << getSpeed() << " m/s " << std::endl;
    std::cout << "Train n°" << getId() << " : distance |" << getCoordX() + getTotalCoordX() << " m |" << std::endl;
    std::cout << "Voisin : " << getVoisin()->getId() << std::endl;
    std::cout << "Terminus : " << getTerminus()->getNom() << std::endl;
    std::cout << "Passagers station : " << getNextStation()->getPassengers() << std::endl;
    std::cout << "Passagers train : " << getPassengers() << std::endl;

    std::cout << "DISTANCE : " << getDistance() << std::endl;
}

void Train::reducePassengers() {
    if (passengersNumber <= 0) {
        return;
    }

    int random = rand() % (passengersNumber / 2 + 1);
    while (passengersNumber > 0 && random > 0) {
        passengersNumber--;
        random--;
    }
}


void Train::addPassengers() {
    while (passengersNumber < MAX_PASSENGERS_CAPACITY && station->getPassengers() > 0) {
        station->setPassengers(station->getPassengers() - 1);
        passengersNumber++;

    }
}

int Train::getPassengers() const {

    return passengersNumber;

}




















