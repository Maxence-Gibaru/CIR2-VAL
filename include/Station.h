#include <string>
#include <random>
#include <iostream>
#include <tuple>

#ifndef CIR2_VAL_STATION_H
#define CIR2_VAL_STATION_H


class Station {
private:
    std::string nom;
    int id;
    std::tuple<int, int> passengers;
    bool presence;
    std::tuple<double, double> coordX;
    double coefficientPopularite;
    Station *neighbour{};
    Station *previousNeighbour{};


public:
    /**
     * @brief Constructeur de la classe Station
     * @param nom : nom de la station
     * @param id : identifiant de la station
     * @param passengers : nombre de passagers dans la station
     * @param presence : présence d'un train dans la station
     * @param coordX : coordonnées X de la station
     * @param neighbour : station voisine
    */
    Station(const std::string &nom, int id, std::tuple<int, int> passengers, bool presence,
            std::tuple<double, double> coordX, double coefficientPopularite);

/* ===== GETTER ===== */

    /**
     *  @brief Getter du nombre de passagers dans la station
     *  @return int : nombre de passagers dans la station
    */
    const int getPassengers(bool direction) const;

    /**
     * @brief Getter des coordonnées X de la station
     * @return double : coordonnées X de la station
    */
    const double getCoordX(const bool direction) const;

    /**
     * @brief getter du Nom de la station
     * @return string : nom de la station
    */
    const std::string getNom() const;

    /**
     * @brief getter de la station voisine
     * @return Station* : station voisine
    */
    Station *getNeighbour() const;

    /**
     * @brief getter de la station précédente
     * @return Station* : station précédente
    */
    Station *getPreviousNeighbour() const;

    /**
     * @brief getter de l'identifiant de la station
     * @return int : identifiant de la station
    */
    const int getId() const;

    /**
     * @brief getter du coefficient de popularité de la station
     * @return double : coefficient de popularité de la station
    */
    double getCoefficientPopularite() const;

/* ===== SETTER ===== */

    /**
     * @brief Setter du nombre de passagers dans la station
     * @param newPassengers : nouveau nombre de passagers dans la station
    */
    void setPassengers(const int &newPassengers,bool direction);

    /**
     * @brief Setter de la station voisine
     * @param newNeighbour : nouvelle station voisine
    */
    void setNeighbour(Station *newNeighbour);

    /**
     * @brief Setter de la station précédente
     * @param newNeighbour : nouvelle station précédente
     */
    void setPreviousNeighbour(Station *newNeighbour);

    /**
     * @brief Ajouter des passagers dans la station
     * @param direction : direction du train (true = droite, false = gauche) Dissocier station aller retour
     */
    void addPassengers(bool direction);

    /**
     * @brief Retirer des passagers de toute les stations
     * @return void : rien
     */
    void emptyPassengers();

    void reducePassengers(const int &newPassengers,bool direction);

};

#endif //CIR2_VAL_STATION_H
