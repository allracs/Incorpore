#ifndef JUGADOR_H
#define JUGADOR_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#include "Entidad.h"
#include "Animacion.h"



class Jugador
{
    public:
        // METODOS PUBLICOS
        Jugador(sf::Vector2f pos);
        virtual ~Jugador();

        void update(float delta, sf::RenderWindow &app);
        void moverse();
        void rotacionAtaque(sf::RenderWindow &app);
        void draw(sf::RenderWindow &app);



        //Getters
        sf::Vector2f getCenter();
        sf::Vector2f getMousePos();
        sf::Vector2f getMovement();
        sf::RectangleShape getHitboxAtaque();

        // VARIABLES PUBLICAS

        float dirMov;



    private:
        //VARIBALES PRIVADAS
        sf::RectangleShape jugadorHitbox;
        sf::Vector2f playerCenter; //centro del jugador
        float speed; //Velocidad del jugador
        sf::Vector2f mousePos; //posicion del raton
        sf::Vector2f movement; //movimiento del jugador

        //Ataque del jugador
        sf::RectangleShape hitboxAtaque;


        //Activar ataque a distancia
        bool rangeON;

        Animacion idle;
        Animacion run;
        Animacion *actual;

};

#endif // JUGADOR_H
