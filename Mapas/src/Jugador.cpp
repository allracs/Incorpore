#include <iostream>
#include "../include/Jugador.h"
using namespace std;
using namespace sf;

Jugador::Jugador(Vector2f pos){
    entityCenter = pos;
    entidadHitbox.setPosition(pos);
    setColisionadores();
    vidas = 10;
    dirMov = 1.f;
    movement = Vector2f(0.f, 0.f);

    // Animaciones
    idle.setAnimacion("resources/sprites/personajes.png", IntRect(0, 28, 16, 28), IntRect(48, 28, 16, 28), 16, 0.1f);
    idle.sprite.setOrigin(9,20);
    run.setAnimacion("resources/sprites/personajes.png", IntRect(64, 28, 16, 28), IntRect(112, 28, 16, 28), 16, 0.1f);
    run.sprite.setOrigin(9,20);

    actual = &idle;
    actual->sprite.setPosition(pos);

    arma = new Arma(0, pos);
}

void Jugador::update(float delta, RenderWindow& window, int nCol, FloatRect* colisiones){
    entityCenter = Vector2f(entidadHitbox.getPosition().x, entidadHitbox.getPosition().y);
    actual->sprite.setScale(1.f*(arma->getDireccionMov()), 1.f);


    // MOVIMIENTO
    moverse(); // comprobar que el jugador se mueve
    //atacar();
    entidadHitbox.move(movement * delta); // mover al jugador.
    ataqueHitbox.move(movement * delta);// mover la hitbox con la que el jugador ataca
    arma->update(movement * delta); // para que la espada se mueva junto con el jugador.
    arma->rotacionAtaque(window, dirMov, entityCenter, entidadHitbox);
    ataqueHitbox = arma->getHitbox();
    moverColisionadores(movement * delta);
    procesarColisiones(nCol, colisiones);

    actual->update(delta, movement);
}

bool Jugador::recibeDmg(RectangleShape enemigoHitbox, int vida){
    Vector2f enemyPos = enemigoHitbox.getPosition();
    bool res = false;
    if(getEntidadHitbox().getGlobalBounds().intersects(enemigoHitbox.getGlobalBounds()) && dmgCD.getElapsedTime().asSeconds() >= 1.5 && vida > 0){
        res = true;
        vidas--;
        if(vidas > 0){/*
            //colisiona por la derecha
            if(playerCenter.x > enemyPos.x){
                actual->sprite.move(8,0);
                entidadHitbox.move(8,0);
                moverColisionadores({8,0});
            }
            //colisiona por la izquierda
            if(playerCenter.x < enemyPos.x){
                 actual->sprite.move(-8,0);
                 entidadHitbox.move(-8,0);
                 moverColisionadores({-8,0});
            }
            //colisiona por arriba
            if(playerCenter.y < enemyPos.y){
                actual->sprite.move(0,-8);
                entidadHitbox.move(0,-8);
                moverColisionadores({0,-8});
            }
            //colisiona por debajo
            if(playerCenter.y > enemyPos.y){
                actual->sprite.move(0,8);
                entidadHitbox.move(0,8);
                moverColisionadores({0,8});
            }*/
        }
        else{
            //Muerto
            cout << "HAS PALMAO, FIN DE LA PARTIDA." << endl; //Cambiar por retorno a menu
            exit(0);
        }

        dmgCD.restart();
    }
}

void Jugador::moverse(){
    movement = Vector2f(0.f, 0.f);

    if (Keyboard::isKeyPressed(Keyboard::W) && colisiona_abajo != true){
        movement.y -= speed;
        if (actual != &run){
            //cout << "CAMBIAMOS A RUN" << endl;
            actual = &run;
            actual->sprite.setPosition(entityCenter);
        }
    }

    if (Keyboard::isKeyPressed(Keyboard::S) && colisiona_arriba != true){
        movement.y += speed;

        if (actual != &run){
            //cout << "CAMBIAMOS A RUN" << endl;
            actual = &run;
            actual->sprite.setPosition(entityCenter);
        }
    }

    if(Keyboard::isKeyPressed(Keyboard::A) && colisiona_derecha != true){
        movement.x -= speed;

        if (actual != &run){
            //cout << "CAMBIAMOS A RUN" << endl;
            actual = &run;
            actual->sprite.setPosition(entityCenter);
        }
    }

    if (Keyboard::isKeyPressed(Keyboard::D) && colisiona_izquierda != true){
        movement.x += speed;

        if (actual != &run){
            //cout << "CAMBIAMOS A RUN" << endl;
            actual = &run;
            actual->sprite.setPosition(entityCenter);
        }
    }

    if(movement.x == 0 & movement.y == 0) {
        if (actual != &idle){
            //cout << "CAMBIAMOS A IDLE" << endl;
            actual = &idle;
            actual->sprite.setPosition(entityCenter);
        }
    }

    colisiona_abajo = false;
    colisiona_arriba = false;
    colisiona_derecha = false;
    colisiona_izquierda = false;
}

Vector2f Jugador::getMovement() {
    return movement;
}

Arma Jugador::getArma() {
    return *arma;
}

void Jugador::draw(sf::RenderWindow &app) {

    if(ataqueHitbox.getRotation() >= 0 && ataqueHitbox.getRotation() <= 180) {
        app.draw(actual->sprite);
        app.draw(arma->getEspada());
    } else {
        app.draw(arma->getEspada());
        app.draw(actual->sprite);
    }
    app.draw(ataqueHitbox);

}

int Jugador::getVidas(){
    return vidas;
}










