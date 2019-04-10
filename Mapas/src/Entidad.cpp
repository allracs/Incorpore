#include "../include/Entidad.h"

Entidad::Entidad(){
    sprite = new sf::RectangleShape({16,16});
    sprite->setFillColor(Color::White);
    sprite->setPosition(150,50);


    //cuadrados para las colisiones
    //cuadrado derecha
    cuadrado_der = new sf::RectangleShape({0.5,8});
    cuadrado_der->setFillColor(sf::Color::Blue);
    //cuadrado izquierda
    cuadrado_izq = new sf::RectangleShape({0.5,8});
    cuadrado_izq->setFillColor(sf::Color::Blue);
    //cuadrado superior
    cuadrado_arr = new sf::RectangleShape({16,0.5});
    cuadrado_arr->setFillColor(sf::Color::Blue);
    //cuadrado inferior
    cuadrado_abj = new sf::RectangleShape({16,0.5});
    cuadrado_abj->setFillColor(sf::Color::Blue);
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


RectangleShape Entidad::getSprite(){
    return *sprite;
}
