#ifndef ENTIDAD_H
#define ENTIDAD_H
#include <SFML/Graphics.hpp>
#include "Animacion.h"
#include <math.h>
using namespace sf;

class Entidad{
    public:
        Entidad();
        RectangleShape getSprite();

        RectangleShape cuadradoder();
        RectangleShape cuadradoarr();
        RectangleShape cuadradoabaj();
        RectangleShape cuadradoizq();
        RectangleShape cuadradocen();

        void setColision(int);
        void setColisionadores();
        void moverColisionadores(Vector2f);
        void procesarColisiones(int, FloatRect*);
        void setCenter(Vector2f);

        Vector2f getCenter();
        RectangleShape getEntidadHitbox();
        RectangleShape getAtaqueHitbox();
        Animacion* getActual();
        void getPosCol(Vector2i& arr, Vector2i& der, Vector2i& aba, Vector2i& izq);

        void draw(RenderWindow&);
        void drawBoundingBoxes(RenderWindow&);
        void showData();
    protected:
        RectangleShape *sprite;
        RectangleShape entidadHitbox;
        RectangleShape ataqueHitbox;

        RectangleShape *cuadrado_der;
        RectangleShape *cuadrado_arr;
        RectangleShape *cuadrado_abj;
        RectangleShape *cuadrado_izq;
        RectangleShape *cuadrado_cen;

        Animacion idle;
        Animacion run;
        Animacion* actual;

        bool colisiona_arriba = false;
        bool colisiona_abajo = false;
        bool colisiona_derecha = false;
        bool colisiona_izquierda = false;

        Vector2f entityCenter;

        float speed;
};

#endif // ENTIDAD_H
