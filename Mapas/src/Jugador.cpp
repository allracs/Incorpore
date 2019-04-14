#include <iostream>
#include "../include/Jugador.h"
using namespace std;
using namespace sf;

Jugador::Jugador(Vector2f pos){
    entityCenter = pos;
    entidadHitbox.setPosition(pos);
    setColisionadores();

    dirMov = 1.f;
    movement = Vector2f(0.f, 0.f);

<<<<<<< HEAD
=======
    // Animaciones
>>>>>>> mapa-colisiones
    idle.setAnimacion("sprites/caballero.png", IntRect(0, 0, 16, 28), IntRect(48, 0, 16, 28), 16, 0.1f);
    idle.sprite.setOrigin(9,20);
    run.setAnimacion("sprites/caballero.png", IntRect(0, 28, 16, 28), IntRect(48, 28, 16, 28), 16, 0.1f);
    run.sprite.setOrigin(9,20);

    actual = &idle;
    actual->sprite.setPosition(pos);

<<<<<<< HEAD
=======
    // Hitbox de ataque (con la que el jugador ataca)
>>>>>>> mapa-colisiones
    ataqueHitbox.setOutlineThickness(1);
    ataqueHitbox.setOutlineColor(Color::Blue);
    ataqueHitbox.setFillColor(Color::Transparent);
    ataqueHitbox.setSize(Vector2f(20.f, 12.f));
    ataqueHitbox.setOrigin(0,6.f);
    ataqueHitbox.setPosition(pos);
<<<<<<< HEAD
}

void Jugador::update(float delta, RenderWindow& window, int nCol, FloatRect* colisiones){
    entityCenter = Vector2f(entidadHitbox.getPosition().x, entidadHitbox.getPosition().y);
    rotacionAtaque(window);
=======

    // Cargar el sprite de la hitbox de ataque.
    if(!swordText.loadFromFile("resources/sprites/sword.png"))
        std::cout << "ERROR AL CARGAR LA TEXTURA: sword.png" << std::endl;
    espada.setTexture(swordText);
    espada.setOrigin(14,14);
    espada.setPosition(ataqueHitbox.getPosition().x +2, ataqueHitbox.getPosition().y +3);
    espada.setScale(-1.f, -1.f);


}

void Jugador::update(float delta, RenderWindow& window, int nCol, FloatRect* colisiones){

    entityCenter = Vector2f(entidadHitbox.getPosition().x, entidadHitbox.getPosition().y);
    rotacionAtaque(window);
    actual->sprite.setScale(1.f*dirMov, 1.f);

>>>>>>> mapa-colisiones

    // MOVIMIENTO
    moverse(); // comprobar que el jugador se mueve
    entidadHitbox.move(movement * delta); // mover al jugador.
<<<<<<< HEAD
    ataqueHitbox.move(movement * delta);
=======
    ataqueHitbox.move(movement * delta);// mover la hitbox con la que el jugador ataca
    espada.move(movement * delta); // para que la espada se mueva junto con el jugador.

>>>>>>> mapa-colisiones
    moverColisionadores(movement * delta);
    procesarColisiones(nCol, colisiones);

    actual->update(delta, movement);
}

void Jugador::moverse(){
    movement = Vector2f(0.f, 0.f);

    if (Keyboard::isKeyPressed(Keyboard::W) && colisiona_abajo != true){
        movement.y -= speed;
        if (actual != &run){
<<<<<<< HEAD
            cout << "CAMBIAMOS A RUN" << endl;
=======
            //cout << "CAMBIAMOS A RUN" << endl;
>>>>>>> mapa-colisiones
            actual = &run;
            actual->sprite.setPosition(entityCenter);
        }
    }

    if (Keyboard::isKeyPressed(Keyboard::S) && colisiona_arriba != true){
        movement.y += speed;

        if (actual != &run){
<<<<<<< HEAD
            cout << "CAMBIAMOS A RUN" << endl;
=======
            //cout << "CAMBIAMOS A RUN" << endl;
>>>>>>> mapa-colisiones
            actual = &run;
            actual->sprite.setPosition(entityCenter);
        }
    }

    if(Keyboard::isKeyPressed(Keyboard::A) && colisiona_derecha != true){
<<<<<<< HEAD
        dirMov = -1.f;
        movement.x -= speed;

        if (actual != &run){
            cout << "CAMBIAMOS A RUN" << endl;
            actual = &run;
            actual->sprite.setPosition(entityCenter);
        }
        actual->sprite.setScale(1.f*dirMov, 1.f);
    }

    if (Keyboard::isKeyPressed(Keyboard::D) && colisiona_izquierda != true){
        dirMov = 1.f;
        movement.x += speed;

        if (actual != &run){
            cout << "CAMBIAMOS A RUN" << endl;
            actual = &run;
            actual->sprite.setPosition(entityCenter);
        }
        actual->sprite.setScale(1.f*dirMov, 1.f);
=======
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
>>>>>>> mapa-colisiones
    }

    if(movement.x == 0 & movement.y == 0) {
        if (actual != &idle){
<<<<<<< HEAD
            cout << "CAMBIAMOS A IDLE" << endl;
            actual = &idle;
            actual->sprite.setPosition(entityCenter);
            actual->sprite.setScale(1.f*dirMov, 1.f);
=======
            //cout << "CAMBIAMOS A IDLE" << endl;
            actual = &idle;
            actual->sprite.setPosition(entityCenter);
>>>>>>> mapa-colisiones
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

<<<<<<< HEAD
    float dx = mousePos.x - entityCenter.x;
    float dy = mousePos.y - entityCenter.y;
=======
    float dx = mousePos.x - entityCenter.x; // distancia x
    float dy = mousePos.y - entityCenter.y; // distancia y
>>>>>>> mapa-colisiones


    float rotation = (atan2(dy, dx)) * 180 / PI;
    ataqueHitbox.setRotation(rotation);
<<<<<<< HEAD
=======
    espada.setRotation(rotation - 45.f); // hacer que la espada rote alrededor del jugador y se le añade 45 para que esté bien posicionada.
    if(ataqueHitbox.getRotation() >= 90 && ataqueHitbox.getRotation() <= 270) {
        dirMov = -1;
        espada.setPosition(ataqueHitbox.getPosition().x -2, ataqueHitbox.getPosition().y +3);

    } else {
        dirMov = 1;
        espada.setPosition(ataqueHitbox.getPosition().x +2, ataqueHitbox.getPosition().y +3);
    }

>>>>>>> mapa-colisiones
}

Vector2f Jugador::getMousePos(){
    return mousePos;
}

Vector2f Jugador::getMovement() {
<<<<<<< HEAD
    return movement;
}
=======

    return movement;
}


void Jugador::draw(sf::RenderWindow &app) {

    if(ataqueHitbox.getRotation() >= 0 && ataqueHitbox.getRotation() <= 180) {
        app.draw(actual->sprite);
        app.draw(espada);
    } else {
        app.draw(espada);
        app.draw(actual->sprite);
    }
    app.draw(espada);
    app.draw(ataqueHitbox);

}









>>>>>>> mapa-colisiones
