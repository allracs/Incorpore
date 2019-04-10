#ifndef PLAYER_H
#define PLAYER_H
#include "Entidad.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Jugador : public Entidad{
    public:
        Jugador();
        void movimiento();
        void procesarColisiones(int, FloatRect*);
    private:
        int velocidad;
};
#endif
