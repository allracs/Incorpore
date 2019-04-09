#include <SFML/Graphics.hpp>
#include "Jugador.h"
#include "Animacion.h"

int main()
{
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(800, 600), "SFML window");
    app.setFramerateLimit(60);
    Jugador Manolito(sf::Vector2f(300, 300));
    sf::Clock frameClock;

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

        float delta = frameClock.restart().asSeconds();
        Manolito.update(delta, app);

        // Clear screen
        app.clear();

        Manolito.draw(app);
        /*
        app.draw(Manolito.actual->sprite);
        app.draw(Manolito.jugador);
        app.draw(Manolito.hitboxAtaque)
        */
        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}
