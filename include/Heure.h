#ifndef HEURE_H
#define HEURE_H

#include <iostream>
#include <ctime>
#include <iomanip>
#include <unistd.h>
#include <tuple>
#include <thread>
#include <chrono>
#include "Train.h"
#include "Station.h"

class Heure {
private:
    int heures;
    int minutes;
    int secondes;
    int millisecondes;
    int microsecondes;

public:
    /**
     * @brief Constructeur de la classe Heure
     * @param heures : heures
     * @param minutes : minutes
     * @param secondes : secondes
     * @param millisecondes : millisecondes
     * @param microsecondes : microsecondes
    */
    Heure();

/* ===== GETTER ===== */

    /**
     * @brief Getter de l'heure
     * @return tuple<int, int, int> : heures, minutes, secondes
     */
    std::tuple<int, int, int> getTime() const;

    /**
     * @brief Getter des heures
     * @return int : heures
     */
    int getHeures() const;

    /**
     * @brief Getter des minutes
     * @return int : minutes
     */

    int getMinutes() const;

    /**
     * @brief Getter des secondes
     * @return int : secondes
     */
    int getSecondes() const;

    /**
     * @brief Getter des millisecondes
     * @return int : millisecondes
     */
    int getMillisecondes() const;

    /**
     * @brief Getter des microsecondes
     * @return int : microsecondes
     */
    int getMicrosecondes() const;


    /**
     * @brief Affiche l'heure
     * @return void
    */
    void afficherHeure() const;

    /**
     * @brief Incrémente le temps
     * @param refresh
     * @return void
    */
    void incrementerTemps(double refresh);

    /**
     * @biref Incrémenter les minutes
     * @return void
     */
    void incrementerMinute();

    /**
     * @brief Incrémenter les heures
     * @return void
     */
    void incrementerHeure();

    /**
     * Remise à zéro de l'heure
     * @return void
     */
    void remiseAZero();

};

/**
 * @brief Function that manages the passing time
 * @param train: train
 * @param temps: time variable from the Heure class
 * @param Stations: list of stations
 */
void ManageTime(Heure &temps, bool &stopWorking, std::mutex &mtxTemps);


#endif // HEURE_H
