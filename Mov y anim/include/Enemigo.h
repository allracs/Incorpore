#ifndef ENEMIGO_H
#define ENEMIGO_H
#include "Jugador.h"


class Enemigo
{
    public:
        Enemigo(sf::Vector2f pos);
        virtual ~Enemigo();
        void serAtacado(sf::RectangleShape hitbox);
        void draw(sf::RenderWindow &app);
        void update(float delta, sf::RenderWindow &app, sf::RectangleShape hitbox);

    private:
        sf::RectangleShape enemigoHitbox;
         //Matar al enemigo
    bool deleteSprite;

};

#endif // ENEMIGO_H
