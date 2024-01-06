#include "TrainGraphics.h"
#include <SFML/Graphics.hpp>


// Fonction de rendu visuel SFML
int renderVisuals(sf::RenderWindow &window, SharedData &sharedData) {


    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return EXIT_FAILURE;
    }

    // Background sprite
    const double ratio = WIDTH / DISTANCE_TOT - 0.01;

    sf::RectangleShape sliderBarRefresh(sf::Vector2f(200, 5));
    sliderBarRefresh.setPosition(1700, 100);
    sliderBarRefresh.setFillColor(sf::Color::Black);

    sf::RectangleShape sliderCursorRefresh(sf::Vector2f(10, 20));
    sliderCursorRefresh.setPosition(1700, 95);
    sliderCursorRefresh.setFillColor(sf::Color::Red);

    sf::RectangleShape sliderBarTrain(sf::Vector2f(200, 5));
    sliderBarTrain.setPosition(1700, 150);
    sliderBarTrain.setFillColor(sf::Color::Black);

    sf::RectangleShape sliderCursorTrain(sf::Vector2f(10, 20));
    sliderCursorTrain.setPosition(1700, 145);
    sliderCursorTrain.setFillColor(sf::Color::Red);

    bool isDragging = false;
    double refresh = REFRESH;
    int trainNumber = TRAIN_NUMBER;
    const double minRefresh = 0.001, maxRefresh = 1.0;
    const int minTrain = 1, maxTrain = 40;

    sf::Text refreshRate;


    while (window.isOpen()) {

        window.clear(sf::Color::White);
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (sliderCursorRefresh.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    isDragging = true;
                }
                if (sliderCursorTrain.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    isDragging = true;
                }
            }
        }


        std::string text = "Refresh :" + std::to_string(REFRESH);
        refreshRate.setFont(font);
        refreshRate.setString(text);
        refreshRate.setCharacterSize(24);
        refreshRate.setFillColor(sf::Color::Black);
        refreshRate.setPosition(1700, 70);

        if (event.type == sf::Event::MouseButtonReleased) {
            isDragging = false;
        }

        if (event.type == sf::Event::MouseMoved) {
            if (isDragging) {
                float newX_refresh = static_cast<float>(event.mouseMove.x);
                float newX_train = static_cast<float>(event.mouseMove.x);
                newX_refresh = std::max(newX_refresh, sliderBarRefresh.getPosition().x);
                newX_refresh = std::min(newX_refresh, sliderBarRefresh.getPosition().x + sliderBarRefresh.getSize().x -
                                                      sliderCursorRefresh.getSize().x);

                newX_train = std::max(newX_train, sliderBarTrain.getPosition().x);
                newX_train = std::min(newX_train, sliderBarTrain.getPosition().x + sliderBarTrain.getSize().x -
                                                  sliderCursorTrain.getSize().x);


                sliderCursorRefresh.setPosition(newX_refresh, sliderCursorRefresh.getPosition().y);
                sliderCursorTrain.setPosition(newX_train, sliderCursorTrain.getPosition().y);

                // Mise à jour de la variable refresh
                float percent = (newX_refresh - sliderBarRefresh.getPosition().x) / sliderBarRefresh.getSize().x;
                REFRESH = minRefresh + (maxRefresh - minRefresh) * percent;
                /*float percent_train = (newX_train - sliderBarTrain.getPosition().x) / sliderBarTrain.getSize().x;
                REFRESH = minTrain + (maxTrain - minTrain) * percent_train;*/
            }
        }


        sf::RectangleShape rectangle;
        rectangle.setSize(sf::Vector2f(WIDTH * 2 / 3, 1));
        rectangle.setOutlineColor(sf::Color::Red);
        rectangle.setOutlineThickness(5);
        rectangle.setPosition(100, 250);


        window.draw(rectangle);


        sf::RectangleShape restartButton;
        restartButton.setSize(sf::Vector2f(200, 100));
        restartButton.setFillColor(sf::Color::Green);
        restartButton.setPosition(1700, HEIGHT - 200);

        sf::Text restartButtonText;
        restartButtonText.setFont(font);
        restartButtonText.setString("Restart "
                                    "Trains");
        restartButtonText.setCharacterSize(24);
        restartButtonText.setFillColor(sf::Color::Black);
        restartButtonText.setPosition(1700, HEIGHT - 200);
        window.draw(restartButton);
        window.draw(restartButtonText);


        for (auto &station: sharedData.Stations) {
            sf::Text nomStation;
            sf::Text passengersNumber;


            passengersNumber.setFont(font);
            passengersNumber.setString(std::to_string(station.getPassengers(true)));
            passengersNumber.setCharacterSize(24);
            passengersNumber.setFillColor(sf::Color::Black);
            passengersNumber.setPosition(station.getCoordX(1) * ratio, MID - 45);
            window.draw(passengersNumber);

            nomStation.setFont(font); // font is a sf::Font
            nomStation.setString(station.getNom());
            nomStation.setCharacterSize(20);
            nomStation.setFillColor(sf::Color::Red);
            nomStation.setPosition(station.getCoordX(1) * ratio, HIGH - 25);

            sf::CircleShape stationCircle(15);
            stationCircle.setFillColor(sf::Color::Black);
            stationCircle.setPosition(station.getCoordX(1) * ratio, MID - 15);
            window.draw(stationCircle);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                // transform the mouse position from window coordinates to world coordinates
                sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                // retrieve the bounding box of the sprite
                sf::FloatRect bounds = stationCircle.getGlobalBounds();

                // hit test
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
            passengersNumber.setPosition(station.getCoordX(1) * ratio, MID + 25);
            window.draw(passengersNumber);
        }


        for (auto &train: *sharedData.Trains) {
            sf::Text passengersNumber;
            passengersNumber.setFont(font); // font is a sf::Font
            passengersNumber.setString(std::to_string(train.getPassengers()));
            passengersNumber.setCharacterSize(24); // in pixels, not points!
            passengersNumber.setFillColor(sf::Color::Black);
            sf::CircleShape trainShape(80, 3);
            trainShape.setFillColor(sf::Color::Blue);


            if (train.getTerminus()->getDirection()) {
                trainShape.setPosition((train.getCoordX() + train.getTotalCoordX()) * ratio,
                                       200);
                trainShape.setRotation(90);

                passengersNumber.setPosition((train.getTotalCoordX() + train.getCoordX()) * ratio - 25,
                                             175);

            } else {
                trainShape.setPosition((DISTANCE_TOT - train.getCoordX() - train.getTotalCoordX()) * ratio,
                                       300);
                trainShape.setRotation(-90);
                passengersNumber.setPosition(
                        (DISTANCE_TOT - train.getCoordX() - train.getTotalCoordX()) * ratio,
                        300);

            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                // transform the mouse position from window coordinates to world coordinates
                sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                // retrieve the bounding box of the sprite
                sf::FloatRect bounds = trainShape.getGlobalBounds();

                sf::FloatRect button = restartButton.getGlobalBounds();

                // hit test
                if (bounds.contains(mouse) and !train.getEmergencyStop()) {
                    train.setEmergencyStop(true);
                    std::cout << "STOP : " << train.getId() << std::endl;
                }
                if (button.contains(mouse) and train.getEmergencyStop()) {
                    train.setEmergencyStop(false);
                    std::cout << "GO : " << train.getId() << std::endl;
                }

            }
            trainShape.setScale(0.3, 0.3);
            if (train.getTotalCoordX() != 0 or train.getCoordX() != 0) {
                window.draw(trainShape);
                window.draw(passengersNumber);
            }


        }


        window.draw(refreshRate);
        window.draw(sliderBarRefresh);
        window.draw(sliderCursorRefresh);
        window.draw(sliderBarTrain);
        window.draw(sliderCursorTrain);

        // display the render

        window.display();
    }
}



