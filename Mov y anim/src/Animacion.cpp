
#include <iostream>
#include "Animacion.h"

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
    this->firstF = firstF;
    this->finalF = finalF;
    this->incremento = incremento;
    actualFrame = firstF;
    switchTime = tiempo;
    sprite = sf::Sprite(texture, actualFrame);

}

void Animacion::update(float deltaTime, sf::Vector2f playerCenter)
{
    totalTime += deltaTime;
    if(totalTime >= switchTime) {
        totalTime -= switchTime;

        if(actualFrame.left == finalF.left){
            actualFrame.left = firstF.left;
        } else {
            actualFrame.left += incremento;
        }

        sprite.setTextureRect(actualFrame);
    }

    std::cout << playerCenter.x << playerCenter.y << std::endl;
    sprite.setPosition(playerCenter);

}