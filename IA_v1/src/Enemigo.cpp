#include "../include/Enemigo.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#define he 0.12

Enemigo::Enemigo()
{
    textura = new sf::Texture();
    sprite = new sf::Sprite();

    textura->loadFromFile("img/rect.JPG");
    sprite->setTexture(*textura);
    sprite->setScale(0.1f, 0.1f);
    sprite->setOrigin(textura->getSize().x/2, textura->getSize().y/2);

    pos[0] = 30;
    pos[1] = 30;
    sprite->setPosition(pos[0], pos[1]);
    movn = false;
    attackn = false;
}

Enemigo::~Enemigo()
{
    delete sprite;
    delete textura;
}

void Enemigo::mover(int x, int y, sf::Clock c)
{
    //mover
    sf::Time time = c.getElapsedTime();

    int dx, dy;
    dx = pos[0] - x;
    dy = pos[1] - y;

    //std::cout << "se mueve " << x << " " << y << std::endl;
    float h = sqrt((pow(dx, 2))+(pow(dy, 2)));
    float xe = dx * he / h;
    float ye = dy * he / h;
    if(h > 100){
        if(dx > sprite->getPosition().x)
        {
            if(dy > sprite->getPosition().y) //si el jugador esta arriba - derecha
            {
                sprite->move(xe * time.asMilliseconds(), ye * time.asMilliseconds());
                movn = true;
                attackn = false;
                //std::cout << xe << " : " << ye << " -- " << xe-ye << std::endl;
            }
            else                            //si el jugador esta abajo - derecha
            {
                sprite->move(xe * time.asMilliseconds(), -ye * time.asMilliseconds());
                movn = true;
                attackn = false;
                //std::cout << xe << " : " << -ye << " -- " << xe-ye << std::endl;
            }
        }
        else
        {
            if(dy > sprite->getPosition().y) //si el jugador esta arriba - izquierda
            {
                sprite->move(-xe * time.asMilliseconds(), ye * time.asMilliseconds());
                movn = true;
                attackn = false;
                //std::cout << -xe << " : " << ye << " -- " << xe-ye << std::endl;
            }
            else                            //si el jugador esta abajo - izquierda
            {
                sprite->move(-xe * time.asMilliseconds(), -ye * time.asMilliseconds());
                movn = true;
                attackn = false;
                //std::cout << -xe << " : " << -ye << " -- " << xe-ye << std::endl;
            }
        }
    }
    else
    {
        attackn = true;
        movn = false;
    }
    std::cout << "Estado--> moviendo: " << movn << " -- atacando: " << attackn << " -- h: " << h << std::endl;

}

void Enemigo::dibujar(sf::RenderWindow w)
{
    w.draw(*sprite);
}

sf::Sprite Enemigo::getSprite()
{
    return *sprite;
}

float *Enemigo::getPos()
{
    pos[0] = sprite->getPosition().x;
    pos[1] = sprite->getPosition().y;
    return pos;
}

bool Enemigo::getMoveState()
{
    return movn;
}

bool Enemigo::getAttackState()
{
    return attackn;
}
