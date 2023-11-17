//
// Created by maxence on 17/11/23.
//

#ifndef CIR2_VAL_STATION_H
#define CIR2_VAL_STATION_H


class Station {
private:
    int passengers;
    bool isTrain;

public:
    // Getters
    const int getPassengers() const{
        return this->passengers;
    }
};

#endif //CIR2_VAL_STATION_H
