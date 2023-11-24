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

/* ===== CONSTRUCTOR ===== */

    Station(const std::string &nom, int id, int passengers, bool presence, double coordX);


/* ===== GETTER ===== */

    /**
     *  @brief Getter du nombre de passagers dans la station
     *  @return int : nombre de passagers dans la station
    */
    const int getPassengers() const;

    const double getCoordX() const;

    const std::string getNom() const;

    Station* getNeighbour() const;

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

    void setNeighbour(Station * newNeighbour);

};

#endif //CIR2_VAL_STATION_H
