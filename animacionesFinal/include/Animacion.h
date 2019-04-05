#ifndef ANIMACION_H
#define ANIMACION_H

#include <SFML/Graphics.hpp>


class Animacion
{
    public:
        Animacion();
        //Animacion(char* nTextura, sf::IntRect firstF, sf::IntRect finalF, int incremento);
        virtual ~Animacion();
        void setAnimacion(char* nTextura, sf::IntRect firstF, sf::IntRect finalF, int incremento,float tiempo);
        void update(float deltaTime);

        sf::Sprite sprite;
    private:
        sf::Texture texture;
        sf::IntRect firstF;
        sf::IntRect finalF;
        sf::IntRect actualFrame;
        int incremento;

        float totalTime;
        float switchTime;

};

#endif // ANIMACION_H
