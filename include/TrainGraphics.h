#include <SFML/Graphics.hpp>
#include "Train.h"

#ifndef CIR2_VAL_TRAINGRAPHICS_H
#define CIR2_VAL_TRAINGRAPHICS_H

#define WIDTH 1920
#define HEIGHT 1080

struct SharedData {
    std::vector<Train> Trains;
    std::vector<Station> Stations;
};

int renderVisuals(sf::RenderWindow &window, SharedData &sharedData);


#endif //CIR2_VAL_TRAINGRAPHICS_H
