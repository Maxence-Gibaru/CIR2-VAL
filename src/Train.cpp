#include "../include/Train.h"

Train::Train() {
    this->passengers = 0;
    this->speed = 0;
}

Train::Train(int index) {
    this->index = index;
    this->speed = 0;
    this->passengers = 0;
}

const float Train::getSpeed() const {
    return this->speed;
}

const int Train::getPassengers() const {
    return this->passengers;
}

const int Train::getIndex() const {
    return this->index;
}

void Train::setSpeed(const int &newSpeed) {
    this->speed += newSpeed;
}

void Train::setPassengers(int &newPassengers) {
    this->passengers = newPassengers;
}










