#include "Bala.h"

Bala::Bala()
{
    //ctor
    bala = sf::CircleShape(5);
    bala.setFillColor(sf::Color::Red);

}

Bala::~Bala()
{
    //dtor
}

void Bala::draw(sf::RenderWindow &window){
    window.draw(bala);
}

