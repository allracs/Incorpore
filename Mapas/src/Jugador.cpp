#include "../include/Jugador.h"
using namespace sf;

Jugador::Jugador(){

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
    cuadrado_arr->setPosition(sprite->getGlobalBounds().left, sprite->getPosition().y + 7.5);
    cuadrado_izq->setPosition(sprite->getGlobalBounds().left -0.5, sprite->getGlobalBounds().top+8);
    cuadrado_abj->setPosition(sprite->getGlobalBounds().left, sprite->getPosition().y + sprite->getGlobalBounds().height);
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
        }

        //SUPERIOR
        if(cuadrado_abj->getGlobalBounds().intersects(colisiones[i])){
            setColision(1);
        }

        //IZQUIERDA
        if(cuadrado_der->getGlobalBounds().intersects(colisiones[i])){
            setColision(3);
        }

        //DERECHA
        if(cuadrado_izq->getGlobalBounds().intersects(colisiones[i])){
            setColision(4);
        }
    }
}
