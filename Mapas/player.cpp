#include "player.h"
using namespace sf;

player::player(){
    jugador = new sf::RectangleShape({16,16});
    jugador->setFillColor(Color::White);
    jugador->setPosition(150,50);

    velocidad = 2;
}

RectangleShape player::getPlayer(){
    return *jugador;
}

void player::movimiento(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        jugador->move(-velocidad,0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        jugador->move(velocidad,0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        jugador->move(0,velocidad);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        jugador->move(0,-velocidad);
    }
}
