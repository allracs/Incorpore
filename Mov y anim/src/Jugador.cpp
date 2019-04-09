#include <SFML/Graphics.hpp>

#include "Jugador.h"

Jugador::Jugador(sf::Vector2f pos)
{
    // Variables del jugador
    //this->jugador = sf::CircleShape(50);
    this->jugadorHitbox = sf::RectangleShape(sf::Vector2f(60, 70));
    this->jugadorHitbox.setPosition(pos);
    this->jugadorHitbox.setOrigin(60/2, 70/2);
    this->jugadorHitbox.setFillColor(sf::Color::Transparent);
    this->jugadorHitbox.setOutlineThickness(2.f);
    this->jugadorHitbox.setOutlineColor(sf::Color::Green);
    this->rangeON = false;
    speed = 200.f;
    movement = sf::Vector2f(0.f, 0.f);

    // Animaciones
    derecha.setAnimacion("caballero.png", sf::IntRect(0,0,16,28), sf::IntRect(48,0,16,28), 16, 0.1f);
    derecha.sprite.setScale(5.f, 5.f);

    actual = &derecha;

    // Hitbox de ataque
    hitboxAtaque.setOutlineThickness(3);
    hitboxAtaque.setOutlineColor(sf::Color::Blue);
    hitboxAtaque.setFillColor(sf::Color::Transparent);
    hitboxAtaque.setSize(sf::Vector2f(100.f, 70.f));
    hitboxAtaque.setOrigin(0,70/2.f);

}

Jugador::~Jugador()
{
    //dtor

}


void Jugador::rotacionAtaque(sf::RenderWindow &app) {

    mousePos = sf::Vector2f(sf::Mouse::getPosition(app));

    float PI = 3.14159265;

    float dx = mousePos.x - playerCenter.x;
    float dy = mousePos.y - playerCenter.y;

    float rotation = (atan2(dy, dx)) * 180 / PI;
    hitboxAtaque.setRotation(rotation);
    //hitboxAtaque.setPosition(jugador.getPosition().x + jugador.getRadius(), jugador.getPosition().y + jugador.getRadius());
    hitboxAtaque.setPosition(jugadorHitbox.getPosition().x, jugadorHitbox.getPosition().y);
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

void Jugador::update(float delta, sf::RenderWindow &app){
    //playerCenter = sf::Vector2f(jugador.getPosition().x + jugador.getRadius(), jugador.getPosition().y+jugador.getRadius());
    playerCenter = sf::Vector2f(jugadorHitbox.getPosition().x, jugadorHitbox.getPosition().y);



    // MOVIMIENTO
    moverse(); // comprobar que el jugador se mueve
    jugadorHitbox.move(movement * delta); // mover al jugador.

    rotacionAtaque(app);



    // ANiMACIONES
    actual->update(delta, playerCenter);

}


void Jugador::draw(sf::RenderWindow &app) {
    app.draw(jugadorHitbox);
    app.draw(actual->sprite);
    app.draw(hitboxAtaque);

}



