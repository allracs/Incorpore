
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
void jugador::movimiento(int num)
{
    //left = 1, right = 2, down = 3, up = 4
    pos_anterior = player->getPosition();
    if( num == 1 )
    {
        player->move(-velocidadJugador,0);
    }
    if( num == 2 )
    {
        player->move(velocidadJugador,0);
    }
    if( num == 3 )
    {
        player->move(0,velocidadJugador);
    }
    if( num == 4 )
    {
        player->move(0,-velocidadJugador);
    }
}


//GETTERS
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


//SETTERS
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

