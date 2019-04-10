#ifndef PLAYER_H
#define PLAYER_H
#include "entidad.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class player : public entidad{
    public:
        player();
        void movimiento();
    private:
        int velocidad;
};
#endif
