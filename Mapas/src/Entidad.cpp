#include "../include/Entidad.h"
#include <iostream>
using namespace std;
using namespace sf;

Entidad::Entidad(){
    sprite = new RectangleShape({16,16});
    sprite->setFillColor(Color::Yellow);
    sprite->setPosition(150,50);

    entidadHitbox = sf::RectangleShape(sf::Vector2f(12,12));
    entidadHitbox.setOrigin(12/2, 12/2);
    entidadHitbox.setFillColor(Color::Transparent);
    entidadHitbox.setOutlineThickness(1.f);
    entidadHitbox.setOutlineColor(Color::Green);

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

    speed = 75.f;
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

void Entidad::setColisionadores(){
    cuadrado_arr->setSize(Vector2f(11, 0.75));
    cuadrado_arr->setOrigin(Vector2f(11/2, 0.75/2));
    cuadrado_arr->setPosition(entidadHitbox.getGlobalBounds().left + 6.5, entidadHitbox.getGlobalBounds().top + entidadHitbox.getGlobalBounds().height/2 - 1.5);

    cuadrado_abj->setSize(Vector2f(11, 0.75));
    cuadrado_abj->setOrigin(Vector2f(11/2, 0.75/2));
    cuadrado_abj->setPosition(entidadHitbox.getGlobalBounds().left + 6.5, entidadHitbox.getGlobalBounds().top + entidadHitbox.getGlobalBounds().height + 1.8);

    cuadrado_izq->setSize(Vector2f(0.75, 6));
    cuadrado_izq->setOrigin(Vector2f(0.75/2, 6/2));
    cuadrado_izq->setPosition(entidadHitbox.getGlobalBounds().left, entidadHitbox.getGlobalBounds().top + entidadHitbox.getGlobalBounds().height/2 + 3.4);

    cuadrado_der->setSize(Vector2f(0.75, 6));
    cuadrado_der->setOrigin(Vector2f(0.75/2, 6/2));
    cuadrado_der->setPosition(entidadHitbox.getGlobalBounds().left + entidadHitbox.getGlobalBounds().width - 0.5, entidadHitbox.getGlobalBounds().top + entidadHitbox.getGlobalBounds().height/2 + 3.4);
}

void Entidad::moverColisionadores(Vector2f mov){
    cuadrado_arr->move(mov);
    cuadrado_izq->move(mov);
    cuadrado_abj->move(mov);
    cuadrado_der->move(mov);
}

void Entidad::procesarColisiones(int nColisiones, FloatRect* colisiones){
   for(int i = 0; i < nColisiones; i++){
        //INFERIOR
        if(cuadrado_arr->getGlobalBounds().intersects(colisiones[i])){
            setColision(2);
            cout <<  "Arriba" << endl;
        }

        //SUPERIOR
        if(cuadrado_abj->getGlobalBounds().intersects(colisiones[i])){
            setColision(1);
            cout <<  "Abajo" << endl;
        }

        //IZQUIERDA
        if(cuadrado_der->getGlobalBounds().intersects(colisiones[i])){
            setColision(3);
            cout <<  "Der" << endl;
        }

        //DERECHA
        if(cuadrado_izq->getGlobalBounds().intersects(colisiones[i])){
            setColision(4);
            cout <<  "Izq" << endl;
        }
    }
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

RectangleShape Entidad::getEntidadHitbox(){
    return entidadHitbox;
}

RectangleShape Entidad::getAtaqueHitbox(){
    return ataqueHitbox;
}

Animacion* Entidad::getActual() {
    return actual;
}

Vector2i* Entidad::getPosCol() {
    Vector2f res[4];
    res[0] = cuadrado_arr->getPosition();
    res[1] = cuadrado_der->getPosition();
    res[2] = cuadrado_abj->getPosition();
    res[3] = cuadrado_izq->getPosition();


    Vector2i ress[4];

    ress[0].x = round(res[0].x)/16;
    ress[0].y = round(res[0].y+0.05)/16;

    ress[1].x = round(res[1].x)/16;
    ress[1].y = round(res[1].y+0.05)/16;

    ress[2].x = round(res[2].x)/16;
    ress[2].y = round(res[2].y+0.05)/16;

    ress[3].x = round(res[3].x)/16;
    ress[3].y = round(res[3].y+0.05)/16;

    return ress;
}

void Entidad::draw(RenderWindow& target) {
    //target.draw(entidadHitbox);
    target.draw(actual->sprite);
    //target.draw(ataqueHitbox);
}

void Entidad::drawBoundingBoxes(RenderWindow& target){
    target.draw(*cuadrado_der);
    target.draw(*cuadrado_arr);
    target.draw(*cuadrado_abj);
    target.draw(*cuadrado_izq);
    //target.draw(*cuadrado_cen);
}

void Entidad::showData(){
    cout <<  "x: " << sprite->getPosition().x << endl;
    cout <<  "y: " << sprite->getPosition().y << endl;
    cout <<  "width: " << sprite->getSize().x << endl;
    cout <<  "height: " << sprite->getSize().x << endl;
}
