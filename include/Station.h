#include <string>

#ifndef CIR2_VAL_STATION_H
#define CIR2_VAL_STATION_H

class Station {
private:
    std::string nom;
    int id;
    int passengers;
    bool presence;
    double coordX;
    Station *neighbour;

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
    Station(const std::string &nom, int id, int passengers, bool presence, double coordX);

/* ===== GETTER ===== */

    /**
     *  @brief Getter du nombre de passagers dans la station
     *  @return int : nombre de passagers dans la station
    */
    const int getPassengers() const;

    /**
     * @brief Getter des coordonnées X de la station
     * @return double : coordonnées X de la station
    */
    const double getCoordX() const;

    /**
     * @brief getter du Nom de la station
     * @return string : nom de la station
    */
    const std::string getNom() const;

    /**
     * @brief getter de la station voisine
     * @return Station* : station voisine
    */
    Station* getNeighbour() const;

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
     * @brief Setter de la présence d'un train dans la station
     * @param newPresence : nouvelle présence d'un train dans la station
    */
    void setPresence(const bool &newPresence);

    /**
     * @brief Setter de la station voisine
     * @param newNeighbour : nouvelle station voisine
    */
    void setNeighbour(Station * newNeighbour);

    /**
    * @brief Setter du nombre de passagers dans la station
    * @param newCoordX : nouveau nombre de passagers dans la station
    */
    void setCoordX(const double &newCoordX);


};

#endif //CIR2_VAL_STATION_H
