#include <SFML/Graphics.hpp>
#include <stdio.h>
#include "../include/Enemigo.h"
#include "../include/Jugador.h"

int main()
{
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(800, 600), "SFML window");

    Enemigo e;
    Jugador j;


	// Start the game loop
    while (app.isOpen())
    {


        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();
        }




        // Clear screen
        app.clear();

        // Draw the sprite
        app.draw(e.getSprite());
        app.draw(j.getSprite());

        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}
