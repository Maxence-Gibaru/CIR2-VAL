
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <cmath>
#include "Terminus.h"
#include "Train.h"
#include "Station.h"
#include "TrainControlFunction.h"
#include "TrainGraphics.h"
#include <string>
#include <ctime>
#include <cstdlib>



#define TRAIN_NUMBER 1
#define WIDTH 1920
#define HEIGHT 1080


using namespace std::chrono_literals;

/*
 * TODO
 * - [x] Gérer l'accélération d'une station à une autre
 * - [X] Gérer les distance parcourues entre chaque train
 * - [ ] Implémenter les heures de la journée
 * - [ ] Mixer Terminus et Station, héritage ??
 *   [ ] lier la vitesse avec la fonction train.move()
 * - [ ] Implémenter les passagers avec temps d'arrêts aux stations
 * - [ ] Optimisation et cleanage du code
 * - [ ] adaptation des vitesses et temps d'arrêt en fonction de la distance de sécurité
 * - [ ] création du visuel avec la lib SFML
 * - [ ] adapter la structure pour le visuel
 */


struct SharedData {
    double coordX;
    double coordY;
};
/*
// Fonction de rendu visuel SFML
int renderVisuals(sf::RenderWindow &window, SharedData &sharedData) {
    while (window.isOpen()) {
        window.clear(sf::Color::White);
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Load an image file from a file
        sf::Image background;
        if (!background.loadFromFile("flashbackmetro.jpeg"))
            return -1;
        // Background sprite

        sf::RectangleShape rectangle;
        rectangle.setSize(sf::Vector2f(1800, 900));
        rectangle.setOutlineColor(sf::Color::Red);
        rectangle.setOutlineThickness(5);
        rectangle.setPosition(50, 50);

        // Load a sprite to display
        sf::Texture texture;
        if (!texture.loadFromFile("spr_train_0.png")) {
            return EXIT_FAILURE;
        }
        sf::Sprite sprite(texture);

        sprite.setPosition(sharedData.coordX * WIDTH/DISTANCE_TOT, sharedData.coordY);
        sprite.setScale(0.5, 0.5);
        window.draw(rectangle);
        window.draw(sprite);



        // display the render
        window.display();
    }
}
*/
int main() {
    srand(time(nullptr));
    SharedData sharedData;

    //sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Train Simulator");




    //std::thread renderThread(renderVisuals, std::ref(window), std::ref(sharedData));


    //display();

    // Vector definition
    std::mutex mtx_;
    std::vector<std::thread> threads;
    std::vector<Train> Trains;
    std::vector<Station> Stations;
    // display stations

    std::vector<Terminus> Line;

    // make function that globalises the process


    // Implementation of Terminus
    std::vector<std::tuple<std::string, int, double, bool>> dataTerminus = {
            {"CHU-Eurasanté", 0, DISTANCE_TOT, 0},
            {"4 Cantons",     0, DISTANCE_TOT, 1}
    };

    for (auto &data: dataTerminus) {
        Line.emplace_back(std::get<0>(data), std::get<1>(data), std::get<2>(data), std::get<3>(data));
    }

    std::vector<std::tuple<std::string, int, int, bool, double,double>> dataStations = {
            {"Terminus CHU",          2, 0,  false, 0, 1.1},
            {"Porte des Postes",      1, 10, false, 100, 1.1},
            {"Wazemmes",              1, 10, false, 500, 1.1},
            {"Gambetta",              1, 10, false, 1100, 1.1},
            {"République Beaux-Arts", 1, 10, false, 1900, 1.1},
            {"Rihour",                2, 10, false, 2500, 1.1},
            {"Lille FLandres",        2, 10, false, 2900, 1.1},
            {"Terminus CANTONS",      2, 0,  false, DISTANCE_TOT, 1.1}
    };

// Implementation of Stations
    for (auto &data: dataStations) {
        Stations.emplace_back(
                std::get<0>(data),
                std::get<1>(data),
                std::get<2>(data),
                std::get<3>(data),
                std::get<4>(data),
                std::get<5>(data));
    }


    // Definition of trains
    initTrains(Trains, Line[1], TRAIN_NUMBER);

    // Set each train's neighbour to each other
    setVoisinList(Trains);

    // Set each station next station to each other
    initNextStation(Stations, &Line[1]);

    // Initialise the first station of each train
    setStation(Stations, Trains, 1);

    //Set the next Terminus of each other
    // !!! OPTI
    Line[1].setNextTerminus(&Line[0]);
    Line[0].setNextTerminus(&Line[1]);

    bool stopping = false; // gérer la boucle while en fonction du temps

    // launch a thread for each train
    for (auto &train: Trains) {
        threads.emplace_back(
                [&sharedData, &mtx_, &train, &Trains, &stopping, &Stations]() mutable -> auto {
                    while (!stopping) {
                        /* ===== MOVE ===== */



                        // make those 2 "if" one
                        if (train.getId() == 1) {

                            // graphics data
                            if (train.getTerminus()->getDirection()) {
                                sharedData.coordX = train.getCoordX() + train.getTotalCoordX();
                                sharedData.coordY = 50;
                            } else {
                                sharedData.coordX = DISTANCE_TOT - train.getTotalCoordX() - train.getCoordX();
                                sharedData.coordY = 900;
                            }



                            train.moveX();
                        }

                        // faire en sorte que le cas getId == Trains.size() soit enlevé, c'est nul à chier
                        if (train.checkSecurityDistance() and train.getId() != Trains.size()) {
                            train.getVoisin()->moveX();
                        }

                        /* ===== SPEED ===== */

                        // en vrai c'est totalement indépendant mdrr
                        train.updateSpeed();


                        /* ===== MANAGE ===== */

                        //  !!! put everything in a single function

                        if (train.trainStationArrived() and
                            round(train.getNextStation()->getCoordX()) != round(train.getTerminus()->getCoordT())) {

                            std::cout << "Train n°" << train.getId() << " à la gare " << train.getNextStation()->getNom() << std::endl;
                            std::cout << "Passagers station : " << train.getNextStation()->getPassengers() << std::endl;
                            std::cout << "Passagers train : " << train.getPassengers() << std::endl;
                            train.addPassengers();
                            train.reducePassengers();
                            std::cout << "Passagers station : " << train.getNextStation()->getPassengers() << std::endl;
                            std::cout << "Passagers train : " << train.getPassengers() << std::endl;
                            std::this_thread::sleep_for(5s);
                            train.getNextStation()->addPassengers();




                            train.setNextStation();
                            train.updateTotalCoordX();
                            // make a reset function
                            train.setCoordX(0);
                            train.setTime(0.0);
                        }

                        // When a train arrive, it swaps to another terminus in the other direction
                        if (train.trainArrived()) {
                            train.swapTerminus();
                            setStation(Stations, Trains, 0);
                            initNextStation(Stations, train.getTerminus());
                            train.setPassengers(-train.getPassengers());
                            std::cout << "nb passagers" << train.getPassengers() << std::endl;
                        }

                        /* ===== DETAILS ===== */

                        mtx_.lock();
                        train.print();
                        mtx_.unlock();

                        // delay between threads
                        std::this_thread::sleep_for(1s);
                        std::cout << std::endl;
                    }
                });
    }

    //renderThread.join();

    for (auto &thread: threads) {
        if (thread.joinable())
            thread.join();
    }

    return 0;
}