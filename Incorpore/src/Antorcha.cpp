#include "../include/Antorcha.h"

using namespace std;
using namespace sf;

Antorcha::Antorcha(Vector2f pos){
    sprite = new Sprite;
    spriteFire = new Sprite;

    if (!tex.loadFromFile("resources/sprites/antorcha.png")){
        cerr << "Error cargando la imagen de textura";
        exit(0);
    }
    sprite->setPosition(pos.x, pos.y);

    IntRect temp_dim(16, 16, 16, 16);
    dim = temp_dim;

    sprite->setTexture(tex);
    sprite->setTextureRect(dim);
    //sprite->setOrigin(0, 16);

    spriteFire->setPosition(pos.x, pos.y-16);

    IntRect temp_dimFire(16, 0, 16, 16);
    dimFire = temp_dimFire;

    spriteFire->setTexture(tex);
    spriteFire->setTextureRect(dimFire);
    //spriteFire->setOrigin(0, 16);
}

Antorcha::~Antorcha(){
    delete sprite;
}

void Antorcha::update(){
    animacion();
}

void Antorcha::animacion(){
       if(clockAnimacion.getElapsedTime().asSeconds() > 0.15f){

            if(dim.left < 128){
                dim.left += 16;
                dimFire.left += 16;
            }
            else{
                dim.left = 16;
                dimFire.left = 16;
            }


            sprite->setTextureRect(dim);
            spriteFire->setTextureRect(dimFire);
            clockAnimacion.restart();
       }
}

void Antorcha::draw(RenderWindow &window){
    window.draw(*sprite);
}

void Antorcha::drawFire(RenderWindow &window){
    window.draw(*spriteFire);
}


Sprite Antorcha::getAntorcha(){
    return *sprite;
}
