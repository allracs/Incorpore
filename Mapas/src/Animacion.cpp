
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


// ANIMACION
/*
#include "Animation.h"

Animation::Animation(sf::Texture spritesheet, float nx, float ny, float nw, float nh, int nmaxx)
{
    //ctor
    sprite = new sf::Sprite(spritesheet);
    x = nx;
    y = ny;
    w = nw;
    h = nh;
    nmax = nmaxx;
    sprite->setTextureRect(sf::IntRect(x, y, w, h));
}

Animation::~Animation()
{
    //dtor
    delete sprite;
}

void Animation::update()
{
    if(clock.getElapsedTime().asSeconds() >= 0.3)
    {
        clock.restart();
        if(pos++ < nmax)
        {
            sprite->setTextureRect(sf::IntRect(x*pos, y, w, h));
            sprite->setOrigin(w/2, h/2);
        }
        else if(pos == nmax)
        {
            pos = 0;
        }
    }
}

void Animation::draw(sf::RenderWindow& w)
{
    w.draw(*sprite);
}

void Animation::die()
{

}

*/



