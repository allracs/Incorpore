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
        void setPath(std::vector<Posicion>);
        void update(float, RenderWindow&, int, FloatRect*);
        void update(float, RenderWindow&, int, FloatRect*, Posicion, sf::RectangleShape enemigoHitbox, std::vector<Proyectil*>, bool*);
        void seguirCamino(Posicion, bool*);
        bool serAtacado(sf::RectangleShape hitbox);
        void compruebaColor();
        int getVida();
        bool getBorrado();

        void draw(sf::RenderWindow &app);



    private:
        float dirMov;
        Vector2f movement; //movimiento del enemigo
        std::vector<Posicion> path;
        int vida;
         //Matar al enemigo
        bool deleteSprite;
        sf::Clock cd, cInterp, cmov;
};

#endif // ENEMY_H
