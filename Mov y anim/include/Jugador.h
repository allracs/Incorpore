#include <SFML/Graphics.hpp>
#ifndef JUGADOR_H
#define JUGADOR_H
#include "Entidad.h"
#include "Animacion.h"



class Jugador
{
    public:
        Jugador(sf::Vector2f pos);
        virtual ~Jugador();

        //Mover el jugador
        void update(float delta);
        void moverse();
         //Jugador
        sf::CircleShape jugador;
        Animacion derecha;
        Animacion izquierda;


    private:

        float speed; //Velocidad del jugador
        sf::Vector2f playerCenter; //centro del jugador
        sf::Vector2f mousePos; //posicion del raton
        sf::Vector2f movement; //movimiento del jugador
        //Hitbox del jugador
        sf::RectangleShape hitbox;

        //Activar ataque a distancia
        bool rangeON;

};

#endif // JUGADOR_H
