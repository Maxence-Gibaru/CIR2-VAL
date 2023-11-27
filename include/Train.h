#ifndef CIR2_VAL_TRAIN_H
#define CIR2_VAL_TRAIN_H

#include <iostream>
#include <cmath>
#include "Terminus.h"
#include "Station.h"

#define COEFF_SPEED 1.0
#define MAX_SPEED 23.0
#define DISTANCE_SECURITY 300
#define MAX_PASSENGERS_CAPACITY 200
#define REFRESH 1

class Train {
private:
    int id;
    double speed;
    Terminus *terminus;
    double coordX;
    int passengersNumber;
    Train *voisin{};
    Station *station{};
    bool arrived;
    float time;
    int passengersCapacity;
    double accelerationDistance;

public:
    /**
     * @brief Contructeur de la classe Train
     * @param id : id du train
     * @param speed : vitesse du train
     * @param time : temps de parcours du train
     * @param terminus : terminus du train
     * @param coordX : coordonnée du train
     * @param passengersNumber : nombre de passagers dans le train
     * @param arrived : le train est-il arrivé ?
     * @param accelerationDistance : distance que met le train jusqu'à sa vitesse max
     * @return void
    */
    Train(int id, double speed, float time, Terminus *terminus, double coordX, int passengersNumber, bool arrived);

    double highestDistance = pow(MAX_SPEED, 2) / COEFF_SPEED;

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
    Terminus *getTerminus() const;

    /**
     * @brief Getter du voisin du train
     * @return Train* : récupérer l'id
     */
    Train *getVoisin() const;

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

    /**
     * @brief getter de la prochaine station ou le train va arriver
     * @return Station* : prochaine station ( pointe sur la station suivante )
    */
    Station *getNextStation() const;

    /**
     * @brief Getter de la distance entre le train et la station
     * @return double : distance entre le train et la station
    */
    double getDistanceStation() const;

    /**
  * @brief Getter de la distance d'acceleration
  * @return double : distance d'acceleration
 */
    double getAccelerationDistance() ;

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
    void moveX(double d1, double t1, double t2);

    /**
     * @brief Setter des coordonnées du train
     * @param newCoordX : nouvelle coordonnée du train
     * @return void
    */
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
    void setVoisin(Train *neighbor);

    /**
     * @brief Setter du terminus du train
     * @param newTerminus : nouveau terminus du train
     * @return void
     */
    void setTerminus(Terminus *newTerminus);

    /**
     * @brief Setter de la station du train
     * @return void
     */
    void setNextStation();

    /**
     * @brief Setter de la station du train
     * @param nextStation : prochaine station du train
     * @return void
     */
    void setStation(Station *nextStation);


/* ===== METHODS ===== */

    /**
     * @brief ajuster la vitesse du train
     * @param refresh
     * @return void
     */
    void addSpeed(double refresh);

    void subSpeed(double refresh);

    /**
    * @brief Vérifie la distance de sécurité
    * @return bool, true si la distance de sécurité est respectée
    */
    bool checkSecurityDistance() const;

    /**
     * @brief Vérifie si le train est arrivé
     * @return bool, true si le train est arrivé
     */
    bool trainArrived() const;

    /**
     * @brief change le terminus du train
     * @return void
     */
    void swapTerminus();

    /**
     * @brief verifie si le train est arrivé à la station
     * @return bool, true si le train est arrivé à la station
     */
    bool trainStationArrived() const;

    /**
     * @brief print les informations du train
     */
    void print() const;

    /**
     * @brief verifie si le train est arrivé à la station
     * @return bool, true si le train est arrivé à la station
     */
    bool fullSpeed() const;

};

#endif //CIR2_VAL_TRAIN_H