#include <SFML/Graphics.hpp>

#include "Jugador.h"

Jugador::Jugador(sf::Vector2f pos)
{
    // Variables del jugador

    this->jugadorHitbox = sf::RectangleShape(sf::Vector2f(12, 12));
    this->jugadorHitbox.setPosition(pos);
    this->jugadorHitbox.setOrigin(12/2, 12/2);
    this->jugadorHitbox.setFillColor(sf::Color::Transparent);
    this->jugadorHitbox.setOutlineThickness(1.f);
    this->jugadorHitbox.setOutlineColor(sf::Color::Green);
    this->rangeON = false;

    float dirMov = 1.f;


    speed = 200.f;
    movement = sf::Vector2f(0.f, 0.f);

    // Animaciones
    idle.setAnimacion("sprites/caballero.png", sf::IntRect(0,0,16,28), sf::IntRect(48,0,16,28), 16, 0.1f);
    idle.sprite.setOrigin(9,20);
    run.setAnimacion("sprites/caballero.png", sf::IntRect(0, 28, 16, 28), sf::IntRect(48, 28, 16, 28), 16, 0.1f);
    run.sprite.setOrigin(9,20);


    actual = &idle;

    actual->sprite.setPosition(pos);


    // Hitbox de ataque
    hitboxAtaque.setOutlineThickness(1);
    hitboxAtaque.setOutlineColor(sf::Color::Blue);
    hitboxAtaque.setFillColor(sf::Color::Transparent);
    hitboxAtaque.setSize(sf::Vector2f(20.f, 12.f));
    hitboxAtaque.setOrigin(0,6.f);
    hitboxAtaque.setPosition(pos);

}

Jugador::~Jugador()
{
    //dtor

}


void Jugador::rotacionAtaque(sf::RenderWindow &app) {
    sf::Vector2i pixelPos = sf::Vector2i(sf::Mouse::getPosition(app));

    mousePos = app.mapPixelToCoords(pixelPos);

    float PI = 3.14159265;

    float dx = mousePos.x - playerCenter.x;
    float dy = mousePos.y - playerCenter.y;


    float rotation = (atan2(dy, dx)) * 180 / PI;
    hitboxAtaque.setRotation(rotation);

}

void Jugador::moverse(){


    movement = sf::Vector2f(0.f, 0.f);
    //Movimiento del jugador

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        movement.y -= speed;
        if (actual != &run){
            std::cout << "CAMBIAMOS A RUN" << std::endl;
            actual = &run;
            actual->sprite.setPosition(playerCenter);
        }

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        movement.y += speed;
        if (actual != &run){
            std::cout << "CAMBIAMOS A RUN" << std::endl;
            actual = &run;
            actual->sprite.setPosition(playerCenter);
        }


    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        dirMov = -1.f;
        this->movement.x -= speed;

        if (actual != &run){
            std::cout << "CAMBIAMOS A RUN" << std::endl;
            actual = &run;
            actual->sprite.setPosition(playerCenter);
        }


        actual->sprite.setScale(1.f*dirMov, 1.f);


    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        dirMov = 1.f;
        this->movement.x += speed;

        if (actual != &run){
            std::cout << "CAMBIAMOS A RUN" << std::endl;
            actual = &run;
            actual->sprite.setPosition(playerCenter);
        }

        actual->sprite.setScale(1.f*dirMov, 1.f);

    }

    if(movement.x == 0 & movement.y == 0) {
        if (actual != &idle){
            std::cout << "CAMBIAMOS A IDLE" << std::endl;
            actual = &idle;
            actual->sprite.setPosition(playerCenter);
            actual->sprite.setScale(1.f*dirMov, 1.f);
        }
    }

}

sf::Vector2f Jugador::getCenter(){
    //std::cout << "HA DEVUELTO EL PLAYER CENTER: " << playerCenter.x << "--" << playerCenter.y << std::endl;
    return playerCenter;
}

sf::Vector2f Jugador::getMousePos(){
    return this->mousePos;
}

sf::Vector2f Jugador::getMovement() {
    return this->movement;
}

sf::RectangleShape Jugador::getHitboxAtaque(){
    return this->hitboxAtaque;
}

void Jugador::update(float delta, sf::RenderWindow &app){
    playerCenter = sf::Vector2f(jugadorHitbox.getPosition().x, jugadorHitbox.getPosition().y);
    rotacionAtaque(app);

    // MOVIMIENTO
    moverse(); // comprobar que el jugador se mueve
    jugadorHitbox.move(movement * delta); // mover al jugador.
    hitboxAtaque.move(movement * delta);

    actual->update(delta, movement);



    // ANiMACIONES

}


void Jugador::draw(sf::RenderWindow &app) {
    app.draw(jugadorHitbox);
    app.draw(actual->sprite);
    app.draw(hitboxAtaque);



}



