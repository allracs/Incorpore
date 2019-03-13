#include <SFML/Graphics.hpp>
#include <stdio.h>
#include "../include/Enemigo.h"
#include "../include/Jugador.h"

int main()
{
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(800, 600), "SFML window");
    app.setFramerateLimit(60);

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

        e.mover(j.getPos()[0], j.getPos()[1], clock);
        j.mover(0, 0, clock);

        // Clear screen and reset clock
        app.clear();
        clock.restart().asMilliseconds();

        // Draw the sprite
        app.draw(e.getSprite());
        app.draw(j.getSprite());

        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}
