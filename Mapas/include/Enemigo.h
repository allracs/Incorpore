#ifndef ENEMY_H
#define ENEMY_H
#include "Entidad.h"
#include "Posicion.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
using namespace sf;
using namespace std;

class Enemigo : public Entidad{
    public:
        Enemigo(Vector2f);
        void setPath(std::vector<Posicion>);
        void update(float, RenderWindow&, int, FloatRect*);
        void update(float, RenderWindow&, int, FloatRect*, Posicion);
        void seguirCamino(Posicion);
    private:
        float dirMov;
        Vector2f movement; //movimiento del enemigo
        std::vector<Posicion> path;
};

#endif // ENEMY_H
