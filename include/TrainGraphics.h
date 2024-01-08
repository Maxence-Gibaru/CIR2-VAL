#ifndef CIR2_VAL_TRAINGRAPHICS_H
#define CIR2_VAL_TRAINGRAPHICS_H

#include <SFML/Graphics.hpp>
#include <string>
#include "TrainControlFunction.h"
#include "Train.h"

#define WIDTH 1920.0
#define HEIGHT 1080.0

#define HIGH 150.0
#define LOW 350.0
#define MID 250.0

struct SharedData {
    std::vector<Train> *Trains1;
    std::vector<Station> Stations1;
    std::vector<Train> *Trains2;
    std::vector<Station> Stations2;
    std::tuple<int, int, int> heure;
    bool isOpen;
    bool emergencyStop;

public:
    void
    updateData(int lineId_data, bool &isOpen_data, std::vector<Train> &Trains_data, std::vector<Station> &Stations_data,
               std::tuple<int, int, int> hour_data) {
        isOpen = isOpen_data; // Updates shared data with station status
        heure = hour_data; // Updates shared data with current time
        ; // Updates shared data with train information
        if (lineId_data == 0) {
            Trains1 = &Trains_data;
            Stations1 = Stations_data;
        } else {
            Trains2 = &Trains_data;
            Stations2 = Stations_data;
        }
    }


};

/**
 * @brief Render the visuals of the metro
 * @param window : window of the metro
 * @param sharedData : data shared between threads
 * @return 0 if rendered successfully
 */
int renderVisuals(sf::RenderWindow &window, SharedData &sharedData);

#endif //CIR2_VAL_TRAINGRAPHICS_H
