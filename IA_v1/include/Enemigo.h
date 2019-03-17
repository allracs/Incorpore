#ifndef ENEMIGO_H
#define ENEMIGO_H
#include <SFML/Graphics.hpp>

class Enemigo
{
    public:
        Enemigo();
        virtual ~Enemigo();
        void dibujar(sf::RenderWindow w);
        void mover(int x, int y, sf::Clock c);
        sf::Sprite getSprite();
        float *getPos();

    protected:

    private:
        sf::Texture *textura;
        sf::Sprite *sprite;
        float pos[2];
        bool movn, attackn;

};

#endif // ENEMIGO_H
