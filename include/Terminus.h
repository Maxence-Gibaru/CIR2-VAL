//
// Created by Ugo WAREMBOURG on 15/11/2023.
//

#ifndef CIR2_PROJET_VAL_TERMINUS_H
#define CIR2_PROJET_VAL_TERMINUS_H
#include <string>

class Terminus {
private:
    std::string nom;
    int train_number;

public:
    Terminus(const std::string& nom, int train_number);

    std::string getNom() const;
    const int getTrainNumber() const;

    void addTrainNumber() {
        this->train_number += 1;
    }
};

#endif //CIR2_PROJET_VAL_TERMINUS_H