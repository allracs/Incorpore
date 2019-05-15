#ifndef PROYECTIL_H
#define PROYECTIL_H
#include <SFML/Graphics.hpp>
#include "Enemigo.h"


class Proyectil
{
    public:
        Proyectil(sf::Vector2f posicion, sf::Vector2f dir);
        virtual ~Proyectil();
        void update();
        void draw(sf::RenderWindow &window);
        sf::RectangleShape getColision();

    private:
        sf::RectangleShape colision;
        sf::Clock reloj;
        int cooldown;
        float maxSpeed;
        sf::Vector2f currVel;

};

#endif // PROYECTIL_H
