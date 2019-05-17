#ifndef ARMA_H
#define ARMA_H
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "Enemigo.h"
#include "Proyectil.h"
using namespace std;
using namespace sf;


class Arma
{
    public:
        Arma(int, Vector2f);
        virtual ~Arma();
        void update(Vector2f, int nCol, FloatRect* colisiones);
        void rotacionAtaque(RenderWindow&, float, Vector2f, RectangleShape);
        void atacar(vector<Enemigo*>, int);
        void crearProyectil(sf::Vector2f centro);

        void empezarAnim();
        void terminAnim();


        RectangleShape getHitbox();
        Sprite getEspada();
        std::vector<Proyectil*> getProyectiles();
        Vector2f getMousePos();
        float getDireccionMov();
        int getOpcion();
    protected:

    private:
        float dMov;
        RectangleShape entidadHitbox;
        RectangleShape ataqueHitbox;
        Sprite espada; // Espada que se muestras encima de la hitbox.
        Texture textura; // Textura para el sprite de la espada
        int tipo;
        vector<Proyectil*> proyectiles;
        sf::Clock CDdisparo;
        Vector2f mousePos;

        sf::Clock animAtaque;
        bool cambiado;
};

#endif // ARMA_H
