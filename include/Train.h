#ifndef CIR2_VAL_TRAIN_H
#define CIR2_VAL_TRAIN_H

#include <iostream>

#include "Terminus.h"

class Train {
private:
    int id;
    double speed;
    Terminus terminus;
    double coordX;
    int nombrePassagers;
    Train* voisin;
    bool arrived;

public:
    /**
     * @brief Contructeur de la classe Train
     * @param id : id du train
     * @param speed : vitesse du train
     * @param terminus : terminus du train
     * @param coordX : coordonnée du train
     * @param nombrePassagers : nombre de passagers dans le train
     * @param arrived : le train est-il arrivé ?
     * @return void
    */
    Train(int id,double speed, const Terminus& terminus, double coordX, int nombrePassagers, bool arrived);

/* ===== GETTER ===== */

    /**
    * @brief Getter de l'id du train
    * @return int : id du train
    */
    int getId() const;

    /**
     * @brief Getter de la vitesse du train
     * @return double : vitesse du train
    */
    double getSpeed() const;

    /**
     * @brief Getter des coordonnées du train
     * @return double : coordonnées du train
    */
    double getCoordX() const;

    /**
     * @brief Getter le terminus du train
     * @return Terminus : terminus du train (le nom)
    */
    Terminus getTerminus() const;

    /**
     * @brief Getter du voisin du train
     * @return Train* : récupérer l'id
     */
    Train* getVoisin() const;

    /**
    * @brief Getter de l'etat d'arrive du train
    * @return bool : le train est arrivé
    */
    bool getState() const;

    /**
     * @biref Getter de la distance entre le train et son voisin
     * @return
     */
    double getDistance() const;

/* ===== SETTER ===== */

    /**
     * @brief Setter de la vitesse du train
     * @param newSpeed : nouvelle vitesse du train
     * @return void
    */
    void setSpeed(const double &newSpeed);

    /**
     * @brief Setter des coordonnées du train
     * @param newCoordX : nouvelle coordonnée du train
     * @return void
    */
    void setCoordX(const double &newCoordX);

    /**
     * @brief Setter du nombre de passagers du train
     * @param deltaPassagers : nombre de passagers à ajouter ou à retirer
     * @return void
    */
    void setPassengers(const int &deltaPassagers);

    /**
     * @brief Setter de l'arrivé
     * @param newState
     * @return void
     */
    void setState(const bool &newState);

    /**
     * @brief Setter du voisin du train
     * @param neighbor
     * @return void
     */
    void setVoisin(Train* neighbor);

    /**
     * @brief ajuster la vitesse du train
     * @param deltaVitesse
     * @return void
     */
    void ajusterVitesse(const double &deltaVitesse);

    /**
    * @brief Vérifie la distance de sécurité
    * @param securiy
    * @return bool
    */
    bool checkSecurityDistance(const int security) {
        if(getDistance() >= security) {
            return true;
        }
        return false;
    }


};

#endif //CIR2_VAL_TRAIN_H