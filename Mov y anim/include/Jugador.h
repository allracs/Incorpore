#ifndef JUGADOR_H
#define JUGADOR_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include "Entidad.h"
#include "Animacion.h"



class Jugador
{
    public:
        // METODOS
        Jugador(sf::Vector2f pos);
        virtual ~Jugador();

        //Mover el jugador
        void update(float delta, sf::RenderWindow &app);
        void moverse();
        void rotacionAtaque(sf::RenderWindow &app);
        void draw(sf::RenderWindow &app);


        // VARIABLES

        Animacion derecha;
        Animacion izquierda;
        Animacion *actual;

    private:
        sf::RectangleShape jugadorHitbox;

        float speed; //Velocidad del jugador
        sf::Vector2f playerCenter; //centro del jugador
        sf::Vector2f mousePos; //posicion del raton
        sf::Vector2f movement; //movimiento del jugador
        //Hitbox del jugador
        sf::RectangleShape hitboxAtaque;

        //Activar ataque a distancia
        bool rangeON;

};

#endif // JUGADOR_H
