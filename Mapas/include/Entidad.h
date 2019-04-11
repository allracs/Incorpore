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
        void setColisionadores();
        void moverColisionadores(Vector2f);
        void procesarColisiones(int, FloatRect*);
        void setPosicion(int, int);

        void setCenter(Vector2f);
        Vector2f getCenter();
        void drawBoundingBoxes(RenderWindow&);
        void showData();
    protected:
        RectangleShape *sprite;
        RectangleShape entidadHitbox;

        RectangleShape *cuadrado_der;
        RectangleShape *cuadrado_arr;
        RectangleShape *cuadrado_abj;
        RectangleShape *cuadrado_izq;
        RectangleShape *cuadrado_cen;

        bool colisiona_arriba = false;
        bool colisiona_abajo = false;
        bool colisiona_derecha = false;
        bool colisiona_izquierda = false;

        Vector2f entityCenter;

        float speed;
};

#endif // ENTIDAD_H
