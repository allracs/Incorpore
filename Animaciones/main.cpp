#include <SFML/Graphics.hpp>
#include "AnimatedSprite.hpp"
#include <iostream>

int main()
{
    // Montamos la ventana
    // TO-DO Hacer un viewpoint para hacerle zoom a los sprites.
    sf::Vector2i screenDimensions(800,600);
    sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Mostrar animaciones");
    window.setFramerateLimit(60);

    // cargamos una textura (spritesheet)

    // TO-DO hacer un array de texturas e ir cargando las texturas según se pulse una tecla u otra.
    // PRUEBAS
    /*
    sf::Texture texture[4];
    if(!texture[0].loadFromFile("sprites/elfa.png")) { // cargamos la textura de la elfa
        std::cout << "No se ha podido cargar la textura 0" << std::endl;
    }
    if(!texture[1].loadFromFile("sprites/elfa.png")) { // cargamos la textura del soldado
        std::cout << "No se ha podido cargar la textura 0" << std::endl;
    }
    if(!texture[2].loadFromFile("sprites/elfa.png")) { // cargamos la textura del mago
        std::cout << "No se ha podido cargar la textura 0" << std::endl;
    }
    */

    // ESTO FUNCIONA
    sf::Texture texture;
    if (!texture.loadFromFile("sprites/elfa.png")) {
        std::cout << "No se ha podido cargar la textura" << std::endl;
        return 1;
    }



    // Montar las animaciones (los dos primeros valores del intRect son la posicion inicial del rectangulo y los dos segundos el tamaño)
    // ANIMACION IDLE
    Animation idle;
    idle.setSpriteSheet(texture);
    idle.addFrame(sf::IntRect(0, 0, 16, 28));
    idle.addFrame(sf::IntRect(16, 0, 16, 28));
    idle.addFrame(sf::IntRect(32, 0, 16, 28));
    idle.addFrame(sf::IntRect(48, 0, 16, 28));

    // ANIMACION CORRER DERECHA
    Animation walkRight;
    walkRight.setSpriteSheet(texture);
    walkRight.addFrame(sf::IntRect(0, 28, 16, 28));
    walkRight.addFrame(sf::IntRect(16, 28, 16, 28));
    walkRight.addFrame(sf::IntRect(32, 28, 16, 28));
    walkRight.addFrame(sf::IntRect(48, 28, 16, 28));


    Animation* currentAnimation = &idle;

    // montar el AnimatedSprite
    AnimatedSprite animatedSprite(sf::seconds(0.1), true, false);
    animatedSprite.setPosition(sf::Vector2f(screenDimensions / 2));

    sf::Clock frameClock;

    bool noTeclaPulsada = true;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
        }

        sf::Time frameTime = frameClock.restart();

        // COLOCAMOS LAS ANIMACIONES SEGÚN LAS TECLAS PULSADAS.
        // aqui comprobariamos is se quiere cambiar de textura.



        // Si se pulsa la tecla derecha camina a la derecha.
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            currentAnimation = &walkRight;
            noTeclaPulsada = false;
        }



        // después de ponerlas decimos que reproduzca la actual.
        animatedSprite.play(*currentAnimation);


        // if no key was pressed stop the animation
        if (noTeclaPulsada) {
            //animatedSprite.stop();
            currentAnimation = &idle;
        }

        noTeclaPulsada = true;

        // update AnimatedSprite
        animatedSprite.update(frameTime);

        // draw
        window.clear();
        window.draw(animatedSprite);
        window.display();
    }

    return 0;
}
