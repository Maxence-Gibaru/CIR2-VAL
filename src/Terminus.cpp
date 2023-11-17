//
// Created by Ugo WAREMBOURG on 15/11/2023.
//

#include "../include/Terminus.h"

Terminus::Terminus(const std::string& nom) : nom(nom) {}

std::string Terminus::getNom() const {
    return nom;
}