#ifndef CIR2_VAL_TRAIN_H
#define CIR2_VAL_TRAIN_H

#include <iostream>

#include "Terminus.h"
#include "Station.h"

class Train {
private:
    int id;
    double speed;
    Terminus terminus;
    double coordX;
    int nombrePassagers;
    Train* voisin;
    Station* station;
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

    Station * getNextStation() const;

    double getDistanceStation(const Station * station) const;

/* ===== SETTER ===== */

    /**
     * @brief Setter de la vitesse du train
     * @param newSpeed : nouvelle vitesse du train
     * @return void
    */
    void setSpeed(const double &newSpeed);

    /**
     * @brief fais avancer les coordonnées du train
     * @param newCoordX : nouvelle coordonnée du train
     * @return void
    */
    void moveX(const double &newCoordX);

    void setCoordX(const double &newCoordX);

    /**
     * @brief Setter du nombre de passagers du train
     * @param deltaPassengers : nombre de passagers à ajouter ou à retirer
     * @return void
    */
    void setPassengers(const int &deltaPassengers);

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

    void setTerminus(Terminus &newTerminus);

    void setStation(Station *nextStation);


    /**
     * @brief ajuster la vitesse du train
     * @param deltaSpeed
     * @return void
     */
    void addSpeed(const double &deltaSpeed);

    void subSpeed(const double &deltaSpeed);

    /**
    * @brief Vérifie la distance de sécurité
    * @param securiy
    * @return bool
    */
    bool checkSecurityDistance(const int security) const {
        if(getDistance() >= security) {
            return true;
        }
        return false;
    }
};

#endif //CIR2_VAL_TRAIN_H