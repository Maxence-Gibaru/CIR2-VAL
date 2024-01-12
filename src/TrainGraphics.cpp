#include "TrainGraphics.h"

int randomTarget1 = rand() % TRAIN_NUMBER_LINE_1;
int randomTarget2 = rand() % TRAIN_NUMBER_LINE_2;

void drawLine(auto &window, int offSetY, auto color) {
    sf::RectangleShape line;
    line.setSize(sf::Vector2f(WIDTH - 520, 30));
    line.setOutlineColor(color);
    line.setOutlineThickness(5);
    line.setFillColor(sf::Color::Transparent);
    line.setPosition(100, 235 + offSetY);
    window.draw(line);
}

void drawTrain(auto &window, Train &train, auto &trainShape, std::vector<Train> &Trains1, std::vector<Train> &Trains2,
               auto font,
               const float ratio,
               int offSetY, auto restartButton, auto stopButton, auto emergencyStopButton,
               auto emergencyRestartButton) {

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


    if (train.getTerminus()->getDirection()) {
        trainShape.setPosition((train.getCoordX() + train.getTotalCoordX()) * ratio + 60,
                               220 + offSetY);
        trainShape.setRotation(0);

    } else {
        trainShape.setPosition((DISTANCE_TOT - train.getCoordX() - train.getTotalCoordX()) * ratio + 130,
                               278 + offSetY);
        trainShape.setRotation(180);
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        // transform the mouse position from window coordinates to world coordinates
        sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        // retrieve the bounding box of the sprite
        sf::FloatRect bounds = trainShape.getGlobalBounds();
        sf::FloatRect restartButtonDetect = restartButton.getGlobalBounds();
        sf::FloatRect stopButtonDetect = stopButton.getGlobalBounds();
        sf::FloatRect emergencyStopDetect = emergencyStopButton.getGlobalBounds();
        sf::FloatRect emergencyRestartDetect = emergencyRestartButton.getGlobalBounds();

        if (bounds.contains(mouse)) {
            window.draw(trainNumber);
            window.draw(passengersNumber);
            window.draw(trainSpeed);
            window.draw(trainDistance);
        }
        if (stopButtonDetect.contains(mouse)) {

            moving = false;
            if (PRINT) {
                std::cout << "🚨 ARRÊT D'URGENCE ! : Le train n°" << train.getId() << " est arrếté !"
                          << std::endl;
            }
        }
        if (restartButtonDetect.contains(mouse)) {
            for (auto &train: Trains1) {

                moving = true;

                if (PRINT) {
                    std::cout << "Les trains peuvent repartir !" << std::endl;
                }
            }
        }


        if (emergencyStopDetect.contains(mouse)) {


            for (auto &targetTrain: Trains1) {
                if (targetTrain.getId() == randomTarget1) {
                    targetTrain.setEmergencyStop(true);
                    if (PRINT) {
                        std::cout << "🚨 ARRÊT D'URGENCE ! : Le train n°" << train.getId() << " est arrếté !"
                                  << std::endl;
                    }
                }
            }

            for (auto &targetTrain: Trains2) {
                if (targetTrain.getId() == randomTarget2) {
                    targetTrain.setEmergencyStop(true);
                    if (PRINT) {
                        std::cout << "🚨 ARRÊT D'URGENCE ! : Le train n°" << train.getId() << " est arrếté !"
                                  << std::endl;
                    }
                }
            }
        }

        if (emergencyRestartDetect.contains(mouse) and train.getEmergencyStop()) {
            train.setEmergencyStop(false);
            if (PRINT) {
                std::cout << "Les trains peuvent repartir !" << std::endl;
            }
        }
    }

    trainShape.setScale(0.1, 0.1);
    if (train.getTotalCoordX() != 0 or train.getCoordX() != 0) {
        window.draw(trainShape);
    }
}

void drawStation(auto &window, Station &station, auto &font, const float &ratio, bool &isOpen, int offSetY,
                 std::vector<Station> &Stations) {
    sf::Text nomStation;
    sf::Text passengersNumber;
    passengersNumber.setFont(font);
    passengersNumber.setString(std::to_string(station.getPassengers(true)));
    passengersNumber.setCharacterSize(24);
    passengersNumber.setFillColor(sf::Color::Black);
    passengersNumber.setPosition(station.getCoordX(true) * ratio + 85, MID - 55 + offSetY);

    sf::Text passengersNumber_;
    passengersNumber_.setFont(font); // font is a sf::Font
    passengersNumber_.setString(std::to_string(station.getPassengers(false)));
    passengersNumber_.setCharacterSize(24); // in pixels, not points!
    passengersNumber_.setFillColor(sf::Color::Black);
    passengersNumber_.setPosition(station.getCoordX(true) * ratio + 85, MID + 27 + offSetY);

    if (station.getNom() != "RESERVE") {
        window.draw(passengersNumber);
        window.draw(passengersNumber_);
    }

    nomStation.setFont(font); // font is a sf::Font
    nomStation.setString(station.getNom());
    nomStation.setCharacterSize(20);
    nomStation.setFillColor(sf::Color::Red);
    nomStation.setPosition(station.getCoordX(true) * ratio + 55, HIGH + 25 + offSetY);

    sf::CircleShape stationCircle(15);

    if (isOpen) {
        stationCircle.setFillColor(sf::Color::Green);
    } else {
        stationCircle.setFillColor(sf::Color::Red);
    }
    if (station.getNom() != "RESERVE") {
        stationCircle.setPosition(station.getCoordX(true) * ratio + 80, MID - 15 + offSetY);
    }

    sf::RectangleShape reserveShape;
    reserveShape.setSize(sf::Vector2f(120, 60));
    reserveShape.setFillColor(sf::Color::Black);

    if (station.getNom() == "RESERVE") {
        reserveShape.setPosition(station.getCoordX(true) * ratio + 50, MID - 30 + offSetY);
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

void drawHour(auto &window, SharedData &sharedData, auto font) {
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

}

void drawUI(auto &window, auto &emergencyStopButton, auto &emergencyRestartButton, auto &restartButton,
            auto &stopButton, auto &restartButtonText, auto &stopButtonText, auto &refreshRate, auto &distanceRate,
            auto &sliderBarRefresh, auto &sliderCursorRefresh, auto &sliderBarTrain, auto &sliderCursorTrain,
            auto &font) {


    emergencyStopButton.setSize(sf::Vector2f(100, 100));
    emergencyStopButton.setFillColor(sf::Color::Yellow);
    emergencyStopButton.setPosition(100, HEIGHT - 200);


    emergencyRestartButton.setSize(sf::Vector2f(100, 100));
    emergencyRestartButton.setFillColor(sf::Color::Cyan);
    emergencyRestartButton.setPosition(250, HEIGHT - 200);


    restartButton.setSize(sf::Vector2f(200, 100));
    restartButton.setFillColor(sf::Color::Green);
    restartButton.setPosition(1700, HEIGHT - 200);


    stopButton.setSize(sf::Vector2f(200, 100));
    stopButton.setFillColor(sf::Color::Red);
    stopButton.setPosition(1700, HEIGHT - 400);


    restartButtonText.setFont(font);
    restartButtonText.setString("START");
    restartButtonText.setCharacterSize(40);
    restartButtonText.setFillColor(sf::Color::White);
    restartButtonText.setPosition(1745, HEIGHT - 175);


    stopButtonText.setFont(font);
    stopButtonText.setString("STOP");
    stopButtonText.setCharacterSize(40);
    stopButtonText.setFillColor(sf::Color::White);
    stopButtonText.setPosition(1745, HEIGHT - 375);


    window.draw(restartButton);
    window.draw(restartButtonText);
    window.draw(stopButton);
    window.draw(stopButtonText);
    window.draw(emergencyStopButton);
    window.draw(emergencyRestartButton);


}

void handleInteractions(sf::Event &event, bool &isDraggingTrain, bool &isDraggingRefresh,
                        sf::RectangleShape &sliderBarRefresh, sf::RectangleShape &sliderCursorRefresh,
                        float minRefresh, float maxRefresh,
                        sf::RectangleShape &sliderBarTrain, sf::RectangleShape &sliderCursorTrain,
                        int minTrain, int maxTrain, auto &refreshRate, auto &distanceRate) {


    if (isDraggingRefresh) {
        auto newX_refresh = static_cast<float>(event.mouseMove.x);

        newX_refresh = std::max(newX_refresh, sliderBarRefresh.getPosition().x);
        newX_refresh = std::min(newX_refresh, sliderBarRefresh.getPosition().x + sliderBarRefresh.getSize().x -
                                              sliderCursorRefresh.getSize().x);

        sliderCursorRefresh.setPosition(newX_refresh, sliderCursorRefresh.getPosition().y);

        // Mise à jour de la variable refresh
        float percent = (newX_refresh - sliderBarRefresh.getPosition().x) / sliderBarRefresh.getSize().x;
        REFRESH = minRefresh + (maxRefresh - minRefresh) * percent;
        std::string text = "Refresh :" + std::to_string(REFRESH);
        refreshRate.setString(text);
    }
    if (isDraggingTrain) {
        auto newX_train = static_cast<float>(event.mouseMove.x);
        newX_train = std::max(newX_train, sliderBarTrain.getPosition().x);
        newX_train = std::min(newX_train, sliderBarTrain.getPosition().x + sliderBarTrain.getSize().x -
                                          sliderCursorTrain.getSize().x);
        sliderCursorTrain.setPosition(newX_train, sliderCursorTrain.getPosition().y);
        float percent_train = (newX_train - sliderBarTrain.getPosition().x) / sliderBarTrain.getSize().x;
        DISTANCE_SECURITY = minTrain + (maxTrain - minTrain) * percent_train;
        std::string distanceText = "Security :" + std::to_string(DISTANCE_SECURITY);
        distanceRate.setString(distanceText);
    }
}

void setSliders(auto &refreshRate, auto &distanceRate, auto &sliderBarRefresh, auto &sliderCursorRefresh,
                auto &sliderBarTrain, auto &sliderCursorTrain, auto &font) {
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

    // Initialize various shapes and variables for UI elements

    sliderBarRefresh.setPosition(1600, 100);
    sliderBarRefresh.setFillColor(sf::Color::Black);


    sliderCursorRefresh.setPosition(1600, 95);
    sliderCursorRefresh.setFillColor(sf::Color::Red);


    sliderBarTrain.setPosition(1600, 150);
    sliderBarTrain.setFillColor(sf::Color::Black);


    sliderCursorTrain.setPosition(1600, 145);
    sliderCursorTrain.setFillColor(sf::Color::Red);
}

void drawSliders(sf::RenderWindow &window, auto &refreshRate, auto &distanceRate, auto &sliderBarRefresh,
                 auto &sliderCursorRefresh,
                 auto &sliderBarTrain, auto &sliderCursorTrain) {
    window.draw(sliderBarRefresh);
    window.draw(sliderCursorRefresh);
    window.draw(sliderBarTrain);
    window.draw(sliderCursorTrain);
    window.draw(refreshRate);
    window.draw(distanceRate);
}


// Function to render visuals
int renderVisuals(sf::RenderWindow &window, SharedData &sharedData) {


    sf::Font font;
    if (!font.loadFromFile("../assets/fonts/arial.ttf")) {
        return EXIT_FAILURE;
    }

    sf::Texture trainTexture;
    if (!trainTexture.loadFromFile("../assets/images/rame.png")) {
        return EXIT_FAILURE;
    }

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("../assets/images/background_image.png")) {
        return EXIT_FAILURE;
    }

    sf::Texture emergencyTexture;
    if (!emergencyTexture.loadFromFile("../assets/images/emergency.png")) {
        return EXIT_FAILURE;
    }

    sf::Texture restartTexture;
    if (!restartTexture.loadFromFile("../assets/images/restart_logo.png")) {
        return EXIT_FAILURE;
    }


    sf::Sprite trainShape;
    trainShape.setTexture(trainTexture);

    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setPosition(0, 0);
    backgroundSprite.setScale(1.2, 1.2);

    sf::Sprite emergencySprite;
    emergencySprite.setTexture(emergencyTexture);
    emergencySprite.setPosition(105, HEIGHT - 195);
    emergencySprite.setScale(0.18, 0.18);

    sf::Sprite restartSprite;
    restartSprite.setTexture(restartTexture);
    restartSprite.setPosition(235, HEIGHT - 190);
    restartSprite.setScale(0.2, 0.2);


    // Background shapes and variables for sliders and buttons

    const float ratio = WIDTH / DISTANCE_TOT - 0.04;

    sf::RectangleShape emergencyStopButton;
    sf::RectangleShape emergencyRestartButton;
    sf::RectangleShape restartButton;
    sf::RectangleShape stopButton;
    sf::Text restartButtonText;
    sf::Text stopButtonText;
    sf::RectangleShape sliderBarRefresh(sf::Vector2f(200, 5));
    sf::RectangleShape sliderCursorRefresh(sf::Vector2f(10, 20));
    sf::RectangleShape sliderBarTrain(sf::Vector2f(200, 5));
    sf::RectangleShape sliderCursorTrain(sf::Vector2f(10, 20));
    sf::Text refreshRate;
    sf::Text distanceRate;

    bool isDraggingTrain = false;
    bool isDraggingRefresh = false;
    const double minRefresh = 0.001, maxRefresh = 2;
    const int minTrain = 100, maxTrain = 5000;

    setSliders(refreshRate, distanceRate, sliderBarRefresh, sliderCursorRefresh, sliderBarTrain, sliderCursorTrain,
               font);

    while (window.isOpen()) {
        window.clear();
        window.draw(backgroundSprite);


        drawUI(window, emergencyStopButton, emergencyRestartButton, restartButton, stopButton, restartButtonText,
               stopButtonText, refreshRate, distanceRate, sliderBarRefresh, sliderCursorRefresh, sliderBarTrain,
               sliderCursorTrain, font);


        // Event handling
        sf::Event event{};
        while (window.pollEvent(event)) {

            // Close window if 'X' button clicked
            if (event.type == sf::Event::Closed)
                window.close();

            // Handling mouse button presses
            if (event.type == sf::Event::MouseButtonPressed) {
                if (sliderCursorRefresh.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    isDraggingRefresh = true;
                }
                if (sliderCursorTrain.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    isDraggingTrain = true;
                }
            }

            // Handling mouse button releases
            if (event.type == sf::Event::MouseButtonReleased) {
                isDraggingTrain = false;
                isDraggingRefresh = false;
            }

            // Handling mouse movement
            if (event.type == sf::Event::MouseMoved) {
                handleInteractions(event, isDraggingTrain, isDraggingRefresh, sliderBarRefresh, sliderCursorRefresh,
                                   minRefresh, maxRefresh, sliderBarTrain, sliderCursorTrain, minTrain, maxTrain,
                                   refreshRate, distanceRate);


            }
        }

        drawSliders(window, refreshRate, distanceRate, sliderBarRefresh, sliderCursorRefresh, sliderBarTrain,
                    sliderCursorTrain);

        drawLine(window, 0, sf::Color::Red);
        drawLine(window, 455, sf::Color::Yellow);


        for (auto &train: *sharedData.Trains1) {
            drawTrain(window, train, trainShape, *sharedData.Trains1, *sharedData.Trains2, font, ratio, 0,
                      restartButton,
                      stopButton, emergencyStopButton, emergencyRestartButton);
        }

        for (auto &train: *sharedData.Trains2) {
            drawTrain(window, train, trainShape, *sharedData.Trains1, *sharedData.Trains2, font, ratio, 455,
                      restartButton,
                      stopButton, emergencyStopButton, emergencyRestartButton);
        }


        for (auto &station: sharedData.Stations1) {
            drawStation(window, station, font, ratio, sharedData.isOpen, 0, sharedData.Stations1);
        }


        for (auto &station: sharedData.Stations2) {
            drawStation(window, station, font, ratio, sharedData.isOpen, 455, sharedData.Stations2);
        }


        drawHour(window, sharedData, font);


        window.draw(emergencySprite);
        window.draw(restartSprite);
        // display the render
        window.display();
    }
}