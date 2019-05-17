#ifndef PROYECTIL_H
#define PROYECTIL_H
#include <SFML/Graphics.hpp>


class Proyectil
{
    public:
        Proyectil(sf::Vector2f posicion, sf::Vector2f dir, float rotation);
        virtual ~Proyectil();
        void update(int nCol, sf::FloatRect* colisiones);
        void draw(sf::RenderWindow &window);
        sf::RectangleShape getColision();

        void setHacolisionado(bool val);
        bool getHacolsionado();
        void procesarColisiones(int nCol, sf::FloatRect*);


    private:
        bool haColisionado;
        sf::RectangleShape colision;
        sf::Clock reloj;
        int cooldown;
        float maxSpeed;
        sf::Vector2f currVel;
        sf::Clock autodestruccion;
        sf::Texture textura;
        sf::Sprite sprite;

};

#endif // PROYECTIL_H
