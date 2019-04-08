
#include "objetos.h"

objetos::objetos()
{
    objeto = new sf::RectangleShape({20,20});
    objeto->setFillColor(sf::Color::Green);
    objeto->setPosition(400,400);

    dibujado = true;
}
objetos::~objetos()
{
    delete objeto;
}
sf::RectangleShape objetos::getObjeto()
{
    return *objeto;
}
