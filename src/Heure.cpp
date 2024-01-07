#include "Heure.h"

Heure::Heure() {
    heures = 7;
    minutes = 0;
    secondes = 0;
    millisecondes = 0;
    microsecondes = 0;
}

int Heure::getHeures() const {
    return heures;
}

int Heure::getMinutes() const {
    return minutes;
}

int Heure::getSecondes() const {
    return secondes;
}

int Heure::getMillisecondes() const {
    return millisecondes;
}

int Heure::getMicrosecondes() const {
    return microsecondes;
}

void Heure::afficherHeure() const {
    std::cout << "Il est : "
              << std::setw(2) << std::setfill('0') << heures << ":"
              << std::setw(2) << std::setfill('0') << minutes << ":"
              << std::setw(2) << std::setfill('0') << secondes << ":"
              << std::setw(3) << std::setfill('0') << millisecondes << ":"
              << std::setw(3) << std::setfill('0') << microsecondes << std::endl;
}

void Heure::incrementerTemps(double refresh) {
    // Convert to milliseconds.
    int delayMilliseconds = static_cast<int>(refresh * 1000);

    // Add the delay to the current time.
    millisecondes += delayMilliseconds;

    // Increment the time.
    while (millisecondes >= 1000) {
        millisecondes -= 1000;
        secondes++;
        if (secondes >= 60) {
            secondes = 0;
            incrementerMinute();
        }
    }
}

void Heure::incrementerMinute() {
    minutes++;
    if (minutes >= 60) {
        minutes = 0;
        incrementerHeure();
    }
}

void Heure::incrementerHeure() {
    heures++;
    if (heures >= 24) {
        heures = 0;
    }
}

void Heure::remiseAZero() {
    heures = 0;
    minutes = 0;
    secondes = 0;
    millisecondes = 0;
    microsecondes = 0;
}

std::tuple<int, int, int> Heure::getTime() const {
    return std::make_tuple(heures, minutes, secondes);
}
