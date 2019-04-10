#include <iostream>
#include "../include/Jugador.h"
using namespace std;
using namespace sf;

Jugador::Jugador(){
    sprite->setOrigin(sprite->getSize().x/2, sprite->getSize().y/2);
    cout <<  "x: " << sprite->getPosition().x << endl;
    cout <<  "y: " << sprite->getPosition().y << endl;
    cout <<  "width: " << sprite->getSize().x << endl;
    cout <<  "height: " << sprite->getSize().x << endl;
    velocidad = 2;
}

///---------------------------------MOVIMIENTO
void Jugador::movimiento(){

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && colisiona_derecha != true){
        sprite->move(-velocidad, 0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && colisiona_izquierda != true){
        sprite->move(velocidad, 0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && colisiona_abajo != true){
        sprite->move(0, -velocidad);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && colisiona_arriba != true){
        sprite->move(0, velocidad);

    }

    cuadrado_der->setPosition(sprite->getGlobalBounds().left + sprite->getGlobalBounds().width, sprite->getGlobalBounds().top + 8);
    cuadrado_arr->setPosition(sprite->getGlobalBounds().left, sprite->getPosition().y - 0.01);
    cuadrado_izq->setPosition(sprite->getGlobalBounds().left -0.5, sprite->getGlobalBounds().top+8);
    cuadrado_abj->setPosition(sprite->getGlobalBounds().left, sprite->getPosition().y + sprite->getGlobalBounds().height/2 - 0.49);
    cuadrado_cen->setPosition(sprite->getPosition().x - 0.25, sprite->getPosition().y - 0.25);

    colisiona_abajo = false;
    colisiona_arriba = false;
    colisiona_derecha = false;
    colisiona_izquierda = false;
}

void Jugador::procesarColisiones(int nColisiones, FloatRect* colisiones){
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

void Jugador::drawBoundingBoxes(RenderWindow& target){
    target.draw(*cuadrado_der);
    target.draw(*cuadrado_arr);
    target.draw(*cuadrado_abj);
    target.draw(*cuadrado_izq);
    target.draw(*cuadrado_cen);
}
