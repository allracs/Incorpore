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
