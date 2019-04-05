#include <SFML/Graphics.hpp>
#include "Animacion.h"

int main()
{
    // Crear la ventana principal
    sf::RenderWindow app(sf::VideoMode(800, 600), "SFML window");
    app.setFramerateLimit(60);

    // Creamos la animacion que vamos a hacer
    Animacion idle;
    // Le damos los valores que son: el nombre del fichero, el frame inicial, el frame final, de cuanto en cuanto se incrementa y la velocidad a la que se reproducirá
    idle.setAnimacion("caballero.png", sf::IntRect(0,0,16,28),sf::IntRect(48,0,16,28), 16, 0.1f);
    idle.sprite.setScale(8.f, 8.f);

    float deltaTime = 0.f;
    sf::Clock clock;

	// Start the game loop
    while (app.isOpen())
    {
        deltaTime = clock.restart().asSeconds();
        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();
        }

        idle.update(deltaTime);

        // Clear screen
        app.clear();

        // Draw the sprite
        app.draw(idle.sprite);

        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}
