#include <SFML/Graphics.hpp>
#include "Jugador.h"
#include "Animacion.h"
#include "Enemigo.h"
#include "Bullet.h"

int main()
{
    // Create the main window
    sf::Vector2i screenDimensions(1080,720);
    sf::RenderWindow app(sf::VideoMode(screenDimensions.x, screenDimensions.y), "SFML window");
    app.setFramerateLimit(60);

    // creacion de los enemigos y jugadores
    Jugador Manolito(sf::Vector2f(300, 300));

    Enemigo Pepe(sf::Vector2f(230, 250));
    Enemigo Pepe2(sf::Vector2f(130, 200));
    Enemigo Pepe3(sf::Vector2f(100, 250));
    Enemigo Pepe4(sf::Vector2f(150, 250));
    Enemigo Pepe5(sf::Vector2f(120, 250));


    std::vector<Enemigo> enemigos;

    enemigos.push_back(Pepe);
    enemigos.push_back(Pepe2);
    enemigos.push_back(Pepe3);
    enemigos.push_back(Pepe4);
    enemigos.push_back(Pepe5);



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

        sf::RectangleShape j_hitbox = Manolito.getHitboxAtaque();


        Manolito.update(delta, app);

        for(int i = 0; i < enemigos.size(); i++) {
            enemigos[i].update(delta, app, j_hitbox);
        }


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

        //Draws
        app.draw(background);
        Manolito.draw(app);


        for(int i = 0; i < enemigos.size(); i++)
            enemigos[i].draw(app);

        //app.draw(Line, 2, sf::Lines);


        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}
