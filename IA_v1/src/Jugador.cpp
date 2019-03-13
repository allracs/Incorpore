#include "../include/Jugador.h"
#include <SFML/Graphics.hpp>

#define vel 0.0002

Jugador::Jugador()
{
    textura = new sf::Texture();
    sprite = new sf::Sprite();

    textura->loadFromFile("img/rect1.JPG");

    sprite->setTexture(*textura);
    sprite->setScale(0.2f, 0.2f);

    pos[0] = 500;
    pos[1] = 500;
    sprite->setPosition(pos[0], pos[1]);
}

Jugador::~Jugador()
{
    delete sprite;
    delete textura;
}

void Jugador::mover(int x, int y, sf::Clock c)
{
    //mover
    sf::Time time = c.getElapsedTime();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        sprite->setScale(-0.2, 0.2);
        sprite->move({-vel * time.asMilliseconds(), 0});
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        sprite->setScale(-0.2, 0.2);
        sprite->move({vel * time.asMilliseconds(), 0});
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        sprite->setScale(-0.2, 0.2);
        sprite->move({0, -vel * time.asMilliseconds()});
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        sprite->setScale(-0.2, 0.2);
        sprite->move({0, vel * time.asMilliseconds()});
    }
}

void Jugador::dibujar(sf::RenderWindow w)
{
    w.draw(*sprite);
}

sf::Sprite Jugador::getSprite()
{
    return *sprite;
}

float *Jugador::getPos()
{
    pos[0] = sprite->getPosition().x;
    pos[1] = sprite->getPosition().y;
    return pos;
}
