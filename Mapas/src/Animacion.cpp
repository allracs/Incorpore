
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
    cout << "Cargamos la textura: " << nTextura << endl;

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

void Animacion::update(float deltaTime, Vector2f movement)
{
    totalTime += deltaTime;
    if(totalTime >= switchTime) {
        totalTime -= switchTime;

        if(actualFrame.left == finalF.left){
            actualFrame.left = firstF.left;
            //::cout << "Cambiamos de frame0" << endl;
        } else {
            actualFrame.left += incremento;
            //cout << "Cambiamos de frame" << endl;
        }

        sprite.setTextureRect(actualFrame);
    }

    //sprite.setPosition(playerCenter.x, playerCenter.y);
    sprite.move(movement * deltaTime);


}
