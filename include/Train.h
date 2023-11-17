#ifndef CIR2_VAL_TRAIN_H
#define CIR2_VAL_TRAIN_H


class Train {
private:
    int speed;
    int passengers;
    int index;


public:
    // Constructors implementation
    Train();
    Train(int index);

    // Getters
    const int getPassengers() const;
    const float getSpeed() const;
    const int getIndex() const;

    // Setters
    void setPassengers(int &newPassengers);
    void setSpeed(const int &newSpeed);


};





#endif //CIR2_VAL_TRAIN_H
