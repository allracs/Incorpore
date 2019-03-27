#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <cmath>

int main()
{
    //Caracteristicas de la ventana y otras variables
    sf::Vector2i screenDimensions(1080,720);
    sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Incorpore");
    window.setFramerateLimit(60);
    //Para el posicionamiento de la hitbox
    sf::Vector2f playerCenter;
    sf::Vector2i mousePos;
    sf::Event event;
    sf::Clock frameClock;
    //Matar al enemigo
    bool deleteSprite = false;
    //Velocidad del jugador
    float speed = 200.f;

    //Jugador
    sf::CircleShape jugador(50);
    jugador.setPosition(sf::Vector2f(screenDimensions / 2));

    //Hitbox del jugador
    sf::RectangleShape hitbox;
    hitbox.setFillColor(sf::Color::Green);
    hitbox.setSize(sf::Vector2f(120.f, 50.f));

    //Enemigo
	sf::RectangleShape enemigo;
	enemigo.setFillColor(sf::Color::Red);
	enemigo.setSize(sf::Vector2f(50.f, 50.f));
	enemigo.setPosition(450.f, 300.f);


    while (window.isOpen())
    {

        //Posicion del mouse para la rotacion persiguiendo al raton
        float mouseX = sf::Mouse::getPosition().x;
        float mouseY = sf::Mouse::getPosition().y;
        playerCenter = sf::Vector2f(jugador.getPosition().x + jugador.getRadius(), jugador.getPosition().y-jugador.getRadius());
        mousePos = sf::Mouse::getPosition(window);

        float PI = 3.14159265;

        float dx = mousePos.x - playerCenter.x;
        float dy = mousePos.y - playerCenter.y;



        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
        }

        sf::Time frameTime = frameClock.restart();

        //Rotacion de la hitbox
        float rotation = (atan2(dy, dx)) * 180 / PI;
        hitbox.setRotation(rotation);


        //Movimiento del jugador
        sf::Vector2f movement(0.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            movement.y -= speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            movement.y += speed;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            movement.x -= speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            movement.x += speed;
        }

        jugador.move(movement * frameTime.asSeconds());
        hitbox.setPosition(jugador.getPosition().x + jugador.getRadius(), jugador.getPosition().y + jugador.getRadius());


        //El enemigo muere cuando la hitbox le toca y hacemos click
        if (hitbox.getGlobalBounds().intersects(enemigo.getGlobalBounds()) && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
					deleteSprite = true;
				}


        //Dibujar
        window.clear();
        if (!deleteSprite) {
            window.draw(enemigo);
        }
        window.draw(hitbox);
        window.draw(jugador);
        window.display();
    }

    return 0;
}
