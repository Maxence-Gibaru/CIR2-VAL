#include "TrainGraphics.h"

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
            return EXIT_FAILURE;
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
        sf::Font font;
        if (!font.loadFromFile("arial.ttf")) {
            return EXIT_FAILURE;
        }

        window.draw(rectangle);

        for (auto &station: sharedData.Stations) {
            sf::Text nomStation;
            sf::Text passengersNumber;


            passengersNumber.setFont(font); // font is a sf::Font
            passengersNumber.setString(std::to_string(station.getPassengers()));
            passengersNumber.setCharacterSize(24); // in pixels, not points!
            passengersNumber.setFillColor(sf::Color::Black);
            passengersNumber.setPosition(station.getCoordX(1) * WIDTH / DISTANCE_TOT, 100);
            window.draw(passengersNumber);

            nomStation.setFont(font); // font is a sf::Font
            nomStation.setString(station.getNom());
            nomStation.setCharacterSize(24); // in pixels, not points!
            nomStation.setFillColor(sf::Color::Red);
            nomStation.setPosition(station.getCoordX(1) * WIDTH / DISTANCE_TOT, 75);
            window.draw(nomStation);


            sf::RectangleShape rectangle;
            rectangle.setSize(sf::Vector2f(50, 50));
            rectangle.setFillColor(sf::Color::Blue);
            rectangle.setPosition(station.getCoordX(1) * WIDTH / DISTANCE_TOT, 25);
            window.draw(rectangle);
        }

        for (auto &station: sharedData.Stations) {
            sf::Text nomStation;
            sf::Text passengersNumber;


            passengersNumber.setFont(font); // font is a sf::Font
            passengersNumber.setString(std::to_string(station.getPassengers()));
            passengersNumber.setCharacterSize(24); // in pixels, not points!
            passengersNumber.setFillColor(sf::Color::Black);
            passengersNumber.setPosition(station.getCoordX(1) * WIDTH / DISTANCE_TOT, 875);
            window.draw(passengersNumber);


            nomStation.setFont(font); // font is a sf::Font
            nomStation.setString(station.getNom());
            nomStation.setPosition(station.getCoordX(1) * WIDTH / DISTANCE_TOT, 900);
            nomStation.setCharacterSize(24); // in pixels, not points!
            nomStation.setFillColor(sf::Color::Red);
            window.draw(nomStation);


            sf::RectangleShape rectangle;
            rectangle.setSize(sf::Vector2f(50, 50));
            rectangle.setFillColor(sf::Color::Blue);
            rectangle.setPosition((DISTANCE_TOT - station.getCoordX(0)) * WIDTH / DISTANCE_TOT, 925);
            window.draw(rectangle);
        }


        for (auto &train: sharedData.Trains) {
            sf::Text passengersNumber;
            passengersNumber.setFont(font); // font is a sf::Font
            passengersNumber.setString(std::to_string(train.getPassengers()));
            passengersNumber.setCharacterSize(24); // in pixels, not points!
            passengersNumber.setFillColor(sf::Color::Black);
            sf::Sprite sprite(texture);
            if (train.getTerminus()->getDirection()) {
                sprite.setPosition((train.getCoordX() + train.getTotalCoordX()) * WIDTH / DISTANCE_TOT,
                                   train.getCoordY());


                passengersNumber.setPosition((train.getTotalCoordX() + train.getCoordX()) * WIDTH / DISTANCE_TOT,
                                             train.getCoordY() + 100);
                window.draw(passengersNumber);
            } else {
                sprite.setPosition((DISTANCE_TOT - train.getCoordX() - train.getTotalCoordX()) * WIDTH / DISTANCE_TOT,
                                   train.getCoordY());
                passengersNumber.setPosition(
                        (DISTANCE_TOT - train.getCoordX() - train.getTotalCoordX()) * WIDTH / DISTANCE_TOT,
                        train.getCoordY() - 50);
                window.draw(passengersNumber);
            }
            sprite.setScale(0.5, 0.5);
            window.draw(sprite);
        }





        // display the render

        window.display();
    }
}