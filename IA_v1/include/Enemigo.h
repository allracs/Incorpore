#ifndef ENEMIGO_H
#define ENEMIGO_H
<<<<<<< HEAD:IA_v1/include/Enemigo.h
#include <SFML/Graphics.hpp>
=======
#include "Jugador.h"
#include "Bullet.h"

>>>>>>> mapa-colisiones:Mov y anim/include/Enemigo.h

class Enemigo
{
    public:
        Enemigo(sf::Vector2f pos);
        virtual ~Enemigo();
<<<<<<< HEAD:IA_v1/include/Enemigo.h
        void dibujar(sf::RenderWindow w);
        void mover(int x, int y, sf::Clock c);
        sf::Sprite getSprite();
        float *getPos();
        bool getMoveState();
        bool getAttackState();

    protected:

    private:
        sf::Texture *textura;
        sf::Sprite *sprite;
        float pos[2];
        bool movn, attackn;
=======
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

>>>>>>> mapa-colisiones:Mov y anim/include/Enemigo.h

};

#endif // ENEMIGO_H
