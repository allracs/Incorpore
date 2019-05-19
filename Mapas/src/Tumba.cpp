#include "Tumba.h"
#include <iostream>

Tumba::Tumba(sf::Vector2f pos)
{

    tTumba.loadFromFile("resources/sprites/blood.png");
    tumba.setTexture(tTumba);
    tumba.setOrigin(136/2, 136/2);
    tumba.setScale(0.13f,0.13f);

    /*OTRA TUMBA DISTINTA*/
//    tTumba.loadFromFile("resources/sprites/blood2.png");
//    tumba.setTexture(tTumba);
//    tumba.setOrigin(32/2,32/2);
//    tumba.setScale(0.5f, 0.5f);

    tumba.setPosition(pos);

}

Tumba::~Tumba()
{
    //dtor
}


void Tumba::draw(sf::RenderWindow &window){
    window.draw(tumba);
}
