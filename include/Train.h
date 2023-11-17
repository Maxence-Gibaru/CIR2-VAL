#ifndef CIR2_VAL_TRAIN_H
#define CIR2_VAL_TRAIN_H

#include "Terminus.h"
#include <string>
#include <iostream>

class Train {
private:
    double speed;
    Terminus terminus;
    double coordX;
    int nombrePassagers;
    std::string assetVisuel;

public:
    Train(double speed, const Terminus& terminus, double coordX, int nombrePassagers, const std::string& assetVisuel);

    double getSpeed() const;
    double getCoordX() const;
    Terminus getTerminus() const;

    void setSpeed(const double &newSpeed);
    void setCoordX(const double &newCoordX);
    void setPassengers(const int &deltaPassagers);
    void ajusterVitesse(const double &deltaVitesse);

};

#endif //CIR2_VAL_TRAIN_H