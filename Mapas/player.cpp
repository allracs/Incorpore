#include "player.h"
using namespace sf;

player::player(){
    jugador = new sf::RectangleShape({16,16});
    jugador->setFillColor(Color::White);
    jugador->setPosition(150,50);

    //cuadrados para las colisiones
    //cuadrado derecha
    cuadrado_der = new sf::RectangleShape({0.1,jugador->getGlobalBounds().height});
    cuadrado_der->setPosition(jugador->getGlobalBounds().left + jugador->getGlobalBounds().width, jugador->getGlobalBounds().top);
    cuadrado_der->setFillColor(sf::Color::Blue);
    //cuadrado izqquieda
    cuadrado_izq = new sf::RectangleShape({0.1,jugador->getGlobalBounds().height});
    cuadrado_izq->setPosition(jugador->getGlobalBounds().left, jugador->getGlobalBounds().top);
    cuadrado_izq->setFillColor(sf::Color::Blue);
    //cuadrado superior
    cuadrado_arr = new sf::RectangleShape({jugador->getGlobalBounds().width,0.1});
    cuadrado_arr->setPosition(jugador->getGlobalBounds().left, jugador->getPosition().y);
    cuadrado_arr->setFillColor(sf::Color::Blue);
    //cuadrado inferior
    cuadrado_abj = new sf::RectangleShape({jugador->getGlobalBounds().width,0.1});
    cuadrado_abj->setPosition(jugador->getGlobalBounds().left, jugador->getPosition().y + jugador->getGlobalBounds().height);
    cuadrado_abj->setFillColor(sf::Color::Blue);

    velocidad = 2;
    colisiona = 1;
}

RectangleShape player::getPlayer(){
    return *jugador;
}


///---------------------------------MOVIMIENTO
void player::movimiento()
{
     if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && colisiona != 4)
    {
        jugador->move(-velocidad, 0);
        cuadrado_der->setPosition(jugador->getGlobalBounds().left + jugador->getGlobalBounds().width, jugador->getGlobalBounds().top);
        cuadrado_arr->setPosition(jugador->getGlobalBounds().left, jugador->getPosition().y -1);
        cuadrado_izq->setPosition(jugador->getGlobalBounds().left, jugador->getGlobalBounds().top);
        cuadrado_abj->setPosition(jugador->getGlobalBounds().left, jugador->getPosition().y + jugador->getGlobalBounds().height);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && colisiona != 3)
    {
        jugador->move(velocidad, 0);
        cuadrado_der->setPosition(jugador->getGlobalBounds().left + jugador->getGlobalBounds().width, jugador->getGlobalBounds().top);
        cuadrado_arr->setPosition(jugador->getGlobalBounds().left, jugador->getPosition().y -1);
        cuadrado_izq->setPosition(jugador->getGlobalBounds().left, jugador->getGlobalBounds().top);
        cuadrado_abj->setPosition(jugador->getGlobalBounds().left, jugador->getPosition().y + jugador->getGlobalBounds().height);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && colisiona != 2)
    {
        jugador->move(0, -velocidad);
        cuadrado_der->setPosition(jugador->getGlobalBounds().left + jugador->getGlobalBounds().width, jugador->getGlobalBounds().top);
        cuadrado_arr->setPosition(jugador->getGlobalBounds().left, jugador->getPosition().y -1);
        cuadrado_izq->setPosition(jugador->getGlobalBounds().left, jugador->getGlobalBounds().top);
        cuadrado_abj->setPosition(jugador->getGlobalBounds().left, jugador->getPosition().y + jugador->getGlobalBounds().height);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && colisiona != 1)
    {
        jugador->move(0, velocidad);
        cuadrado_der->setPosition(jugador->getGlobalBounds().left + jugador->getGlobalBounds().width, jugador->getGlobalBounds().top);
        cuadrado_arr->setPosition(jugador->getGlobalBounds().left, jugador->getPosition().y -1);
        cuadrado_izq->setPosition(jugador->getGlobalBounds().left, jugador->getGlobalBounds().top);
        cuadrado_abj->setPosition(jugador->getGlobalBounds().left, jugador->getPosition().y + jugador->getGlobalBounds().height);
    }
    colisiona = 0;
}

void player::setColision(int num)
{
    colisiona = num;
}

void player::setPosicion(int x, int y)
{
    jugador->setPosition(x,y);
}

sf::RectangleShape player::cuadradoder(){
    return *cuadrado_der;
}

sf::RectangleShape player::cuadradoarr(){
    return *cuadrado_arr;
}

sf::RectangleShape player::cuadradoizq(){
    return *cuadrado_izq;
}

sf::RectangleShape player::cuadradoabaj(){
    return *cuadrado_abj;
}

