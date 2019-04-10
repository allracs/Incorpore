#include "Enemigo.h"
#include "Jugador.h"
#include "Bullet.h"

Enemigo::Enemigo(sf::Vector2f pos)
{

    this->enemigoHitbox = sf::RectangleShape(sf::Vector2f(12, 12));
    this->enemigoHitbox.setPosition(pos);
    this->enemigoHitbox.setOrigin(12/2, 12/2);
    this->enemigoHitbox.setFillColor(sf::Color::Transparent);
    this->enemigoHitbox.setOutlineThickness(1.f);
    this->enemigoHitbox.setOutlineColor(sf::Color::Red);
    deleteSprite = false;

}

Enemigo::~Enemigo()
{
    //dtor
}
/*
void Enemigo::serAtacado(sf::RectangleShape hitbox){
    //El enemigo muere cuando la hitbox le toca y hacemos click
    if (hitbox.getGlobalBounds().intersects(enemigoHitbox.getGlobalBounds()) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        deleteSprite = true;
    }

    if (hitboxBullet.getGlobalBounds().intersects(enemigoHitbox.getGlobalBounds()))
        {
            deleteSprite = true;
        }
}
*/

void Enemigo::draw(sf::RenderWindow &app) {
    if(!deleteSprite){
        app.draw(enemigoHitbox);
    }
}

void Enemigo::update(float delta, sf::RenderWindow &app, sf::RectangleShape enemigoHitbox){

    //serAtacado(enemigoHitbox);

}

