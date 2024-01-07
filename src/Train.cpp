#include "Train.h"

double REFRESH = 0.01;

Train::Train(int id, double speed, float time, Terminus *terminus, double coordX, double totalCoordX,
             int passengersNumber, bool emergencyStop)
        : id(id), speed(speed), time(time), terminus(terminus), coordX(coordX), totalCoordX(totalCoordX),
          passengersNumber(passengersNumber), passengersCapacity(MAX_PASSENGERS_CAPACITY),
          emergencyStop(emergencyStop) {
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


double Train::getDistance() const {
    if (getVoisin()->getId() == getId()) {
        return DISTANCE_SECURITY;
    }
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

bool Train::getEmergencyStop() const {
    return this->emergencyStop;
}


double Train::getWait() const {
    return wait;
}

void Train::decreaseWait(double decrement) {
    if (wait > 0) {
        wait -= decrement;
        if (wait < 0) {
            wait = 0;
        }
    }
}

void Train::setWait(double secondes) {
    wait = secondes;
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

void Train::setEmergencyStop(const bool &newState) {
    this->emergencyStop = newState;
}

/* ==== OTHER ==== */


// à faire
void Train::stopX() {
    isStopping = true;

    decelerationDistance = pow(speed, 2) / (2 * DECELERATION_COEFF);

}

void Train::moveX() {
    this->time += REFRESH;
    double NEW_MAX_SPEED = sqrt(
            (getNextStation()->getCoordX(getTerminus()->getDirection()) - getTotalCoordX()) * COEFF_SPEED);
    double time1 = MAX_SPEED / COEFF_SPEED;
    double time2 = (getNextStation()->getCoordX(getTerminus()->getDirection()) - getTotalCoordX()) / MAX_SPEED;

    if (isStopping) {
        if (decelerationDistance > 0 and speed > 0) {
            coordX += speed * REFRESH - 0.5 * DECELERATION_COEFF * pow(REFRESH, 2);
            speed -= DECELERATION_COEFF * REFRESH;

            // Assurez-vous que la vitesse ne devient pas négative
            if (speed < 0) {
                speed = 0;
            }

            // Mettre à jour la distance de décélération restante
            decelerationDistance -= speed * REFRESH;
        } else {
            // Le train est complètement arrêté

            speed = 0; // Assurez-vous que la vitesse est bien à 0
            return;
        }
    } else {
        if (fullSpeed()) {
            if (coordX <= getAccelerationDistance()) {
                this->coordX = 0.5 * COEFF_SPEED * pow(this->time, 2);
                this->speed = COEFF_SPEED * time;
            }

            if (coordX > getAccelerationDistance() and
                getCoordX() < getNextStation()->getCoordX(getTerminus()->getDirection()) - getTotalCoordX()) {
                this->coordX = MAX_SPEED * (this->time - time1) + 0.5 * COEFF_SPEED * pow(time1, 2);
                this->speed = MAX_SPEED;
            }

            if (coordX >= (getNextStation()->getCoordX(getTerminus()->getDirection()) - getTotalCoordX()) -
                          getAccelerationDistance()) {
                this->coordX =
                        -0.5 * COEFF_SPEED * pow(this->time - time2, 2) + MAX_SPEED * (this->time - time2) +
                        MAX_SPEED * (time2 - time1) +
                        0.5 * COEFF_SPEED * pow(time1, 2);
                this->speed = -COEFF_SPEED * (time - time2) + MAX_SPEED;
            }
        } else {
            time1 = NEW_MAX_SPEED / COEFF_SPEED;
            if (coordX < getAccelerationDistance()) {
                this->coordX = 0.5 * COEFF_SPEED * pow(this->time, 2);
                this->speed = COEFF_SPEED * time;
            }

            if (coordX >= (getNextStation()->getCoordX(getTerminus()->getDirection()) - getTotalCoordX()) -
                          getAccelerationDistance()) {
                this->coordX = -0.5 * COEFF_SPEED * pow(this->time - time1, 2) + NEW_MAX_SPEED * (this->time - time1) +
                               0.5 * COEFF_SPEED * pow(time1, 2);
                this->speed = -COEFF_SPEED * (time - time1) + NEW_MAX_SPEED;
            }
        }
    }
}


void Train::restart() {
    isStopping = false;

    speed = 0;
}


bool Train::trainArrived() const {
    if (round(getCoordX() + getTotalCoordX()) == getTerminus()->getCoordT()) {
        if (PRINT) {
            std::cout << "Le train n°" << getId() << " est arrivé au terminus : " << getTerminus()->getNom()
                      << std::endl;
        }
        return true;
    }
    return false;
}

bool Train::checkSecurityDistance() const {


    if (getDistance() >= DISTANCE_SECURITY or getTerminus() != getVoisin()->getTerminus()) {
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
        if (PRINT) {
            std::cout << "Arrêt du train " << getId() << " à la gare " << getNextStation()->getNom() << std::endl;
        }
        return true;
    }
    return false;
}

bool Train::fullSpeed() const {
    double highestDistance = pow(MAX_SPEED, 2) / COEFF_SPEED;
    if (highestDistance <= (getNextStation()->getCoordX(getTerminus()->getDirection()) - getTotalCoordX())) {
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
    std::cout << "Train n°" << getId() << " : distance |" << getCoordX() + getTotalCoordX() << " m |" << std::endl;
    std::cout << "Voisin : " << getVoisin()->getId() << std::endl;
    std::cout << "Terminus : " << getTerminus()->getNom() << std::endl;
    std::cout << "Passagers train : " << getPassengers() << std::endl;
    std::cout << "VOISIN : " << getVoisin()->getId() << std::endl;
    std::cout << "DISTANCE : " << getDistance() << std::endl;
}

void Train::reducePassengers() {
    if (passengersNumber <= 0) {
        return;
    }
    int random = rand() % 5 * getNextStation()->getCoefficientPopularite();
    while (passengersNumber > 0 && random > 0) {
        passengersNumber--;
        random--;
    }
}

void Train::addPassengers() {
    while (passengersNumber < MAX_PASSENGERS_CAPACITY && station->getPassengers(getTerminus()->getDirection()) > 0) {
        station->reducePassengers(1, getTerminus()->getDirection());
        passengersNumber++;
    }
}

int Train::getPassengers() const {
    return passengersNumber;
}

void Train::emptyPassengers() {
    passengersNumber = 0;
}

