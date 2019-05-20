#include "Proyectil.h"
#include <iostream>


Proyectil::Proyectil(sf::Vector2f posicion, sf::Vector2f dir, float rotation, int tipo)
{
    //ctor
    if(tipo==1)
    {
        if(!textura.loadFromFile("resources/sprites/EnergyBall.png")){
            std::cout<<"No se cargo el sprite de la bola de energia sideral"<<std::endl;
        }
    } else if(tipo==2)
    {
        if(!textura.loadFromFile("resources/sprites/bolaEnemigo.png")){
            std::cout<<"No se cargo el sprite de la bola de energia sideral"<<std::endl;
        }
    }

    sprite.setTexture(textura);
    if(tipo==1)
    sprite.setOrigin(10/2, 5/2);
    else
    {
        sprite.setOrigin(10, 5);
        sprite.setScale({0.6,0.6});
    }

    //std::cout << "POSICION: " << colision.getPosition().x << " ," << colision.getPosition().y << std::endl;
    sprite.setPosition(posicion);

    colision = sf::RectangleShape(sf::Vector2f(4,4));
    colision.setFillColor(sf::Color::Transparent);
    maxSpeed = 180.f;
    cooldown = 0;
    reloj = sf::Clock();
    autodestruccion = sf::Clock();
    colision.setOrigin(colision.getOrigin().x + 2, colision.getOrigin().y + 2);
    colision.setPosition(posicion.x, posicion.y);
    currVel = dir*maxSpeed;
    haColisionado = false;
}

Proyectil::~Proyectil()
{
    //dtor
}

void Proyectil::update(int nCol, sf::FloatRect* colisiones){

    float tiempo = reloj.restart().asSeconds();
    colision.move(currVel* tiempo);
    sprite.move(currVel* tiempo);
    procesarColisiones(nCol, colisiones);
}

void Proyectil::procesarColisiones(int nCol, sf::FloatRect* colisiones){
    for(int i = 0; i < nCol; i++){
        //INFERIOR
        if(colision.getGlobalBounds().intersects(colisiones[i])){
            setHacolisionado(true);
        }
    }
}

sf::RectangleShape Proyectil::getColision(){
    return colision;
}

void Proyectil::setHacolisionado(bool val) {
    haColisionado = val;
}

bool Proyectil::getHacolsionado() {
    return haColisionado;
}

void Proyectil::draw(sf::RenderWindow &window){
    window.draw(colision);
    window.draw(sprite);
}


