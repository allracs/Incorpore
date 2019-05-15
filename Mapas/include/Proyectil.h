#ifndef PROYECTIL_H
#define PROYECTIL_H
#include <SFML/Graphics.hpp>


class Proyectil
{
    public:
        Proyectil(float radius, sf::Vector2f posicion, sf::Vector2f dir);
        virtual ~Proyectil();
        void update();
        void draw(sf::RenderWindow &window);

    private:
        sf::CircleShape colision;
        sf::Clock reloj;
        int cooldown;
        float maxSpeed;
        sf::Vector2f currVel;

};

#endif // PROYECTIL_H
