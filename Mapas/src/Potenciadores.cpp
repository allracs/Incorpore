#include "../include/Potenciadores.h"

using namespace std;
using namespace sf;

Potenciadores::Potenciadores(Vector2f pos){
    sprite = new Sprite;

    if (!tex.loadFromFile("resources/sprites/cofres.png")){
        cerr << "Error cargando la imagen de textura";
        exit(0);
    }

    sprite->setPosition(pos.x, pos.y);

    sprite->setTexture(tex);
    sprite->setTextureRect(IntRect(16, 1, 16, 16));
    sprite->setOrigin(8, 8);
    cout << "Jaja: " << pos.x/16 << " , " << pos.y/16 << endl;
}

Potenciadores::~Potenciadores(){
    //dtor
}

void Potenciadores::abrirCofre(Jugador& jugador, int tipo){
    sprite->setTextureRect(IntRect(16, 16, 16, 16));
    gestionarHabilidades(jugador, tipo);
}

void Potenciadores::gestionarHabilidades(Jugador& jugador, int tipo){
    switch(tipo){
        case 1:
            //Atk up
            jugador.setAtaque(jugador.getAtaque() + 1);

        break;
        case 2:
            //Dfn down
            jugador.setDefensa(jugador.getDefensa() - 1);
        break;
        case 3:
            //Spd down
            jugador.setVelocidad(jugador.getVelocidad() - 25);

        break;
        case 4:
            //Bubble
            jugador.escudarse();
        break;
    }
    jugador.showStats();
}

Sprite Potenciadores::getCofre(){
    return *sprite;
}

void Potenciadores::draw(RenderWindow& window){
    window.draw(*sprite);
}
