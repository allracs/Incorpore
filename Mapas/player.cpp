#include "player.h"
using namespace sf;

player::player(){
    jugador = new sf::RectangleShape({30,30});
    jugador->setFillColor(Color::White);
    jugador->setPosition(250,250);

    velocidad = 5;
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
