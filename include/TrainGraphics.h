#include <SFML/Graphics.hpp>
#include "Train.h"
#include <string>


#ifndef CIR2_VAL_TRAINGRAPHICS_H
#define CIR2_VAL_TRAINGRAPHICS_H

#define WIDTH 1920.0
#define HEIGHT 1080.0

#define HIGH 150.0
#define LOW 350.0
#define MID 250.0

struct SharedData {
    std::vector<Train> *Trains;
    std::vector<Station> Stations;
    std::tuple<int, int, int> heure;
    bool isOpen;
    bool emergencyStop;
};

int renderVisuals(sf::RenderWindow &window, SharedData &sharedData);


#endif //CIR2_VAL_TRAINGRAPHICS_H
