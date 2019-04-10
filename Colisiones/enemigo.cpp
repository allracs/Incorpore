
#include "enemigo.h"

enemigo::enemigo()
{
    monstruo = new sf::RectangleShape({35,35});
    monstruo->setFillColor(sf::Color::Red);
    monstruo->setPosition(150,200);

    vida = 30;
}


sf::RectangleShape enemigo::getEnemigo()
{
    return *monstruo;
}


void enemigo::estado_enemigo()
{
    sf::Color color_monstruo = monstruo->getFillColor();
    if(color_monstruo == sf::Color::Red)
    {
        monstruo->setFillColor(sf::Color::Blue);
    }
    else if(color_monstruo == sf::Color::Blue)
    {
        monstruo->setFillColor(sf::Color::Red);
    }
}


void enemigo::movimiento_enemigo()
{
    if(monstruo->getPosition().y <= 420 && baja == true)
    {
        monstruo->move({0,1});
        if(monstruo->getPosition().y == 420)
        {
            baja = false;
        }
    }
    else if(monstruo->getPosition().y > 200 && baja == false)
    {
        monstruo->move({0,-1});
        if(monstruo->getPosition().y == 200)
        {
            baja = true;
        }
    }
}
