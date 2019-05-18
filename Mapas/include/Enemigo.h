#ifndef ENEMY_H
#define ENEMY_H
#include "Entidad.h"
#include "Posicion.h"
#include "Proyectil.h"
#include <iostream>
#include <vector>
using namespace sf;
using namespace std;

class Enemigo : public Entidad{
    public:
        Enemigo(Vector2f);
        void setPath(vector<Posicion>);
        void update(float, RenderWindow&, int, FloatRect*);
        void update(float, RenderWindow&, int, FloatRect*, Posicion, RectangleShape enemigoHitbox, vector<Proyectil*>, bool*, float);
        void seguirCamino(Posicion, bool*);
        bool serAtacado(RectangleShape, float);
        void compruebaColor();

        int getVida();
        bool getBorrado();

        void draw(RenderWindow &app);



    private:
        float dirMov;
        bool deleteSprite;

        Vector2f movement; //movimiento del enemigo
        vector<Posicion> path;
        Clock cd, cInterp, cmov;
};

#endif // ENEMY_H
