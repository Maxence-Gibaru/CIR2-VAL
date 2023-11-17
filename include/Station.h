//
// Created by maxence on 17/11/23.
//

#ifndef CIR2_VAL_STATION_H
#define CIR2_VAL_STATION_H


class Station {
private:
    int passengers;
    bool presence;

public:
    // Getters
    const int getPassengers() const{
        return this->passengers;
    }
    const bool isTrain() const{
        return this->presence;
    };

    // Setters
    void setPassengers(const int &newPassengers) {
        this->passengers = newPassengers;
    }
    void setPresence(bool &newPresence) {
        this->presence = newPresence;
    }

};

#endif //CIR2_VAL_STATION_H
