#include "../include/Arma.h"
using namespace std;
using namespace sf;

Arma::Arma(int opcion, int mejora, Vector2f pos)
{
    tipo = opcion;

    ataqueHitbox.setOutlineThickness(1);
    ataqueHitbox.setOutlineColor(Color::Transparent);
    ataqueHitbox.setFillColor(Color::Transparent);
    ataqueHitbox.setSize(Vector2f(11.f, 4.f));
    ataqueHitbox.setOrigin(-8,2.f);
    ataqueHitbox.setPosition(pos.x + 2, pos.y + 3);

    // Cargar el sprite de la hitbox de ataque.
    if(!texturaMelee.loadFromFile("resources/sprites/melee0.png"))
        cout << "ERROR AL CARGAR LA TEXTURA: basic.png" << endl;
    if(!texturaRange.loadFromFile("resources/sprites/range0.png"))
        cout << "ERROR AL CARGAR LA TEXTURA: basic.png" << endl;
    if(!texturaAtaque.loadFromFile("resources/sprites/ataque.png"))
        cout << "ERROR AL CARGAR LA TEXTURA: atque.png" << endl;

    if(mejora != 0)
        mejorarArma(mejora);

    if(tipo == 0) {
        texturaActual = texturaMelee;
    } else if(tipo == 1) {
        texturaActual = texturaRange;
    }

    espada.setTexture(texturaActual);
    espada.setOrigin(14,14);
    espada.setPosition(pos.x +2, pos.y +3);
    espada.setScale(-1.f, -1.f);

    cambiado = false;
}

Arma::~Arma()
{
    //dtor
}

void Arma::update(Vector2f vDir, int nCol, FloatRect* colisiones){
    espada.move(vDir);
    for(int i = 0; i < proyectiles.size(); i++) {
        if(proyectiles.at(i)->getHacolsionado() == true) {
            delete proyectiles.at(i);
            proyectiles.erase(proyectiles.begin()+i);
        } else {
            proyectiles.at(i)->update(nCol, colisiones);
        }
    }

    terminAnim();
}


void Arma::empezarAnim(){
    // reinicio el reloj
    // cambio el sprite
//    std::cout << "SE LLAMA AL MÉTODO EMPEZAR ANIM" << std::endl;
    animAtaque.restart();
    espada.setTexture(texturaAtaque);
    cambiado = true;
}

void Arma::terminAnim() {
    if(animAtaque.getElapsedTime().asSeconds() >= 0.2f && cambiado){
        animAtaque.restart();
        espada.setTexture(texturaActual);
        cambiado = false;
    }
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

void Arma::atacar(std::vector<Enemigo*> enemigos, int nEnemigos, float atkJugador){
    if(tipo==0){
        for(int i = 0; i < nEnemigos; i++){
            enemigos.at(i)->serAtacado(ataqueHitbox, atkJugador);
        }

    }
}

void Arma::crearProyectil(sf::Vector2f entityCenter) {
    if(tipo==1){

        if(CDdisparo.getElapsedTime().asSeconds()>=1.f){
            CDdisparo.restart();
            sf::Vector2f aimDir = mousePos - entityCenter;
            sf::Vector2f aimDirNorm = aimDir/(float)sqrt(pow(aimDir.x,2)+pow(aimDir.y,2));
            sf::Vector2f pos(aimDirNorm.x*15, aimDirNorm.y*15);

            // ROTACION SPRITE:
            float dx = mousePos.x - entityCenter.x; // distancia x
            float dy = mousePos.y - entityCenter.y; // distancia y
            float PI = 3.14159265;

            float rotation=(atan2(dx,dy))*180/PI;

            Proyectil *pr = new Proyectil(ataqueHitbox.getPosition() + pos, aimDirNorm, rotation);
            proyectiles.push_back(pr);
        }
    }
}


int Arma::getOpcion(){
    return tipo;
}


void Arma::cambiarArma(int opcion) {
    if(opcion == 0) {
        texturaActual = texturaMelee;
        tipo = opcion;
    }
    if(opcion == 1) {
        texturaActual = texturaRange;
        tipo = opcion;
    }
}

void Arma::mejorarArma(int mejora) {
    if(mejora == 1) {
        texturaMelee.loadFromFile("resources/sprites/melee1.png");
        texturaRange.loadFromFile("resources/sprites/range1.png");
    } else if(mejora == 2) {
        texturaMelee.loadFromFile("resources/sprites/melee2.png");
        texturaRange.loadFromFile("resources/sprites/range2.png");
    } else if(mejora >= 3) {
        texturaMelee.loadFromFile("resources/sprites/melee3.png");
        texturaRange.loadFromFile("resources/sprites/range3.png");
    }

    if(tipo == 0) {
        texturaActual = texturaMelee;
    } else if(tipo == 1) {
        texturaActual = texturaRange;
    }
}


RectangleShape Arma::getHitbox(){
    return ataqueHitbox;
}

Sprite Arma::getEspada(){
    return espada;
}

std::vector<Proyectil*> Arma::getProyectiles() {
    return proyectiles;
}

Vector2f Arma::getMousePos(){
    return mousePos;
}

float Arma::getDireccionMov(){
    return dMov;
}

