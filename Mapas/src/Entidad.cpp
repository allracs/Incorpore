#include "../include/Entidad.h"
using namespace std;
using namespace sf;

Entidad::Entidad(){
    sprite = new RectangleShape({16,16});
    sprite->setFillColor(Color::Yellow);
    sprite->setPosition(150,50);

    cuadrado_der = new RectangleShape({0.5,7.5});
    cuadrado_der->setFillColor(Color::Blue);
    cuadrado_izq = new RectangleShape({0.5,7.5});
    cuadrado_izq->setFillColor(Color::Blue);
    cuadrado_arr = new RectangleShape({16,0.5});
    cuadrado_arr->setFillColor(Color::Red);
    cuadrado_abj = new RectangleShape({16,0.5});
    cuadrado_abj->setFillColor(Color::Green);
    cuadrado_cen = new RectangleShape({1,1});
    cuadrado_cen->setFillColor(Color::Black);
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

void Entidad::setPosicion(int x, int y){
    sprite->setPosition(x + sprite->getSize().x, y + sprite->getSize().y);
}

void Entidad::setCenter(Vector2f centro){
    entityCenter = centro;
}

RectangleShape Entidad::cuadradoder(){
    return *cuadrado_der;
}

RectangleShape Entidad::cuadradoarr(){
    return *cuadrado_arr;
}

RectangleShape Entidad::cuadradoizq(){
    return *cuadrado_izq;
}

RectangleShape Entidad::cuadradoabaj(){
    return *cuadrado_abj;
}

RectangleShape Entidad::cuadradocen(){
    return *cuadrado_cen;
}

RectangleShape Entidad::getSprite(){
    return *sprite;
}

Vector2f Entidad::getCenter(){
    return entityCenter;
}
