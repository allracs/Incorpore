#include <SFML/Graphics.hpp>
#include <stdio.h>
#include "../include/Enemigo.h"
#include "../include/Jugador.h"

int main()
{
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(1280, 720), "SFML window");
    app.setFramerateLimit(60);
    app.setPosition({10.f, 10.f});

    Enemigo e;
    Jugador j;

    sf::Clock clock;
	// Start the game loop
    while (app.isOpen())
    {
        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                app.close();
        }

        if(!j.getSprite().getGlobalBounds().intersects(e.getSprite().getGlobalBounds()))
        {
            e.mover(j.getPos()[0], j.getPos()[1], clock);
        }

        j.mover(0, 0, clock);

        // Clear screen and reset clock
        app.clear();
        clock.restart().asMilliseconds();

        //Draw a line between player and enemy
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(j.getPos()[0], j.getPos()[1])),
            sf::Vertex(sf::Vector2f(e.getPos()[0], e.getPos()[1]))
        };

        app.draw(line, 2, sf::Lines);


        // Draw the sprite
        app.draw(e.getSprite());
        app.draw(j.getSprite());

        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}
