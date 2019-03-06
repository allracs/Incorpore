#include "../include/Enemigo.h"
#include <SFML/Graphics.hpp>

Enemigo::Enemigo()
{
    textura = new sf::Texture();
    sprite = new sf::Sprite();
    textura->loadFromFile("img/rect.JPG");
    sprite->setTexture(*textura);
    sprite->setScale(0.2f, 0.2f);
    pos[0] = 30;
    pos[1] = 30;
    sprite->setPosition(pos[0], pos[1]);
}

Enemigo::~Enemigo()
{
    delete sprite;
    delete textura;
}

void Enemigo::mover(int x, int y)
{
    //mover
}

void Enemigo::dibujar(sf::RenderWindow w)
{
    w.draw(*sprite);
}

sf::Sprite Enemigo::getSprite()
{
    return *sprite;
}
