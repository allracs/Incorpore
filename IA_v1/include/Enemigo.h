#ifndef ENEMIGO_H
#define ENEMIGO_H
#include <SFML/Graphics.hpp>

class Enemigo
{
    public:
        Enemigo();
        virtual ~Enemigo();
        void dibujar(sf::RenderWindow w);
        void mover(int x, int y);
        sf::Sprite getSprite();

    protected:

    private:
        sf::Texture *textura;
        sf::Sprite *sprite;
        int pos[2];
};

#endif // ENEMIGO_H
