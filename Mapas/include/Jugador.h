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
        Jugador(Vector2f pos, int, int, int, int, float);

        int update(float, RenderWindow&, int, FloatRect*);
        void moverse();
        int recibeDmg(RectangleShape, int, float);
        void cambiarArma(int opcion);
        bool cogePortal(FloatRect);
        bool cogeCofre(FloatRect);
        bool getEscudo();
        void compruebaColor();

        Arma getArma();
        Arma* getPuntArma();
        Vector2f getMovement();

        void controlarEsquivar();
        void esquivarInicio();

        float getCooldownAtaque();
        void restartCoolDownAtaque();
        bool puedeCambiarArma();
        bool flagEsquivar();
        void muerteJugador();
        void escudarse();
        void draw(sf::RenderWindow &);

    private:
        float dirMov;
        bool atacando;
        bool esquivando;
        bool puedeEsquivar;
        bool flagArma;
        bool inicioArma = true;
        bool escudo;

        Clock cdEsquivar;
        Clock duracionEsquivar;
        Clock cInterp;
        Clock CDarma;
        Clock cd;

        bool mostrarTumba;
        sf::Texture tTumba;
        sf::Sprite tumba;

        Arma* arma;
//        Vector2f playerCenter; // centro del jugador
        Vector2f movement; // movimiento del jugador
        Clock dmgCD;
        Clock meleCD;

};
#endif
