#ifndef PROYECTIL_H
#define PROYECTIL_H
#include <SFML/Graphics.hpp>


class Proyectil
{
    public:
        Proyectil(sf::Vector2f posicion, sf::Vector2f dir);
        virtual ~Proyectil();
        void update();
        void draw(sf::RenderWindow &window);
        sf::RectangleShape getColision();

        void setHacolisionado(bool val);
        bool getHacolsionado();


    private:
        bool haColisionado;
        sf::RectangleShape colision;
        sf::Clock reloj;
        int cooldown;
        float maxSpeed;
        sf::Vector2f currVel;

};

#endif // PROYECTIL_H
