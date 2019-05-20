#ifndef JEFE_H
#define JEFE_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include "Animacion.h"
#include "Proyectil.h"

#define he 0.1

class Jefe
{
    public:
        Jefe(sf::Vector2f);
        virtual ~Jefe();
        void update(sf::Vector2f,int,sf::FloatRect*);
        void draw(sf::RenderWindow&);
        bool restarVida();
        sf::RectangleShape* getCollision();
        std::vector<Proyectil*> getBalas();
        void destruirBala(int);

    protected:

    private:
        sf::RectangleShape *collision;
        std::vector<Proyectil*> balas;

        void estados(sf::Vector2f);
        sf::Clock cestados, cmov, cdispCD;
        sf::Vector2f posFdash, cd2dash;

        int estado, dirCaminar, vida;
        bool finDash;

        void dash();
        void caminar();
        void disparo8dir();
        void manejarDisp(int,sf::FloatRect*);

        Animacion idle;
        Animacion run;
        Animacion* actual;

};

#endif // JEFE_H
