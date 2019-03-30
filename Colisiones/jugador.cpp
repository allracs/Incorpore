
#include "jugador.h"

jugador::jugador()
{
    player = new sf::RectangleShape({30,30});
    player->setFillColor(sf::Color::Yellow);
    player->setPosition(300,300);

    //cuadrados para las colisiones
    //cuadrado derecha
    cuadrado_der = new sf::RectangleShape({0.1,player->getGlobalBounds().height});
    cuadrado_der->setPosition(player->getGlobalBounds().left + player->getGlobalBounds().width, player->getPosition().y);
    cuadrado_der->setFillColor(sf::Color::Blue);
    //cuadrado superior
    cuadrado_arr = new sf::RectangleShape({player->getGlobalBounds().width,0.1});
    cuadrado_arr->setPosition(player->getGlobalBounds().left, player->getPosition().y);
    cuadrado_arr->setFillColor(sf::Color::Blue);

    vida = 30;
    velocidadJugador = 1.5;

    pos_anterior = {0.f,0.f};
    colisiona = 0;
}

///---------------------------------MOVIMIENTO
void jugador::movimiento()
{
    setPosAnterior();
     if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && colisiona != 4)
    {
        player->move({-velocidadJugador, 0});
        cuadrado_der->setPosition(player->getGlobalBounds().left + player->getGlobalBounds().width, player->getPosition().y);
        cuadrado_arr->setPosition(player->getGlobalBounds().left, player->getPosition().y -1);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && colisiona != 3)
    {
        player->move({velocidadJugador, 0});
        cuadrado_der->setPosition(player->getGlobalBounds().left + player->getGlobalBounds().width, player->getPosition().y);
        cuadrado_arr->setPosition(player->getGlobalBounds().left, player->getPosition().y -1);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && colisiona != 2)
    {
        player->move({0, -velocidadJugador});
        cuadrado_der->setPosition(player->getGlobalBounds().left + player->getGlobalBounds().width, player->getPosition().y);
        cuadrado_arr->setPosition(player->getGlobalBounds().left, player->getPosition().y -1);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && colisiona != 1)
    {
        player->move({0, velocidadJugador});
        cuadrado_der->setPosition(player->getGlobalBounds().left + player->getGlobalBounds().width, player->getPosition().y);
        cuadrado_arr->setPosition(player->getGlobalBounds().left, player->getPosition().y -1);
    }
    colisiona = 0;
}
void jugador::setColision(int num)
{
    colisiona = num;
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

sf::RectangleShape jugador::cuadradoder()
{
    return *cuadrado_der;
}

sf::RectangleShape jugador::cuadradoarr()
{
    return *cuadrado_arr;
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

