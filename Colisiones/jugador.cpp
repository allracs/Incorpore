
#include "jugador.h"

jugador::jugador()
{
    player = new sf::RectangleShape({30,30});
    player->setFillColor(sf::Color::Yellow);
    player->setPosition(300,300);

    vida = 30;
    velocidadJugador = 2;

    pos_anterior = {0.f,0.f};
}

///---------------------------------MOVIMIENTO
void jugador::move_izq()
{
    pos_anterior = player->getPosition();
    player->move(-velocidadJugador,0);
}
void jugador::move_der()
{
    pos_anterior = player->getPosition();
    player->move(velocidadJugador,0);
}
void jugador::move__abaj()
{
    pos_anterior = player->getPosition();
    player->move(0,velocidadJugador);
}
void jugador::move__arr()
{
    pos_anterior = player->getPosition();
    player->move(0,-velocidadJugador);
}


///------------------------------------GETTERS
sf::Vector2f jugador::getPos()
{
    return pos_anterior;
}

sf::RectangleShape jugador::getJugador()
{
    return *player;
}

int jugador::getVida()
{
    return vida;
}


///------------------------------------SETTERS
void jugador::setPosicion(int x, int y)
{
    player->setPosition(x,y);
}

void jugador::setVida()
{
    vida += 20;
}

void jugador::setPosAnterior()
{
    pos_anterior = player->getPosition();
}


///---------------------------------------DANIO
void jugador::danio(int num)
{
    //right = 1, left = 2, top = 3, down = 4
    vida -= 5;
    if(num == 1)
    {
       player->move(20,0);
    }
    else if(num == 2)
    {
       player->move(-20,0);
    }
    else if(num == 3)
    {
       player->move(0,-20);
    }
    else if(num == 4)
    {
       player->move(0,20);
    }
}

