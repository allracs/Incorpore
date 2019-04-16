#ifndef JUGADOR_H
#define JUGADOR_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#include "Entidad.h" //<- Hijo de
#include "Enemigo.h"
#include "Animacion.h"
#include "Arma.h"

using namespace std;
using namespace sf;

class Jugador: public Entidad{
    public:
        Jugador(Vector2f pos);

        void update(float, RenderWindow&, int, FloatRect*);
        void moverse();
        bool recibeDmg(RectangleShape, int);
        void draw(sf::RenderWindow &);

        Vector2f getMovement();
        Arma getArma();
        int getVidas();
    private:
        float dirMov;
        int vidas;
        bool atacando;

        Arma* arma;
        Vector2f playerCenter; // centro del jugador
        Vector2f movement; // movimiento del jugador
        Clock dmgCD;
};
#endif
