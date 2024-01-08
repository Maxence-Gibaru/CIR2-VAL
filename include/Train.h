#ifndef CIR2_VAL_TRAIN_H
#define CIR2_VAL_TRAIN_H

#include <iostream>
#include <thread>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>
#include <ctime>
#include "Terminus.h"
#include "Station.h"
#include "config.h"

class Train {
private:
    int id;
    double speed;
    Terminus *terminus;
    double coordX;
    double coordY;
    double totalCoordX;
    int passengersNumber;
    Train *voisin{};
    Station *station{};
    float time;
    int passengersCapacity;
    double accelerationDistance;
    bool emergencyStop;
    double wait = 0;
    bool isStopping = false;
    double decelerationDistance;

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
    Train(int id, double speed, float time, Terminus *terminus, double coordX, double totalCoordX, int passengersNumber,
          bool emergencyStop);

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
     * @brief Getter des coordonnées x du train (par rapport à la station)
     * @return double : coordonnées du train
    */
    double getCoordX() const;

    /**
     * @brief Getter des coordonnées en y du train (par rapport à la station)
     * @return double : coordonnées du train
     */
    double getCoordY() const;

    /**
      * @brief Getter des coordonnées totales du train
      * @return double : coordonnées du train
    */
    double getTotalCoordX() const;

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
    double getAccelerationDistance();

    /**
     *@brief Getter retourne vrai si le arret d'urgence est activé
     * @return bool : true or false si le arret d'urgence est activé
     */
    bool getEmergencyStop() const;

    /**
     * @brief Getter du nombre de passagers du train
     * @return int : nombre de passagers du train
    */
    int getPassengers() const;

    double getWait() const;

    void setWait();

    void decreaseWait(double decrement);

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
    void moveX();

/**
     * @brief fais reculer les coordonnées du train
     * @param newCoordX : nouvelle coordonnée du train
     * @return void
    */
    void stopX();

    void restart();

    /**
     * @brief Setter des coordonnées du train
     * @param newCoordX : nouvelle coordonnée du train
     * @return void
    */
    void setCoordX(const double &newCoordX);

    /**
     * @brief Setter des coordonnées du train
     * @param newCoordX : nouvelle coordonnée du train
     * @return void
    */
    void setCoordY(const double &newCoordY);

    /**
     * @brief Setter du nombre de passagers du train
     * @param deltaPassengers : nombre de passagers à ajouter ou à retirer
     * @return void
    */
    void setPassengers(const int &deltaPassengers);

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

    /**
     * @brief Setter de la station du train
     * @param nextStation : prochaine station du train
     * @return void
     */
    void setTime(const float &newTime);

    /**
     * @brief Setter de l'émergency stop true or false
     * @param newState : true or false
     * @return void
     */
    void setEmergencyStop(const bool &newState);


/* ===== METHODS ===== */

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

    /**
     * @brief met à jour les coordonnées totales du train
     */
    void updateTotalCoordX();

    /**
     * @biref ajoute des passagers dans le train
     * @return void
     */
    void addPassengers();

    /**
     * @brief retire des passagers dans le train
     * @return void
     */
    void emptyPassengers();

    /**
     * @biref : Reduce the number of passengers in the train
     * @return void
     */
    void reducePassengers();

};

#endif //CIR2_VAL_TRAIN_H