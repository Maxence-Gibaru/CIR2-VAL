#include <thread>
#include <vector>
#include <cmath>
#include "Terminus.h"
#include "Train.h"
#include "Station.h"
#include "TrainControlFunction.h"
#include "TrainGraphics.h"
#include <string>
#include "data.h"

#define DISPLAY true

int TRAIN_NUMBER_LINE_1 = 2;
int TRAIN_NUMBER_LINE_2 = 2;

double DISTANCE_SECURITY = 1000;


// Main function
int main(void) {
    // Shared data among threads
    SharedData sharedData;
    bool stop_working = false;
    std::thread renderThread;

    // Thread for rendering visuals
    if (DISPLAY) {
        renderThread = std::thread([&sharedData]() {
            sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Train Simulator");
            renderVisuals(window, sharedData);
        });
    }

    // Vector definition
    std::mutex mtx_;
    std::vector<std::thread> threads;

    std::vector<Train> Trains;
    std::vector<Station> Stations;
    std::vector<Terminus> Line;

    Line.reserve(dataTerminus.size());
    for (auto &data: dataTerminus) {
        Line.emplace_back(std::get<0>(data), std::get<1>(data), std::get<2>(data), std::get<3>(data));
    }

    // Implementation of Stations
    Stations.reserve(dataStations.size());
    for (auto &data: dataStations) {
        Stations.emplace_back(std::get<0>(data), std::get<1>(data), std::get<2>(data), std::get<3>(data),
                              std::get<4>(data), std::get<5>(data));
    }

    // Definition of trains
    initTrains(Trains, Line, TRAIN_NUMBER_LINE_1);

    // Set each train's neighbour to each other
    setVoisinList(Trains);

    // Set each station next station to each other
    initNextStation(Stations, &Line[1]);

    // Initialise the first station of each train
    for (auto &train: Trains) {
        setStation(Stations, train, true);
    }

    //Set the next Terminus of each other
    Line[1].setNextTerminus(&Line[0]);
    Line[0].setNextTerminus(&Line[1]);

    Heure temps;
    // launch a thread for each train
    threads.reserve(Trains.size());
    for (auto &train: Trains) {
        threads.emplace_back(manageSubway, std::ref(sharedData), std::ref(train), std::ref(Trains), std::ref(Stations),
                             std::ref(mtx_), std::ref(stop_working), std::ref(temps));
    }

    // Wait for all threads to finish
    for (auto &thread: threads) {
        if (thread.joinable())
            thread.join();
    }

    // Wait for rendering thread to finish if applicable
    if (DISPLAY and renderThread.joinable()) {
        renderThread.join();
    }

    return 0;
}