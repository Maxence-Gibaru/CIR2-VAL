#include <string>

#ifndef CIR2_PROJET_VAL_TERMINUS_H
#define CIR2_PROJET_VAL_TERMINUS_H

/**
 * @brief Classe représentant un terminus
*/
class Terminus {
private:
    std::string nom;
    int train_number;
    int coordT;

public:
    /**
     * Constructeur de la classe Terminus
     * @param nom : nom du terminus
     * @param train_number : nombre de train ayant atteint le terminus
     * @return void
    */
    Terminus(const std::string& nom, int train_number, int coordT);

    /**
     * @brief Getter du nom du terminus
     * @return std::string : nom du terminus
    */
    std::string getNom() const;

    /**
     * @brief Getter du nombre dans le terminus
     * @return int : nombre de train ayant atteint le terminus
    */
    const int getTrainNumber() const;

    const int getCoordT() const;

    /**
     * @brief Incrémente le nombre de train ayant atteint le terminus
     * @return void
    */
    void addTrainNumber() {
        this->train_number += 1;
    }

};

#endif //CIR2_PROJET_VAL_TERMINUS_H