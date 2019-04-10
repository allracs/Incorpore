#ifndef PLAYER_H
#define PLAYER_H
#include "Entidad.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Player : public Entidad{
    public:
        Player();
        void movimiento();
    private:
        int velocidad;
};
#endif
