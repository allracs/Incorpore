#ifndef JUGADOR_H
#define JUGADOR_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#include "Entidad.h" //<- Hijo de
#include "Enemigo.h"
#include "Animacion.h"
#include "Arma.h"
#include "Proyectil.h"

using namespace std;
using namespace sf;

class Jugador: public Entidad{
    public:
        Jugador(Vector2f pos);
        Jugador(Vector2f pos, int, int);

        void update(float, RenderWindow&, int, FloatRect*);
        void moverse();
        bool recibeDmg(RectangleShape, int);
        void draw(sf::RenderWindow &);
        void cambiarArma(int opcion);
        bool cogePortal(FloatRect);
        Vector2f getMovement();
        Arma getArma();
        Arma* getPuntArma();
        int getVidas();

        float getCooldownAtaque();
        void restartCoolDownAtaque();

    private:
        float dirMov;
        int vidas;
        bool atacando;

        sf::Clock cInterp;
        sf::Clock CDarma;

        Arma* arma;
//        Vector2f playerCenter; // centro del jugador
        Vector2f movement; // movimiento del jugador
        Clock dmgCD;
        Clock meleCD;

};
#endif
