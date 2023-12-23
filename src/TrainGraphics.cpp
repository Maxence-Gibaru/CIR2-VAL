#include "TrainGraphics.h"

// Fonction de rendu visuel SFML
//int renderVisuals(sf::RenderWindow &window, SharedData &sharedData) {
/*
    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile("spr_train_0.png")) {
        return EXIT_FAILURE;
    }
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return EXIT_FAILURE;
    }
    // Load an image file from a file
    sf::Image background;
    if (!background.loadFromFile("flashbackmetro.jpeg"))
        return EXIT_FAILURE;
    // Background sprite

    const double ratio = WIDTH / DISTANCE_TOT - 0.01;

    while (window.isOpen()) {
        window.clear(sf::Color::White);
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        sf::RectangleShape rectangle;
        rectangle.setSize(sf::Vector2f(WIDTH, 1));
        rectangle.setOutlineColor(sf::Color::Red);
        rectangle.setOutlineThickness(5);
        rectangle.setPosition(0, MID);


        window.draw(rectangle);


        sf::RectangleShape restartButton;
        restartButton.setSize(sf::Vector2f(100, 100));
        restartButton.setFillColor(sf::Color::Green);
        restartButton.setPosition(100, HEIGHT - 200);


        window.draw(restartButton);

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
                std::to_string(std::get<0>(sharedData.heure)) + ':' + std::to_string(std::get<1>(sharedData.heure)) +
                ':' + std::to_string(std::get<2>(sharedData.heure));

        heure.setFont(font); // font is a sf::Font
        heure.setString(hour);
        heure.setCharacterSize(24); // in pixels, not points!
        heure.setFillColor(sf::Color::Black);
        heure.setPosition(WIDTH - 125, 25);
        window.draw(heure);

        for (auto &station: sharedData.Stations) {
            sf::Text nomStation;
            sf::Text passengersNumber;


            passengersNumber.setFont(font); // font is a sf::Font
            passengersNumber.setString(std::to_string(station.getPassengers(false)));
            passengersNumber.setCharacterSize(24); // in pixels, not points!
            passengersNumber.setFillColor(sf::Color::Black);
            passengersNumber.setPosition(station.getCoordX(1) * ratio, MID + 25);
            window.draw(passengersNumber);
*/
/* A garder
            nomStation.setFont(font); // font is a sf::Font
            nomStation.setString(station.getNom());
            nomStation.setPosition(station.getCoordX(1) * ratio, LOW);
            nomStation.setCharacterSize(12); // in pixels, not points!
            nomStation.setFillColor(sf::Color::Red);
            window.draw(nomStation);*/


            /*sf::RectangleShape rectangle;
            rectangle.setSize(sf::Vector2f(50, 50));
            rectangle.setFillColor(sf::Color::Blue);
            rectangle.setPosition((DISTANCE_TOT - station.getCoordX(0)) * ratio, LOW);
            window.draw(rectangle);*/
        //}

/*
        for (auto &train: *sharedData.Trains) {
            sf::Text passengersNumber;
            passengersNumber.setFont(font); // font is a sf::Font
            passengersNumber.setString(std::to_string(train.getPassengers()));
            passengersNumber.setCharacterSize(24); // in pixels, not points!
            passengersNumber.setFillColor(sf::Color::Black);
            sf::CircleShape trainShape(60, 8);
            trainShape.setFillColor(sf::Color::Green);

            if (train.getTerminus()->getDirection()) {
                trainShape.setPosition((train.getCoordX() + train.getTotalCoordX()) * ratio,
                                       train.getCoordY());


                passengersNumber.setPosition((train.getTotalCoordX() + train.getCoordX()) * ratio,
                                             train.getCoordY());

            } else {
                trainShape.setPosition((DISTANCE_TOT - train.getCoordX() - train.getTotalCoordX()) * ratio,
                                       train.getCoordY());
                passengersNumber.setPosition(
                        (DISTANCE_TOT - train.getCoordX() - train.getTotalCoordX()) * ratio,
                        train.getCoordY());

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

            window.draw(trainShape);
            window.draw(passengersNumber);

        }





        // display the render

        window.display();
    }
}

 */