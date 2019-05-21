#ifndef BALA_H
#define BALA_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include "Enemigo.h"


class Bala
{
    public:
        Bala();
        virtual ~Bala();
        void draw(sf::RenderWindow &window);

    private:
        sf::CircleShape bala;
};

#endif // BALA_H
