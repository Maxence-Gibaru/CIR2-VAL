//
// Created by ugo on 06/12/23.
//

#ifndef CIR2_VAL_HEURE_H
#define CIR2_VAL_HEURE_H

#include <iostream>
#include <ctime>
#include <iomanip>
#include <unistd.h>

#include <iostream>
#include <ctime>
#include <iomanip> // Pour std::setw
#include <unistd.h>

class Heure {
private:
    int heures;
    int minutes;
    int secondes;
    int millisecondes;
    int microsecondes;

public:
    Heure() {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        heures = ltm->tm_hour;
        minutes = ltm->tm_min;
        secondes = ltm->tm_sec;
        millisecondes = 0;
        microsecondes = 0;
    }

    void afficherHeure() {
        std::cout << "Il est : "
                  << std::setw(2) << std::setfill('0') << heures << ":"
                  << std::setw(2) << std::setfill('0') << minutes << ":"
                  << std::setw(2) << std::setfill('0') << secondes << ":"
                  << std::setw(3) << std::setfill('0') << millisecondes << ":"
                  << std::setw(3) << std::setfill('0') << microsecondes << std::endl;
    }

    void incrementerTemps(double refresh) {
        int delayMicroseconds = static_cast<int>(refresh * 1000); // Convertir les millisecondes en microsecondes

        for (int i = 0; i < 1000; i += delayMicroseconds) {
            microsecondes += delayMicroseconds;
            if (microsecondes >= 1000) {
                microsecondes -= 1000;
                millisecondes++;
                if (millisecondes >= 1000) {
                    millisecondes -= 1000;
                    secondes++;
                    if (secondes >= 60) {
                        secondes = 0;
                        incrementerMinute();
                    }
                }
            }
        }
    }

    void incrementerMinute() {
        minutes++;
        if (minutes >= 60) {
            minutes = 0;
            incrementerHeure();
        }
    }

    void incrementerHeure() {
        heures++;
        if (heures >= 24) {
            heures = 0;
        }
    }

    void remiseAZero() {
        heures = 0;
        minutes = 0;
        secondes = 0;
        millisecondes = 0;
        microsecondes = 0;
    }


    const std::tuple<int, int, int> getTime() const;
};




#endif //CIR2_VAL_HEURE_H
