#ifndef ANIMACION_H
#define ANIMACION_H

#include <SFML/Graphics.hpp>


class Animacion
{
    public:
        Animacion();
        virtual ~Animacion();
        void setAnimacion(char* nTextura, sf::IntRect firstF, sf::IntRect finalF, int incremento,float tiempo);
        void update(float deltaTime, sf::Vector2f movement);

        float getFrame();


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
