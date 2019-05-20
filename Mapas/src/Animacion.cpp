
#include <iostream>
#include "../include/Animacion.h"
using namespace std;
using namespace sf;

Animacion::Animacion()
{

}

Animacion::~Animacion()
{
    //dtor
}


void Animacion::setAnimacion(char* nTextura, IntRect firstF, IntRect finalF, int incremento, float tiempo)
{
  //  cout << "Cargamos la textura: " << nTextura << endl;

    if(!texture.loadFromFile(nTextura)){
        cout << "ERROR AL CARGAR TEXTURA";
    }
    this->firstF = firstF;
    this->finalF = finalF;
    this->incremento = incremento;
    actualFrame = firstF;
    switchTime = tiempo;
    sprite = Sprite(texture, actualFrame);
    sprite.setOrigin((firstF.width)/2, (firstF.height)/2);

}

void Animacion::update(Vector2f movement, float mTime)
{
    float delta = clock.getElapsedTime().asSeconds();
    if(delta >= switchTime) {
        clock.restart();
        if(actualFrame.left == finalF.left){
            actualFrame.left = firstF.left;
        } else {
            actualFrame.left += incremento;
        }

        sprite.setTextureRect(actualFrame);
    }
    sprite.move(movement* mTime);
}

void Animacion::update()
{
    float delta = clock.getElapsedTime().asSeconds();
    if(delta >= switchTime) {
        clock.restart();
        if(actualFrame.left == finalF.left){
            actualFrame.left = firstF.left;
        } else {
            actualFrame.left += incremento;
        }

        sprite.setTextureRect(actualFrame);
    }
}





