//
// Created by Ugo WAREMBOURG on 15/11/2023.
//

#ifndef CIR2_PROJET_VAL_TERMINUS_H
#define CIR2_PROJET_VAL_TERMINUS_H
#include <string>

class Terminus {
private:
    std::string nom;

public:
    Terminus(const std::string& nom);

    std::string getNom() const;
};

#endif //CIR2_PROJET_VAL_TERMINUS_H