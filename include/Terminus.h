#include <string>

#ifndef CIR2_PROJET_VAL_TERMINUS_H
#define CIR2_PROJET_VAL_TERMINUS_H

class Terminus {
private:
    std::string nom;
    int train_number;
    int coordT;
    bool direction;
    Terminus * nextTerminus;

public:
    /**
     * Constructeur de la classe Terminus
     * @param nom : nom du terminus
     * @param train_number : nombre de train ayant atteint le terminus
     * @param coordT : coordonnées du terminus
     * @param nextTerminus : prochain terminus
    */
    Terminus(const std::string& nom, int train_number, int coordT, bool direction);

/* ===== GETTER ===== */

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

    /**
     * @brief Getter des coordonnées du terminus
     * @return int : coordonnées du terminus
    */
    const int getCoordT() const;

    /**
     * @brief Getter du prochain terminus
     * @return Terminus* : prochain terminus
    */
    Terminus * getNextTerminus() const;

    bool getDirection() const;

/* ===== SETTER ===== */

    /**
     * @brief Setter du prochain terminus
     * @param nextTerminus : prochain terminus
     * @return void
    */
    void setNextTerminus(Terminus* nextTerminus) ;

    /**
     * @brief Incrémente le nombre de train ayant atteint le terminus
     * @return void
    */
    void addTrainNumber() {
        this->train_number += 1;
    }

};

#endif //CIR2_PROJET_VAL_TERMINUS_H