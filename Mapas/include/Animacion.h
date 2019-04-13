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
        void update(float deltaTime, Vector2f movement);

        Sprite sprite;
    private:
        Texture texture;
        IntRect firstF;
        IntRect finalF;
        IntRect actualFrame;
        int incremento;

        float totalTime;
        float switchTime;

};

#endif // ANIMACION_H
