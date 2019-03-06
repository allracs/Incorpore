#include "../include/Jugador.h"
#include <SFML/Graphics.hpp>

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

void Jugador::mover(int x, int y)
{
    //mover
}

void Jugador::dibujar(sf::RenderWindow w)
{
    w.draw(*sprite);
}

sf::Sprite Jugador::getSprite()
{
    return *sprite;
}
