#ifndef CIR2_PROJET_VAL_TRAIN_H
#define CIR2_PROJET_VAL_TRAIN_H

#include "Terminus.h"
#include <string>
#include <iostream>

class Train {
private:
    double vitesse;
    Terminus terminus;
    double distanceTerminus;
    int nombrePassagers;
    std::string assetVisuel;

public:
    Train(double vitesse, const Terminus& terminus, double distanceTerminus, int nombrePassagers, const std::string& assetVisuel);

    double getVitesse() const;
    void setVitesse(double nouvelleVitesse);
    Terminus getTerminus() const;
    void ajusterPassagers(int deltaPassagers);
    void ajusterVitesse(double deltaVitesse);

};

#endif //CIR2_PROJET_VAL_TRAIN_H