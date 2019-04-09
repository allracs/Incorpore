#include <SFML/Graphics.hpp>

#include "Jugador.h"

Jugador::Jugador(sf::Vector2f pos)
{
    // Variables del jugador
    //this->jugador = sf::CircleShape(50);
    this->jugadorHitbox = sf::RectangleShape(sf::Vector2f(15, 20));
    this->jugadorHitbox.setPosition(pos);
    this->jugadorHitbox.setOrigin(18/2, 20/2);
    this->jugadorHitbox.setFillColor(sf::Color::Transparent);
    this->jugadorHitbox.setOutlineThickness(2.f);
    this->jugadorHitbox.setOutlineColor(sf::Color::Green);
    this->rangeON = false;
    speed = 200.f;
    movement = sf::Vector2f(0.f, 0.f);

    // Animaciones
    derecha.setAnimacion("caballero.png", sf::IntRect(0,0,16,28), sf::IntRect(48,0,16,28), 16, 0.1f);

    actual = &derecha;

    actual->sprite.setPosition(pos);

    //PRUEBAS CON LAS CAJAS DE LOS PERSONAJES.


    // Hitbox de ataque
    hitboxAtaque.setOutlineThickness(2);
    hitboxAtaque.setOutlineColor(sf::Color::Blue);
    hitboxAtaque.setFillColor(sf::Color::Transparent);
    hitboxAtaque.setSize(sf::Vector2f(30.f, 16.f));
    hitboxAtaque.setOrigin(0,16/2.f);
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
            this->movement.y -= speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            this->movement.y += speed;

        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            this->movement.x -= speed;
            derecha.sprite.setScale(-1.f, 1.f);

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            this->movement.x += speed;
            actual = &derecha;
            derecha.sprite.setScale(1.f, 1.f);

        }

}

sf::Vector2f Jugador::getCenter(){
    std::cout << "HA DEVUELTO EL PLAYER CENTER: " << playerCenter.x << "--" << playerCenter.y << std::endl;
    return playerCenter;
}

sf::Vector2f Jugador::getMousePos(){
    return this->mousePos;
}

sf::Vector2f Jugador::getMovement() {
    return this->movement;
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



