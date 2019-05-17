#ifndef ANTORCHA_H
#define ANTORCHA_H
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

class Antorcha
{
    public:
        Antorcha(Vector2f);
        virtual ~Antorcha();
        void draw(RenderWindow&);
        void drawFire(RenderWindow&);
        void animacion();
        void update();
        Sprite getAntorcha();
    private:
        Texture tex;
        Sprite *sprite, *spriteFire;
        Clock clockAnimacion;
        IntRect dim, dimFire;
};

#endif // ANTORCHA_H
