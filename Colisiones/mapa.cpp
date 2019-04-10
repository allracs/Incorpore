
#include "mapa.h"

mapa::mapa()
{
    //ID DEL OBJETO MAPA
    pid = 103;

    //PARED SUPERIOR
    pared_superior = new sf::RectangleShape({700,20});
    pared_superior->setFillColor(sf::Color::Magenta);
    pared_superior->setPosition(50,100);

    //PARED INFERIOR
    pared_inferior = new sf::RectangleShape({700,20});
    pared_inferior->setFillColor(sf::Color::Magenta);
    pared_inferior->setPosition(50,550);

    //PARED DERECHA
    pared_derecha = new sf::RectangleShape({20,450});
    pared_derecha->setFillColor(sf::Color::Magenta);
    pared_derecha->setPosition(730,100);

    //PARED IZQUIERDA
    pared_izquierda = new sf::RectangleShape({20,450});
    pared_izquierda->setFillColor(sf::Color::Magenta);
    pared_izquierda->setPosition(50,100);

    //COLUMNA
    columna = new sf::RectangleShape({60,60});
    columna->setFillColor(sf::Color::Magenta);
    columna->setOrigin(columna->getSize().x /2 , columna->getSize().y /2);
    columna->setPosition(400,300);
}

sf::RectangleShape mapa::getParedSuperior()
{
    return *pared_superior;
}
sf::RectangleShape mapa::getParedInferior()
{
    return *pared_inferior;
}
sf::RectangleShape mapa::getParedDerecha()
{
    return *pared_derecha;
}
sf::RectangleShape mapa::getParedIzquierda()
{
    return *pared_izquierda;
}
sf::RectangleShape mapa::getColumna()
{
    return *columna;
}
