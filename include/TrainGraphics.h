//include <SFML/Graphics.hpp>
#include "Train.h"
#include <string>


#ifndef CIR2_VAL_TRAINGRAPHICS_H
#define CIR2_VAL_TRAINGRAPHICS_H

#define WIDTH 1920.0
#define HEIGHT 1080.0

#define HIGH 400.0
#define LOW 600.0
#define MID 500.0

struct SharedData {
    std::vector<Train> *Trains;
    std::vector<Station> Stations;
    std::tuple<int, int, int> heure;
    bool emergencyStop;
};

//int renderVisuals(sf::RenderWindow &window, SharedData &sharedData);


#endif //CIR2_VAL_TRAINGRAPHICS_H
