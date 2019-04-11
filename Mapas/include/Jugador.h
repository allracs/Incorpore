#ifndef JUGADOR_H
#define JUGADOR_H

#include "Entidad.h" //<- Hijo de

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#include "Animacion.h"

using namespace std;
using namespace sf;

class Jugador : public Entidad{
    public:
        Jugador(Vector2f pos);
        void setColisionadores();
        void moverColisionadores(Vector2f);
        void procesarColisiones(int, FloatRect*);

        void update(float, RenderWindow&, int, FloatRect*);
        void moverse();
        void rotacionAtaque(RenderWindow&);

        RectangleShape getJugadorHitbox();
        RectangleShape getAtaqueHitbox();
        Vector2f getCenter();
        Vector2f getMousePos();
        Vector2f getMovement();
        Animacion* getActual();

        void draw(RenderWindow&);
        void drawBoundingBoxes(RenderWindow&);
        void showData();

    private:
        float speed;
        float dirMov;

        RectangleShape jugadorHitbox;
        RectangleShape ataqueHitbox;

        Vector2f playerCenter; //centro del jugador
        Vector2f mousePos; //posicion del raton
        Vector2f movement; //movimiento del jugador

        //Animaciones
        Animacion idle;
        Animacion run;
        Animacion* actual;
};
#endif
