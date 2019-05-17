#ifndef ANIMACION_H
#define ANIMACION_H

#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Animacion
{
    public:
        Animacion();
        virtual ~Animacion();
        void setAnimacion(char* nTextura, IntRect firstF, IntRect finalF, int incremento,float tiempo);
        void update(Vector2f movement, float mTime);
        Sprite sprite;

    private:
        Texture texture;
        IntRect firstF;
        IntRect finalF;
        IntRect actualFrame;
        int incremento;
//        float totalTime;
        float switchTime;
        sf::Clock clock;

};

#endif // ANIMACION_H

/*

#ifndef ANIMATION_H
#define ANIMATION_H
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <iostream>

class Animation
{
    public:
        Animation(sf::Texture,float,float,float,float, int);
        virtual ~Animation();
        void update();
        void draw(sf::RenderWindow&);
        void die();

    protected:

    private:
        sf::Sprite *sprite;
        sf::Clock clock;
        int pos, x, y, w, h, nmax;
};

#endif // ANIMATION_H

*/
