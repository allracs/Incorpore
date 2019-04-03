#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <cmath>
#include "Bullet.h"

int main()
{
    //Caracteristicas de la ventana y otras variables
    sf::Vector2i screenDimensions(1080,720);
    sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Incorpore");
    window.setFramerateLimit(60);
    //Para el posicionamiento de la hitbox
    sf::Vector2f playerCenter; //centro del jugador
    sf::Vector2f mousePos; //posicion del raton
    sf::Vector2f aimDirNorm; //normalizar vector
     sf::Vector2f aimDir;
    sf::Event event;
    sf::Clock frameClock;
    //Matar al enemigo
    bool deleteSprite = false;
    //Velocidad del jugador
    float speed = 200.f;

    //Jugador
    sf::CircleShape jugador(50);
    jugador.setPosition(sf::Vector2f(screenDimensions / 2));
    jugador.setFillColor(sf::Color::Green);
    bool rangeON = false;

    //Hitbox del jugador
    sf::RectangleShape hitbox;
    hitbox.setOutlineThickness(3);
    hitbox.setOutlineColor(sf::Color::Blue);
    hitbox.setFillColor(sf::Color::Transparent);
    hitbox.setSize(sf::Vector2f(120.f, 100.f));
    hitbox.setOrigin(0,50.f);

    //balas
    Bullet b1;
    std::vector<Bullet> bullets;



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
        playerCenter = sf::Vector2f(jugador.getPosition().x + jugador.getRadius(), jugador.getPosition().y+jugador.getRadius());
        mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
        aimDir = mousePos - playerCenter;
        aimDirNorm = aimDir / (float)sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));


        sf::Vertex Line[] =
        {
            sf::Vertex(sf::Vector2f(playerCenter)),
            sf::Vertex(sf::Vector2f(mousePos))
        };

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

        //Cambio de melee a distancia
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {
            if(rangeON)
                rangeON = false;
             else
                rangeON = true;

        }



        jugador.move(movement * frameTime.asSeconds());
        hitbox.setPosition(jugador.getPosition().x + jugador.getRadius(), jugador.getPosition().y + jugador.getRadius());

        if(rangeON == false){
            //El enemigo muere cuando la hitbox le toca y hacemos click
            if (hitbox.getGlobalBounds().intersects(enemigo.getGlobalBounds()) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                deleteSprite = true;
            }
        } else {
            //Shooting
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                b1.shape.setPosition(playerCenter);
                b1.currVelocity = aimDirNorm * b1.maxSpeed;

                bullets.push_back(Bullet(b1));


            }
        }

         for(size_t i = 0; i < bullets.size(); i++){
            bullets[i].shape.move(bullets[i].currVelocity);
            //Para borrar los proyectiles
            if(bullets[i].shape.getPosition().x < 0 || bullets[i].shape.getPosition().x > window.getSize().x ||
               bullets[i].shape.getPosition().y < 0 || bullets[i].shape.getPosition().y > window.getSize().y )
               {
                bullets.erase(bullets.begin()+i);
               }

            if (bullets[i].shape.getGlobalBounds().intersects(enemigo.getGlobalBounds()))
            {
                deleteSprite = true;
            }
        }


        //Dibujar
        window.clear();
        if (!deleteSprite) {
            window.draw(enemigo);
        }

        for(size_t i = 0; i < bullets.size(); i++)
            {
                window.draw(bullets[i].shape);
            }

        window.draw(hitbox);
        window.draw(jugador);
        window.draw(Line, 2, sf::Lines);
        window.display();
    }

    return 0;
}
