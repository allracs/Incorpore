#include "../include/Enemigo.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#define he 0.08

Enemigo::Enemigo()
{
    textura = new sf::Texture();
    sprite = new sf::Sprite();

    textura->loadFromFile("img/rect.JPG");
    sprite->setTexture(*textura);
    sprite->setScale(0.2f, 0.2f);
    sprite->setOrigin(textura->getSize().x/2, textura->getSize().y/2);

    pos[0] = 30;
    pos[1] = 30;
    sprite->setPosition(pos[0], pos[1]);
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

    //std::cout << "se mueve " << x << " " << y << std::endl;
    float h = sqrt((pow(x, 2))+(pow(y, 2)));
    float xe = x * he / h;
    float ye = y * he / h;

    if(x > sprite->getPosition().x)
    {
        if(y > sprite->getPosition().y) //si el jugador esta arriba - derecha
        {
            sprite->move(xe * time.asMilliseconds(), ye * time.asMilliseconds());
            //std::cout << xe << " : " << ye << " -- " << xe-ye << std::endl;
        }
        else                            //si el jugador esta abajo - derecha
        {
            sprite->move(xe * time.asMilliseconds(), -ye * time.asMilliseconds());
            //std::cout << xe << " : " << -ye << " -- " << xe-ye << std::endl;
        }
    }
    else
    {
        if(y > sprite->getPosition().y) //si el jugador esta arriba - izquierda
        {
            sprite->move(-xe * time.asMilliseconds(), ye * time.asMilliseconds());
            //std::cout << -xe << " : " << ye << " -- " << xe-ye << std::endl;
        }
        else                            //si el jugador esta abajo - izquierda
        {
            sprite->move(-xe * time.asMilliseconds(), -ye * time.asMilliseconds());
            //std::cout << -xe << " : " << -ye << " -- " << xe-ye << std::endl;
        }
    }
}

void Enemigo::dibujar(sf::RenderWindow w)
{
    w.draw(*sprite);
}

sf::Sprite Enemigo::getSprite()
{
    return *sprite;
}
