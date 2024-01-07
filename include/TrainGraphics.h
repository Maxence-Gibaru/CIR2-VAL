#ifndef CIR2_VAL_TRAINGRAPHICS_H
#define CIR2_VAL_TRAINGRAPHICS_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Train.h"

#define WIDTH 1920.0
#define HEIGHT 1080.0

#define HIGH 150.0
#define LOW 350.0
#define MID 250.0

struct SharedData {
    std::vector<Train> Trains1;
    std::vector<Station> Stations1;
    std::vector<Train> Trains2;
    std::vector<Station> Stations2;
    std::tuple<int, int, int> heure;
    bool isOpen;
    bool emergencyStop;
};

int renderVisuals(sf::RenderWindow &window, SharedData &sharedData);


#endif //CIR2_VAL_TRAINGRAPHICS_H
