#include "../include/Arma.h"
using namespace std;
using namespace sf;

Arma::Arma(int opcion, Vector2f pos)
{
    // 0: Melee 1: Distancia "a implementar ataque a distancia fisico y magico"
    if(opcion == 0){
        ataqueHitbox.setOutlineThickness(1);
        ataqueHitbox.setOutlineColor(Color::Blue);
        ataqueHitbox.setFillColor(Color::Transparent);
        ataqueHitbox.setSize(Vector2f(11.f, 4.f));
        ataqueHitbox.setOrigin(-8,2.f);
        ataqueHitbox.setPosition(pos.x + 2, pos.y + 3);

        // Cargar el sprite de la hitbox de ataque.
        if(!textura.loadFromFile("resources/sprites/sword.png"))
            cout << "ERROR AL CARGAR LA TEXTURA: sword.png" << endl;
        espada.setTexture(textura);
        espada.setOrigin(14,14);
        espada.setPosition(pos.x +2, pos.y +3);
        espada.setScale(-1.f, -1.f);
    } else if(opcion == 1){

    }
}

Arma::~Arma()
{
    //dtor
}

void Arma::update(Vector2f vDir){
    espada.move(vDir);
}


void Arma::rotacionAtaque(RenderWindow& window, float dirMov, Vector2f entityCenter, RectangleShape entidadHitbox) {
    Vector2i pixelPos = Vector2i(Mouse::getPosition(window));

    mousePos = window.mapPixelToCoords(pixelPos);

    float PI = 3.14159265;

    float dx = mousePos.x - entityCenter.x; // distancia x
    float dy = mousePos.y - entityCenter.y; // distancia y


    float rotation = (atan2(dy, dx)) * 180 / PI;
    ataqueHitbox.setRotation(rotation);
    espada.setRotation(rotation - 45.f); // hacer que la espada rote alrededor del jugador y se le añade 45 para que esté bien posicionada.
    if(ataqueHitbox.getRotation() >= 90 && ataqueHitbox.getRotation() <= 270) {
        dirMov = -1;
        espada.setPosition(entidadHitbox.getPosition().x -2, entidadHitbox.getPosition().y +3);
        ataqueHitbox.setPosition(entidadHitbox.getPosition().x -2, entidadHitbox.getPosition().y +3);

    } else {
        dirMov = 1;
        espada.setPosition(entidadHitbox.getPosition().x +2, entidadHitbox.getPosition().y +3);
        ataqueHitbox.setPosition(entidadHitbox.getPosition().x +2, entidadHitbox.getPosition().y +3);
    }
    dMov = dirMov;
}

void Arma::atacar(int opcion, std::vector<Enemigo*> enemigos, int nEnemigos){
    for(int i = 0; i < nEnemigos; i++){
        enemigos.at(i)->serAtacado(ataqueHitbox);
    }
}

RectangleShape Arma::getHitbox(){
    return ataqueHitbox;
}

Sprite Arma::getEspada(){
    return espada;
}

Vector2f Arma::getMousePos(){
    return mousePos;
}

float Arma::getDireccionMov(){
    return dMov;
}
