#include "Animacion.h"
#include <iostream>

Animacion::Animacion()
{

}

Animacion::~Animacion()
{
    //dtor
}


void Animacion::setAnimacion(char* nTextura, sf::IntRect firstF, sf::IntRect finalF, int incremento, float tiempo)
{
    std::cout << "cargamos la textura: " << nTextura << std::endl;

    if(!texture.loadFromFile(nTextura)){
        std::cout << "ERROR AL CARGAR TEXTURA";
    }
    sprite = sf::Sprite(texture, actualFrame);
    firstF = firstF;
    finalF = finalF;
    incremento = incremento;
    actualFrame = firstF;
    switchTime = tiempo;
}

void Animacion::update(float deltaTime)
{
    totalTime += deltaTime;
    if(totalTime >= switchTime) {
        totalTime -= switchTime;

        if(actualFrame.left == 48){
            actualFrame.left = 0;
        } else {
            actualFrame.left += 16;
        }

        sprite.setTextureRect(actualFrame);
    }

    /*
    if(clock.getElapsedTime().asSeconds() >= 1.f) {
        if(actualFrame.left == 48){
            actualFrame.left = 0;
        } else {
            actualFrame.left += 16;
        }

        sprite.setTextureRect(actualFrame);
        clock.restart();
    }
    */
}



