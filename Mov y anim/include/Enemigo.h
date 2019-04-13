#ifndef ENEMIGO_H
#define ENEMIGO_H
#include "Jugador.h"
#include "Bullet.h"


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
        sf::Vector2f movement; //movimiento del enemigo
        Animacion *actual;


        Animacion idle;
        Animacion run;


};

#endif // ENEMIGO_H
