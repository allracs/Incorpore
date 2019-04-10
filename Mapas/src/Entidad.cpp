#include "../include/Entidad.h"

Entidad::Entidad(){
    sprite = new sf::RectangleShape({16,16});
    sprite->setFillColor(Color::Yellow);
    sprite->setPosition(150,50);
    //sprite->setOrigin(sprite->getPosition().x + sprite->getSize().x/2, sprite->getPosition().y + sprite->getSize().y/2);


    //cuadrados para las colisiones
    //cuadrado derecha
    cuadrado_der = new sf::RectangleShape({0.5,7.5});
    cuadrado_der->setFillColor(sf::Color::Blue);
    //cuadrado izquierda
    cuadrado_izq = new sf::RectangleShape({0.5,7.5});
    cuadrado_izq->setFillColor(sf::Color::Blue);
    //cuadrado superior
    cuadrado_arr = new sf::RectangleShape({16,0.5});
    cuadrado_arr->setFillColor(sf::Color::Red);
    //cuadrado inferior
    cuadrado_abj = new sf::RectangleShape({16,0.5});
    cuadrado_abj->setFillColor(sf::Color::Green);

    cuadrado_cen = new sf::RectangleShape({1,1});
    cuadrado_cen->setFillColor(sf::Color::Black);
}

void Entidad::setColision(int num){
    if(num == 1)
        colisiona_arriba = true;
    if(num == 2)
        colisiona_abajo = true;
    if(num == 3)
        colisiona_izquierda = true;
    if(num == 4)
        colisiona_derecha = true;
}

void Entidad::setPosicion(int x, int y)
{
    sprite->setPosition(x + sprite->getSize().x, y + sprite->getSize().y);
}

sf::RectangleShape Entidad::cuadradoder(){
    return *cuadrado_der;
}

sf::RectangleShape Entidad::cuadradoarr(){
    return *cuadrado_arr;
}

sf::RectangleShape Entidad::cuadradoizq(){
    return *cuadrado_izq;
}

sf::RectangleShape Entidad::cuadradoabaj(){
    return *cuadrado_abj;
}

sf::RectangleShape Entidad::cuadradocen(){
    return *cuadrado_cen;
}

RectangleShape Entidad::getSprite(){
    return *sprite;
}
