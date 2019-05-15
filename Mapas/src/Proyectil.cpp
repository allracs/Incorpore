#include "Proyectil.h"
#include <iostream>


Proyectil::Proyectil(float radius, sf::Vector2f posicion, sf::Vector2f dir)
{
    //ctor
    colision = sf::CircleShape(radius);
    maxSpeed = 100.f;
    cooldown = 0;
    reloj = sf::Clock();
    colision.setOrigin(colision.getOrigin().x + colision.getRadius(), colision.getOrigin().y + colision.getRadius());
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

void Proyectil::draw(sf::RenderWindow &window){
    window.draw(colision);
}


