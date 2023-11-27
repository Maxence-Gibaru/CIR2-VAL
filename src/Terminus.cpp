//
// Created by Ugo WAREMBOURG on 15/11/2023.
//

#include "../include/Terminus.h"

Terminus::Terminus(const std::string &nom, int train_number, int coordT) : nom(nom), train_number(train_number),
                                                                           coordT(coordT) {}

/* ==== GETTERS ==== */

std::string Terminus::getNom() const {
    return nom;
}

const int Terminus::getTrainNumber() const {
    return this->train_number;
}

const int Terminus::getCoordT() const {
    return this->coordT;
}

Terminus *Terminus::getNextTerminus() const {
    return this->nextTerminus;
}

/* ==== SETTERS ==== */

void Terminus::setNextTerminus(Terminus* newTerminus) {
    this->nextTerminus = newTerminus;
}