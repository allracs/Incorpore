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

        int update(float, RenderWindow&, int, FloatRect*);
        void moverse();
        bool recibeDmg(RectangleShape, int, float);
        void cambiarArma(int opcion);
        bool cogePortal(FloatRect);
        bool cogeCofre(FloatRect);

        void compruebaColor();

        Arma getArma();
        Arma* getPuntArma();
        Vector2f getMovement();

        void controlarEsquivar();
        void esquivarInicio();

        float getCooldownAtaque();
        void restartCoolDownAtaque();

        void muerteJugador();
        void escudarse();
        void draw(sf::RenderWindow &);
    private:
        float dirMov;
        bool atacando;
        bool esquivando;
        bool puedeEsquivar;

        Clock cdEsquivar;
        Clock duracionEsquivar;
        Clock cInterp;
        Clock CDarma;
        Clock cd;

        Arma* arma;
//        Vector2f playerCenter; // centro del jugador
        Vector2f movement; // movimiento del jugador
        Clock dmgCD;
        Clock meleCD;

};
#endif
