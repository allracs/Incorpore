#ifndef ARMA_H
#define ARMA_H
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "Enemigo.h"
using namespace std;
using namespace sf;


class Arma
{
    public:
        Arma(int, Vector2f);
        virtual ~Arma();
        void update(Vector2f);
        void rotacionAtaque(RenderWindow&, float, Vector2f, RectangleShape);
        void atacar(int, vector<Enemigo*>, int);

        RectangleShape getHitbox();
        Sprite getEspada();
        Vector2f getMousePos();
        float getDireccionMov();
    protected:

    private:
        float dMov;
        RectangleShape entidadHitbox;
        RectangleShape ataqueHitbox;
        Sprite espada; // Espada que se muestras encima de la hitbox.
        Texture textura; // Textura para el sprite de la espada

        Vector2f mousePos;
};

#endif // ARMA_H
