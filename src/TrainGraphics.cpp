#include "TrainGraphics.h"
#include <SFML/Graphics.hpp>


// Fonction de rendu visuel SFML
int renderVisuals(sf::RenderWindow &window, SharedData &sharedData) {
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return EXIT_FAILURE;
    }

    // Background sprite
    const double ratio = WIDTH / DISTANCE_TOT - 0.04;

    sf::RectangleShape sliderBarRefresh(sf::Vector2f(200, 5));
    sliderBarRefresh.setPosition(1600, 100);
    sliderBarRefresh.setFillColor(sf::Color::Black);

    sf::RectangleShape sliderCursorRefresh(sf::Vector2f(10, 20));
    sliderCursorRefresh.setPosition(1600, 95);
    sliderCursorRefresh.setFillColor(sf::Color::Red);

    sf::RectangleShape sliderBarTrain(sf::Vector2f(200, 5));
    sliderBarTrain.setPosition(1600, 150);
    sliderBarTrain.setFillColor(sf::Color::Black);

    sf::RectangleShape sliderCursorTrain(sf::Vector2f(10, 20));
    sliderCursorTrain.setPosition(1600, 145);
    sliderCursorTrain.setFillColor(sf::Color::Red);

    bool isDraggingTrain = false;
    bool isDraggingRefresh = false;
    double refresh = REFRESH;
    const double minRefresh = 0.001, maxRefresh = 2;
    const int minTrain = 100, maxTrain = 5000;

    sf::Text refreshRate;
    sf::Text distanceRate;

    while (window.isOpen()) {
        window.clear(sf::Color::White);
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (sliderCursorRefresh.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    isDraggingRefresh = true;
                }
                if (sliderCursorTrain.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    isDraggingTrain = true;
                }
            }
        }

        std::string text = "Refresh :" + std::to_string(REFRESH);
        refreshRate.setFont(font);
        refreshRate.setString(text);
        refreshRate.setCharacterSize(24);
        refreshRate.setFillColor(sf::Color::Black);
        refreshRate.setPosition(1600, 70);

        std::string distanceText = "Security :" + std::to_string(DISTANCE_SECURITY);
        distanceRate.setFont(font);
        distanceRate.setString(distanceText);
        distanceRate.setCharacterSize(24);
        distanceRate.setFillColor(sf::Color::Black);
        distanceRate.setPosition(1600, 120);

        if (event.type == sf::Event::MouseButtonReleased) {
            isDraggingTrain = false;
            isDraggingRefresh = false;
        }

        if (event.type == sf::Event::MouseMoved) {
            if (isDraggingRefresh) {
                float newX_refresh = static_cast<float>(event.mouseMove.x);

                newX_refresh = std::max(newX_refresh, sliderBarRefresh.getPosition().x);
                newX_refresh = std::min(newX_refresh, sliderBarRefresh.getPosition().x + sliderBarRefresh.getSize().x -
                                                      sliderCursorRefresh.getSize().x);


                sliderCursorRefresh.setPosition(newX_refresh, sliderCursorRefresh.getPosition().y);


                // Mise à jour de la variable refresh
                float percent = (newX_refresh - sliderBarRefresh.getPosition().x) / sliderBarRefresh.getSize().x;
                REFRESH = minRefresh + (maxRefresh - minRefresh) * percent;

            }
            if (isDraggingTrain) {
                float newX_train = static_cast<float>(event.mouseMove.x);
                newX_train = std::max(newX_train, sliderBarTrain.getPosition().x);
                newX_train = std::min(newX_train, sliderBarTrain.getPosition().x + sliderBarTrain.getSize().x -
                                                  sliderCursorTrain.getSize().x);
                sliderCursorTrain.setPosition(newX_train, sliderCursorTrain.getPosition().y);
                float percent_train = (newX_train - sliderBarTrain.getPosition().x) / sliderBarTrain.getSize().x;
                DISTANCE_SECURITY = minTrain + (maxTrain - minTrain) * percent_train;
            }
        }

        sf::RectangleShape rectangle;
        rectangle.setSize(sf::Vector2f(WIDTH - 520, 10));
        rectangle.setOutlineColor(sf::Color::Red);
        rectangle.setOutlineThickness(5);
        rectangle.setPosition(100, 245);

        window.draw(rectangle);

        sf::RectangleShape restartButton;
        restartButton.setSize(sf::Vector2f(200, 100));
        restartButton.setFillColor(sf::Color::Green);
        restartButton.setPosition(1700, HEIGHT - 200);

        sf::RectangleShape stopButton;
        stopButton.setSize(sf::Vector2f(200, 100));
        stopButton.setFillColor(sf::Color::Red);
        stopButton.setPosition(1700, HEIGHT - 400);

        sf::Text restartButtonText;
        restartButtonText.setFont(font);
        restartButtonText.setString("START "
                                    "Trains");
        restartButtonText.setCharacterSize(24);
        restartButtonText.setFillColor(sf::Color::White);
        restartButtonText.setPosition(1725, HEIGHT - 175);

        sf::Text stopButtonText;
        stopButtonText.setFont(font);
        stopButtonText.setString("Stop "
                                 "Train");
        stopButtonText.setCharacterSize(24);
        stopButtonText.setFillColor(sf::Color::White);
        stopButtonText.setPosition(1725, HEIGHT - 375);

        window.draw(restartButton);
        window.draw(restartButtonText);
        window.draw(stopButton);
        window.draw(stopButtonText);

        for (auto &train: *sharedData.Trains) {
            std::string passengerText =
                    "Passagers : " + std::to_string(train.getPassengers());
            sf::Text passengersNumber;
            passengersNumber.setFont(font);
            passengersNumber.setString(passengerText);
            passengersNumber.setCharacterSize(24); // in pixels, not points!
            passengersNumber.setFillColor(sf::Color::Black);
            passengersNumber.setPosition(1600, MID + 20);

            std::string speedText =
                    "Vitesse : " + std::to_string(train.getSpeed()) + " m/s";
            sf::Text trainSpeed;
            trainSpeed.setFont(font);
            trainSpeed.setString(speedText);
            trainSpeed.setCharacterSize(24); // in pixels, not points!
            trainSpeed.setFillColor(sf::Color::Black);
            trainSpeed.setPosition(1600, MID + 40);

            std::string idText =
                    "Train num " + std::to_string(train.getId());
            sf::Text trainNumber;
            trainNumber.setFont(font);
            trainNumber.setString(idText);
            trainNumber.setCharacterSize(24);
            trainNumber.setFillColor(sf::Color::Black);
            trainNumber.setPosition(1600, MID);

            std::string distanceText =
                    "Distance : " + std::to_string(train.getCoordX() + train.getTotalCoordX()) + " m";
            sf::Text trainDistance;
            trainDistance.setFont(font);
            trainDistance.setString(distanceText);
            trainDistance.setCharacterSize(24);
            trainDistance.setFillColor(sf::Color::Black);
            trainDistance.setPosition(1600, MID + 60);

            sf::CircleShape trainShape(80, 3);
            trainShape.setFillColor(sf::Color::Blue);

            if (train.getTerminus()->getDirection()) {
                trainShape.setPosition((train.getCoordX() + train.getTotalCoordX()) * ratio + 125,
                                       200);
                trainShape.setRotation(90);
            } else {
                trainShape.setPosition((DISTANCE_TOT - train.getCoordX() - train.getTotalCoordX()) * ratio + 80,
                                       300);
                trainShape.setRotation(-90);
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                // transform the mouse position from window coordinates to world coordinates
                sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                // retrieve the bounding box of the sprite
                sf::FloatRect bounds = trainShape.getGlobalBounds();
                sf::FloatRect restartButtonDetect = restartButton.getGlobalBounds();
                sf::FloatRect stopButtonDetect = stopButton.getGlobalBounds();

                if (bounds.contains(mouse)) {
                    window.draw(trainNumber);
                    window.draw(passengersNumber);
                    window.draw(trainSpeed);
                    window.draw(trainDistance);
                }

                if (restartButtonDetect.contains(mouse)) {
                    if (train.getEmergencyStop()) {
                        train.setEmergencyStop(false);

                        if (PRINT) {
                            std::cout << "Les trains peuvent repartir !" << std::endl;
                        }
                    }
                }

                if (stopButtonDetect.contains(mouse)) {
                    if (train.getId() == 1 and !train.getEmergencyStop()) {
                        train.setEmergencyStop(true);
                        if (PRINT) {
                            std::cout << "🚨 ARRÊT D'URGENCE ! : Le train n°" << train.getId() << " est arrếté !"
                                      << std::endl;
                        }
                    }
                }
            }
            trainShape.setScale(0.3, 0.3);
            if (train.getTotalCoordX() != 0 or train.getCoordX() != 0) {
                window.draw(trainShape);
            }
        }

        for (auto &station: sharedData.Stations) {
            sf::Text nomStation;
            sf::Text passengersNumber;
            passengersNumber.setFont(font);
            passengersNumber.setString(std::to_string(station.getPassengers(true)));
            passengersNumber.setCharacterSize(24);
            passengersNumber.setFillColor(sf::Color::Black);
            passengersNumber.setPosition(station.getCoordX(true) * ratio + 90, MID - 45);

            if (station.getNom() != "RESERVE") {
                window.draw(passengersNumber);
            }

            nomStation.setFont(font); // font is a sf::Font
            nomStation.setString(station.getNom());
            nomStation.setCharacterSize(20);
            nomStation.setFillColor(sf::Color::Red);
            nomStation.setPosition(station.getCoordX(true) * ratio, HIGH - 25);

            sf::CircleShape stationCircle(15);

            if (sharedData.isOpen) {
                stationCircle.setFillColor(sf::Color::Green);
            } else {
                stationCircle.setFillColor(sf::Color::Red);
            }
            if (station.getNom() != "RESERVE") {
                stationCircle.setPosition(station.getCoordX(true) * ratio + 80, MID - 15);
            }

            sf::RectangleShape reserveShape;
            reserveShape.setSize(sf::Vector2f(70, 170));
            reserveShape.setFillColor(sf::Color::Black);

            if (station.getNom() == "RESERVE") {
                reserveShape.setPosition(station.getCoordX(true) * ratio + 80, MID - 80);
            }

            if (stationCircle.getPosition().x != 0 and stationCircle.getPosition().y != 0) {
                window.draw(stationCircle);
            }

            if (reserveShape.getPosition().x != 0 and reserveShape.getPosition().y != 0) {
                window.draw(reserveShape);
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                sf::FloatRect bounds = stationCircle.getGlobalBounds();

                if (bounds.contains(mouse)) {
                    window.draw(nomStation);
                }
            }
        }

        sf::Text heure;
        std::string hour =
                std::to_string(std::get<0>(sharedData.heure)) + ':' +
                std::to_string(std::get<1>(sharedData.heure)) +
                ':' + std::to_string(std::get<2>(sharedData.heure));
        heure.setFont(font); // font is a sf::Font
        heure.setString(hour);
        heure.setCharacterSize(24); // in pixels, not points!
        heure.setFillColor(sf::Color::Black);
        heure.setPosition(WIDTH - 125, 25);
        window.draw(heure);

        for (auto &station: sharedData.Stations) {
            sf::Text passengersNumber;
            passengersNumber.setFont(font); // font is a sf::Font
            passengersNumber.setString(std::to_string(station.getPassengers(false)));
            passengersNumber.setCharacterSize(24); // in pixels, not points!
            passengersNumber.setFillColor(sf::Color::Black);
            passengersNumber.setPosition(station.getCoordX(1) * ratio + 90, MID + 25);

            if (station.getNom() != "RESERVE") {
                window.draw(passengersNumber);
            }
        }

        window.draw(refreshRate);
        window.draw(distanceRate);
        window.draw(sliderBarRefresh);
        window.draw(sliderCursorRefresh);
        window.draw(sliderBarTrain);
        window.draw(sliderCursorTrain);

        // display the render
        window.display();
    }
}



