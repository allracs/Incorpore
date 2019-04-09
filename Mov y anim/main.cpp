#include <SFML/Graphics.hpp>
#include "Jugador.h"
#include "Animacion.h"

int main()
{
    // Create the main window
    sf::Vector2i screenDimensions(800,600);
    sf::RenderWindow app(sf::VideoMode(screenDimensions.x, screenDimensions.y), "SFML window");
    app.setFramerateLimit(60);
    Jugador Manolito(sf::Vector2f(300, 300));


    // VISTA
    sf::View view;
    view.reset(sf::FloatRect(0, 0, screenDimensions.x, screenDimensions.y)); // Esto es necesario para crear la vista.
    view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
    view.zoom(0.2f);
    view.setCenter(Manolito.getCenter());

    bool centrado = false;

    // BACKGROUND
    sf::Texture textBackground;
    textBackground.loadFromFile("background.png");
    sf::Sprite background;
    sf::Vector2u size = textBackground.getSize();
    background.setTexture(textBackground);
    background.setOrigin(size.x / 2, size.y / 2);


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
        if(!centrado) {
            view.setCenter(Manolito.getCenter());
            centrado = true;

        }


        /*sf::Vertex Line[] =
        {
            sf::Vertex(sf::Vector2f(Manolito.getCenter())),
            sf::Vertex(sf::Vector2f(Manolito.getMousePos()))
        };*/

        view.move(Manolito.getMovement() * delta);



        // Set the viewport
        app.setView(view);

        // Clear screen
        app.clear();

        app.draw(background);
        Manolito.draw(app);
        //app.draw(Line, 2, sf::Lines);

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
