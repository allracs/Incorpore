#ifndef ENTITY_H
#define ENTITY_H

#include"SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include"SFML/System.hpp"
#include"SFML/Network.hpp"


#include<iostream>
#include<ctime>
#include<cstdlib>

#include<stack>
#include<vector>
#include<map>


class Entity
{
        private:

     protected:
            sf::RectangleShape shape;
            float movementSpeed;

    public:
        Entity();
       virtual ~Entity();

       //Funciones
      virtual void update(const float& dt);
      virtual void render(sf::RenderTarget* target);

      virtual void move(const float& dt,const float x, const float y);


    };
    #endif

