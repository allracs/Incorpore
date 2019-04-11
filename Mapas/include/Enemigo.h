#ifndef ENEMY_H
#define ENEMY_H
#include "Entidad.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Enemigo : public Entidad{
    public:
        Enemigo(Vector2f);
    private:
        float dirMov;
        Vector2f movement; //movimiento del jugador
};

#endif // ENEMY_H
