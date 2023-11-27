#include "../include/TrainGraphics.h"

int display() {
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML window");

    sf::Texture texture;
    if (!texture.loadFromFile("ugo.png"))
        return EXIT_FAILURE;
    sf::Sprite sprite(texture);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }
    return 0;
}