#include <SFML/Graphics.hpp>
#include "Jugador.h"

Jugador::Jugador(sf::Vector2f pos)
{
    //ctor
    this->jugador = sf::CircleShape(50);
    this->jugador.setPosition(pos);
    this->jugador.setFillColor(sf::Color::Transparent);
    this->rangeON = false;
    speed = 200.f;
    movement = sf::Vector2f(0.f, 0.f);

    derecha.setAnimacion("caballero.png", sf::IntRect(0,0,16,28), sf::IntRect(48,0,16,28), 16, 0.1f);
    derecha.sprite.setScale(5.f, 5.f);

    actual = &derecha;


}

Jugador::~Jugador()
{
    //dtor

}

void Jugador::moverse(){

        movement = sf::Vector2f(0.f, 0.f);
        //Movimiento del jugador
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            this->movement.y -= speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            this->movement.y += speed;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            this->movement.x -= speed;
            derecha.sprite.setScale(-5.f, 5.f);

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            this->movement.x += speed;
            actual = &derecha;
            derecha.sprite.setScale(5.f, 5.f);

        }

}

void Jugador::update(float delta){
    playerCenter = sf::Vector2f(jugador.getPosition().x + jugador.getRadius(), jugador.getPosition().y+jugador.getRadius());
    moverse();
    jugador.move(movement * delta);

    actual->update(delta, playerCenter);

}




