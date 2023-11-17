//
// Created by Ugo WAREMBOURG on 15/11/2023.
//

#include "../include/Terminus.h"

Terminus::Terminus(const std::string& nom, int train_number) : nom(nom), train_number(train_number) {}

/* ==== GETTERS ==== */

std::string Terminus::getNom() const {
    return nom;
}

const int Terminus::getTrainNumber() const {
    return this->train_number;
}
