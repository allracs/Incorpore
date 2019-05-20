#ifndef ENTIDAD_H
#define ENTIDAD_H
#include <SFML/Graphics.hpp>
#include "Animacion.h"
#include "Proyectil.h"
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
        void setHP(float);
        void setAtaque(float);
        void setDefensa(float);
        void setVelocidad(float);

        Vector2f getCenter();
        RectangleShape getEntidadHitbox();
        RectangleShape getAtaqueHitbox();
        Animacion* getActual();
        float getHP();
        float getAtaque();
        float getDefensa();
        float getVelocidad();

        void draw(RenderWindow&);
        void drawBoundingBoxes(RenderWindow&);
        void muerteEntidad();
        void showData();
        void showStats();

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

//        Texture tTumba;
//        Sprite tumba;
//        bool mostrarTumba;

        Vector2f entityCenter;

        float hp, attack, defense, speed, spd;
};

#endif // ENTIDAD_H
