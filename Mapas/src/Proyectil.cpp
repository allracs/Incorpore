#include "Proyectil.h"
#include <iostream>


Proyectil::Proyectil(sf::Vector2f posicion, sf::Vector2f dir)
{
    //ctor
    colision = sf::RectangleShape(sf::Vector2f(4,4));
    maxSpeed = 100.f;
    cooldown = 0;
    reloj = sf::Clock();
    //colision.setOrigin(colision.getOrigin().x + colision.getRadius(), colision.getOrigin().y + colision.getRadius());
    colision.setOrigin(colision.getOrigin().x + 2, colision.getOrigin().y + 2);
    colision.setPosition(posicion.x, posicion.y);
    currVel = dir*maxSpeed;

}

Proyectil::~Proyectil()
{
    //dtor
}

void Proyectil::update(){
    float tiempo = reloj.restart().asSeconds();
    colision.move(currVel* tiempo);
}

sf::RectangleShape Proyectil::getColision(){
    return colision;
}


void Proyectil::draw(sf::RenderWindow &window){
    window.draw(colision);
}


