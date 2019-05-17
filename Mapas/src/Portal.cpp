#include "Portal.h"

Portal::Portal(int tipo, sf::Vector2i){
    sprite = new sf::Sprite;

    ancho = 200;
    alto = 320;
    sep_ancho = 60;
    sep_alto = 0;
    switch(tipo){
        case 1:
            if (!tex.loadFromFile("resources/sprites/portal.png")){
                std::cerr << "Error cargando la imagen de textura";
                exit(0);
            }
        break;
        case 2:
        break;
        default:
        break;
    }

    sf::IntRect temp_dim(sep_ancho,sep_alto,ancho,alto);
    dim = temp_dim;

    sprite->setTexture(tex);
    sprite->setTextureRect(dim);
    sprite->setOrigin(ancho/2, alto/2);
    sprite->scale(0.1,0.1);
    sprite->setPosition(10*16, 24);
}

Portal::~Portal()
{
    delete sprite;
}

void Portal::update(){
    animacion();
}

void Portal::animacion(){
       if(clockAnimacion.getElapsedTime().asSeconds() > 0.05f){
            if(dim.top == 0){
                if(dim.left < 1340){
                    dim.left +=320;
                }
                else{
                    dim.top += 320;
                    dim.left = 60;
                }
            }
            else{
                if(dim.left < 1020){
                    dim.left +=320;
                }
                else{
                    dim.top = 0;
                    dim.left = 60;
                }
            }

            sprite->setTextureRect(dim);
            clockAnimacion.restart();
       }
}

void Portal::draw(sf::RenderWindow &window){
    window.draw(*sprite);
}


sf::Sprite Portal::getPortal(){
    return *sprite;
}
