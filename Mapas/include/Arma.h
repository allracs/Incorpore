#ifndef ARMA_H
#define ARMA_H
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "Enemigo.h"
#include "Proyectil.h"
#include "Jefe.h"

using namespace std;
using namespace sf;


class Arma
{
    public:
        Arma(int, Vector2f);
        virtual ~Arma();
        void update(Vector2f, int nCol, FloatRect* colisiones);
        void rotacionAtaque(RenderWindow&, float, Vector2f, RectangleShape);
        void atacar(vector<Enemigo*>, int, float);
        void atacar(vector<Jefe*>, int);
        void crearProyectil(sf::Vector2f centro);

        void empezarAnim();
        void terminAnim();

        RectangleShape getHitbox();
        Sprite getEspada();
        vector<Proyectil*> getProyectiles();
        Vector2f getMousePos();
        float getDireccionMov();
        int getOpcion();


        void cambiarArma(int tipo);

    protected:

    private:
        float dMov;
        int tipo;
        bool cambiado;

        RectangleShape entidadHitbox;
        RectangleShape ataqueHitbox;
        Sprite espada; // Espada que se muestras encima de la hitbox.
        Texture textura; // Textura para el sprite de la espada

        vector<Proyectil*> proyectiles;

        Vector2f mousePos;
        IntRect* dim;

        Clock animAtaque;
        Clock CDdisparo;
};

#endif // ARMA_H
