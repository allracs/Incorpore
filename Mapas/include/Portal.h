#ifndef PORTAL_H
#define PORTAL_H
#include <SFML/Graphics.hpp>
#include <iostream>

class Portal
{
    public:
        Portal(int,sf::Vector2i);
        virtual ~Portal();
        void draw(sf::RenderWindow&);
        void animacion();
        void update();
        sf::Sprite getPortal();
    private:
        sf::Texture tex;
        sf::Sprite *sprite;
        int ancho, alto, sep_ancho, sep_alto;
        sf::Clock clockAnimacion;
        sf::IntRect dim;
};

#endif // PORTAL_H
