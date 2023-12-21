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

    Station *getPreviousNeighbour() const;

    /**
     * @brief getter de l'identifiant de la station
     * @return int : identifiant de la station
    */
    const int getId() const;

/* ===== SETTER ===== */

    /**
     * @brief Setter du nombre de passagers dans la station
     * @param newPassengers : nouveau nombre de passagers dans la station
    */
    void setPassengers(const int &newPassengers);

    /**
     * @brief Setter de la station voisine
     * @param newNeighbour : nouvelle station voisine
    */
    void setNeighbour(Station *newNeighbour);

    void setPreviousNeighbour(Station *newNeighbour);

    /*
    void reducePassengers(int reductionAmount);
*/
    double getCoefficientPopularite() const;

    void addPassengers(bool direction);
};

#endif //CIR2_VAL_STATION_H
