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

    /*hp = 4;
    attack = 3;
    defense = 2;
    speed = 75.f;*/

    mostrarTumba=false;
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
    cuadrado_arr->setSize(Vector2f(8, 0.75));
    cuadrado_arr->setOrigin(cuadrado_arr->getGlobalBounds().width/2, cuadrado_arr->getGlobalBounds().height/2);
    cuadrado_arr->setPosition(entidadHitbox.getPosition().x, entidadHitbox.getGlobalBounds().top + entidadHitbox.getGlobalBounds().height/2 - 1.5);

    cuadrado_izq->setSize(Vector2f(0.75, 5.5));
    cuadrado_izq->setOrigin(cuadrado_izq->getGlobalBounds().width/2, cuadrado_izq->getGlobalBounds().height/2);
    cuadrado_izq->setPosition(entidadHitbox.getGlobalBounds().left - 0.5, entidadHitbox.getPosition().y + 4);

    cuadrado_abj->setSize(Vector2f(8, 0.75));
    cuadrado_abj->setOrigin(cuadrado_abj->getGlobalBounds().width/2, cuadrado_abj->getGlobalBounds().height/2);
    cuadrado_abj->setPosition(entidadHitbox.getPosition().x, entidadHitbox.getGlobalBounds().top + entidadHitbox.getGlobalBounds().height + 2);

    cuadrado_der->setSize(Vector2f(0.75, 5.5));
    cuadrado_der->setOrigin(cuadrado_der->getGlobalBounds().width/2, cuadrado_der->getGlobalBounds().height/2);
    cuadrado_der->setPosition(entidadHitbox.getGlobalBounds().left + entidadHitbox.getGlobalBounds().width + 0.5, entidadHitbox.getPosition().y + 4);
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
          //  cout <<  "Arriba" << endl;
        }

        //SUPERIOR
        if(cuadrado_abj->getGlobalBounds().intersects(colisiones[i])){
            setColision(1);
          //  cout <<  "Abajo" << endl;
        }

        //IZQUIERDA
        if(cuadrado_der->getGlobalBounds().intersects(colisiones[i])){
            setColision(3);
           // cout <<  "Der" << endl;
        }

        //DERECHA
        if(cuadrado_izq->getGlobalBounds().intersects(colisiones[i])){
            setColision(4);
          //  cout <<  "Izq" << endl;
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

float Entidad::getHP() {
    return hp;
}

float Entidad::getAtaque() {
    return attack;
}

float Entidad::getDefensa() {
    return defense;
}

float Entidad::getVelocidad() {
    return speed;
}

void Entidad::draw(RenderWindow& target) {
    //target.draw(entidadHitbox);
    //target.draw(actual->sprite);
    //target.draw(ataqueHitbox);
}

void Entidad::drawBoundingBoxes(RenderWindow& target){

    //target.draw(*cuadrado_der);
    //target.draw(*cuadrado_arr);
    //target.draw(*cuadrado_abj);
    //target.draw(*cuadrado_izq);
    //target.draw(*cuadrado_cen);

}


void Entidad::muerteEntidad(){
    mostrarTumba=true;

     if(!tTumba.loadFromFile("resources/sprites/muerte.png")){
        std::cout<<"No se cargo la tumba"<<std::endl;
    }
    tumba.setTexture(tTumba);
    tumba.setOrigin(16/2,20/2);
    tumba.setPosition(entityCenter);

}

void Entidad::showData(){
    cout <<  "x: " << sprite->getPosition().x << endl;
    cout <<  "y: " << sprite->getPosition().y << endl;
    cout <<  "width: " << sprite->getSize().x << endl;
    cout <<  "height: " << sprite->getSize().x << endl;
}
