#include "Enemigo.h"

Enemigo::Enemigo()
{
    //ctor
}

Enemigo::~Enemigo()
{
    //dtor
}

void Enemigo::serAtacado(Jugador j){
    //El enemigo muere cuando la hitbox le toca y hacemos click
    if (j.getHitboxAtaque().getGlobalBounds().intersects(enemigoHitbox.getGlobalBounds()) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        deleteSprite = true;
    }

}


