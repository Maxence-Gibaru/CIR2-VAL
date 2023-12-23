#ifndef HEURE_H
#define HEURE_H

#include <iostream>
#include <ctime>
#include <iomanip>
#include <unistd.h>
#include <tuple>

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

    /**
     * @brief Affiche l'heure
     * @return void
    */
    void afficherHeure() const;

    /**
     * @brief Incrémente le temps
     * @param refresh
    */
    void incrementerTemps(double refresh);


    void incrementerMinute();
    void incrementerHeure();
    void remiseAZero();
    const std::tuple<int, int, int> getTime() const;
};

#endif // HEURE_H
