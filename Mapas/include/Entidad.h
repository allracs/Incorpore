#ifndef ENTIDAD_H
#define ENTIDAD_H
#include <SFML/Graphics.hpp>
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
        void setPosicion(int, int);

    protected:
        RectangleShape *sprite;

        RectangleShape *cuadrado_der;
        RectangleShape *cuadrado_arr;
        RectangleShape *cuadrado_abj;
        RectangleShape *cuadrado_izq;
        RectangleShape *cuadrado_cen;

        bool colisiona_arriba = false;
        bool colisiona_abajo = false;
        bool colisiona_derecha = false;
        bool colisiona_izquierda = false;
};

#endif // ENTIDAD_H
