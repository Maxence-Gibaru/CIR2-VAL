#include "Heure.h"



const std::tuple<int, int, int> Heure::getTime() const {
    return {this->heures, this->minutes, this->secondes};
}



