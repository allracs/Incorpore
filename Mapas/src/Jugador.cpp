#include <iostream>
#include "../include/Jugador.h"
using namespace std;
using namespace sf;

Jugador::Jugador(Vector2f pos){
    playerCenter = pos;
    //sprite->setOrigin(sprite->getSize().x/2, sprite->getSize().y/2);

    //jugadorHitbox = RectangleShape(Vector2f(sprite->getSize().x - 4, sprite->getSize().y - 4));
    jugadorHitbox = sf::RectangleShape(sf::Vector2f(12,12));
    jugadorHitbox.setPosition(pos);
    jugadorHitbox.setOrigin(12/2, 12/2);
    jugadorHitbox.setFillColor(Color::Transparent);
    jugadorHitbox.setOutlineThickness(1.f);
    jugadorHitbox.setOutlineColor(Color::Green);
    setColisionadores();

    speed = 75.f;
    dirMov = 1.f;
    movement = Vector2f(0.f, 0.f);

    idle.setAnimacion("sprites/caballero.png", IntRect(0,0,16,28), IntRect(48,0,16,28), 16, 0.1f);
    idle.sprite.setOrigin(9,20);
    run.setAnimacion("sprites/caballero.png", IntRect(0, 28, 16, 28), IntRect(48, 28, 16, 28), 16, 0.1f);
    run.sprite.setOrigin(9,20);

    actual = &idle;
    actual->sprite.setPosition(pos);

    ataqueHitbox.setOutlineThickness(1);
    ataqueHitbox.setOutlineColor(Color::Blue);
    ataqueHitbox.setFillColor(Color::Transparent);
    ataqueHitbox.setSize(Vector2f(20.f, 12.f));
    ataqueHitbox.setOrigin(0,6.f);
    ataqueHitbox.setPosition(pos);
}

void Jugador::setColisionadores(){
    cuadrado_arr->setSize(Vector2f(11, 0.75));
    cuadrado_arr->setPosition(jugadorHitbox.getGlobalBounds().left + 1.5, jugadorHitbox.getGlobalBounds().top + jugadorHitbox.getGlobalBounds().height/2 - 0.5);
    cuadrado_izq->setSize(Vector2f(0.75, 5.5));
    cuadrado_izq->setPosition(jugadorHitbox.getGlobalBounds().left, jugadorHitbox.getGlobalBounds().top + jugadorHitbox.getGlobalBounds().height/2 + 0.99);
    cuadrado_abj->setSize(Vector2f(11, 0.75));
    cuadrado_abj->setPosition(jugadorHitbox.getGlobalBounds().left + 1.5, jugadorHitbox.getGlobalBounds().top + jugadorHitbox.getGlobalBounds().height + 0.5);
    cuadrado_der->setSize(Vector2f(0.75, 5.5));
    cuadrado_der->setPosition(jugadorHitbox.getGlobalBounds().left + jugadorHitbox.getGlobalBounds().width - 0.5, jugadorHitbox.getGlobalBounds().top + jugadorHitbox.getGlobalBounds().height/2 + 0.99);
}

void Jugador::moverColisionadores(Vector2f mov){
    cuadrado_arr->move(mov);
    cuadrado_izq->move(mov);
    cuadrado_abj->move(mov);
    cuadrado_der->move(mov);
}

void Jugador::procesarColisiones(int nColisiones, FloatRect* colisiones){
   for(int i = 0; i < nColisiones; i++){
        //INFERIOR
        if(cuadrado_arr->getGlobalBounds().intersects(colisiones[i])){
            setColision(2);
            cout <<  "Arriba" << endl;
        }

        //SUPERIOR
        if(cuadrado_abj->getGlobalBounds().intersects(colisiones[i])){
            setColision(1);
            cout <<  "Abajo" << endl;
        }

        //IZQUIERDA
        if(cuadrado_der->getGlobalBounds().intersects(colisiones[i])){
            setColision(3);
            cout <<  "Der" << endl;
        }

        //DERECHA
        if(cuadrado_izq->getGlobalBounds().intersects(colisiones[i])){
            setColision(4);
            cout <<  "Izq" << endl;
        }
    }
}

void Jugador::update(float delta, RenderWindow& window, int nCol, FloatRect* colisiones){
    playerCenter = Vector2f(jugadorHitbox.getPosition().x, jugadorHitbox.getPosition().y);
    rotacionAtaque(window);

    // MOVIMIENTO
    moverse(); // comprobar que el jugador se mueve
    jugadorHitbox.move(movement * delta); // mover al jugador.
    ataqueHitbox.move(movement * delta);
    moverColisionadores(movement * delta);
    procesarColisiones(nCol, colisiones);

    //cout << "Delta: " << delta << endl;
    actual->update(delta, movement);
}

void Jugador::moverse(){
    movement = Vector2f(0.f, 0.f);

    if (Keyboard::isKeyPressed(Keyboard::W) && colisiona_abajo != true){
        movement.y -= speed;
        if (actual != &run){
            cout << "CAMBIAMOS A RUN" << endl;
            actual = &run;
            actual->sprite.setPosition(playerCenter);
        }
    }

    if (Keyboard::isKeyPressed(Keyboard::S) && colisiona_arriba != true){
        movement.y += speed;

        if (actual != &run){
            cout << "CAMBIAMOS A RUN" << endl;
            actual = &run;
            actual->sprite.setPosition(playerCenter);
        }
    }

    if(Keyboard::isKeyPressed(Keyboard::A) && colisiona_derecha != true){
        dirMov = -1.f;
        movement.x -= speed;

        if (actual != &run){
            cout << "CAMBIAMOS A RUN" << endl;
            actual = &run;
            actual->sprite.setPosition(playerCenter);
        }
        actual->sprite.setScale(1.f*dirMov, 1.f);
    }

    if (Keyboard::isKeyPressed(Keyboard::D) && colisiona_izquierda != true){
        dirMov = 1.f;
        movement.x += speed;

        if (actual != &run){
            cout << "CAMBIAMOS A RUN" << endl;
            actual = &run;
            actual->sprite.setPosition(playerCenter);
        }
        actual->sprite.setScale(1.f*dirMov, 1.f);
    }

    if(movement.x == 0 & movement.y == 0) {
        if (actual != &idle){
            cout << "CAMBIAMOS A IDLE" << endl;
            actual = &idle;
            actual->sprite.setPosition(playerCenter);
            actual->sprite.setScale(1.f*dirMov, 1.f);
        }
    }

    colisiona_abajo = false;
    colisiona_arriba = false;
    colisiona_derecha = false;
    colisiona_izquierda = false;
}

void Jugador::rotacionAtaque(RenderWindow& window) {
    Vector2i pixelPos = Vector2i(Mouse::getPosition(window));

    mousePos = window.mapPixelToCoords(pixelPos);

    float PI = 3.14159265;

    float dx = mousePos.x - playerCenter.x;
    float dy = mousePos.y - playerCenter.y;


    float rotation = (atan2(dy, dx)) * 180 / PI;
    ataqueHitbox.setRotation(rotation);
}

RectangleShape Jugador::getJugadorHitbox(){
    return jugadorHitbox;
}

RectangleShape Jugador::getAtaqueHitbox(){
    return ataqueHitbox;
}

Vector2f Jugador::getCenter(){
    //cout << "PLAYER CENTER: " << playerCenter.x << " - " << playerCenter.y << endl;
    return playerCenter;
}

Vector2f Jugador::getMousePos(){
    return mousePos;
}

Vector2f Jugador::getMovement() {
    return movement;
}

Animacion* Jugador::getActual() {
    return actual;
}

void Jugador::draw(RenderWindow& target) {
    //target.draw(jugadorHitbox);
    target.draw(actual->sprite);
    //target.draw(ataqueHitbox);
}

void Jugador::drawBoundingBoxes(RenderWindow& target){
    target.draw(*cuadrado_der);
    target.draw(*cuadrado_arr);
    target.draw(*cuadrado_abj);
    target.draw(*cuadrado_izq);
    //target.draw(*cuadrado_cen);
}

void Jugador::showData(){/*
    cout <<  "x: " << sprite->getPosition().x << endl;
    cout <<  "y: " << sprite->getPosition().y << endl;
    cout <<  "width: " << sprite->getSize().x << endl;
    cout <<  "height: " << sprite->getSize().x << endl;*/
}
