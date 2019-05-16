#include "../include/Enemigo.h"
#include "Proyectil.h"

Enemigo::Enemigo(Vector2f pos){
    entityCenter = pos;
    entidadHitbox.setPosition(pos);
    setColisionadores();

    dirMov = 1.f;
    movement = Vector2f(0.f, 0.f);

    /*idle.setAnimacion("resources/sprites/elfa.png", IntRect(0, 0, 16, 28), IntRect(48, 0, 16, 28), 16, 0.1f);
    idle.sprite.setOrigin(9,20);
    run.setAnimacion("resources/sprites/elfa.png", IntRect(0, 28, 16, 28), IntRect(48, 28, 16, 28), 16, 0.1f);
    run.sprite.setOrigin(9,20);*/

    idle.setAnimacion("resources/sprites/enemigos.png", IntRect(0, 0, 16, 28), IntRect(48, 0, 16, 28), 16, 0.1f);
    idle.sprite.setOrigin(9,20);
    run.setAnimacion("resources/sprites/enemigos.png", IntRect(64, 0, 16, 28), IntRect(112, 0, 16, 28), 16, 0.1f);
    run.sprite.setOrigin(9,20);

    actual = &idle;
    actual->sprite.setPosition(pos);

    ataqueHitbox.setOutlineThickness(1);
    ataqueHitbox.setOutlineColor(Color::Blue);
    ataqueHitbox.setFillColor(Color::Transparent);
    ataqueHitbox.setSize(Vector2f(20.f, 12.f));
    ataqueHitbox.setOrigin(0,6.f);
    ataqueHitbox.setPosition(pos);

    speed = 30.f;
    deleteSprite = false;
    vida = 3;
}

void Enemigo::setPath(std::vector<Posicion> p){
    path = p;
}

void Enemigo::update(float delta, RenderWindow& window, int nCol, FloatRect* colisiones, Posicion pos_a,
                     sf::RectangleShape enemigoHitbox, std::vector<Proyectil*> proyectiles, bool* esquinas){

    entityCenter = Vector2f(entidadHitbox.getPosition().x, entidadHitbox.getPosition().y);

    // MOVIMIENTO con interpolacion
    if(cInterp.getElapsedTime().asMilliseconds() >= 1000/15)
    {
        seguirCamino(pos_a, esquinas); // comprobar que el jugador se mueve
        cInterp.restart();
    }
    entidadHitbox.move(movement * delta); // mover al jugador.
    ataqueHitbox.move(movement * delta);
    moverColisionadores(movement * delta);
    procesarColisiones(nCol, colisiones);
    actual->update(delta, movement);
    compruebaColor();


    for(int i= 0; i< proyectiles.size(); i++) {
        if(serAtacado(proyectiles.at(i)->getColision())) {
            proyectiles.at(i)->setHacolisionado(true);
        }
    }


}

void Enemigo::seguirCamino(Posicion a, bool* esquinas){

    //aqui el enemigo sigue el camino
    movement = Vector2f(0.f, 0.f);

    Posicion head = path.front();
    sf::Vector2f coordhead = {head.getX()*16+8, head.getY()*16+8};
    sf::Vector2f coordnow = getCenter();

    if (a.getY() > head.getY() && !colisiona_abajo){    // ABAJO
        movement.y -= speed;
        if (actual != &run){
            //cout << "CAMBIAMOS A RUN" << endl;
            actual = &run;
            actual->sprite.setPosition(entityCenter);
        }
    }

    if (a.getY() < head.getY() && !colisiona_arriba){   // ARRIBA
        movement.y += speed;

        if (actual != &run){
            //cout << "CAMBIAMOS A RUN" << endl;
            actual = &run;
            actual->sprite.setPosition(entityCenter);
        }
    }

    if(a.getX() > head.getX() && !colisiona_derecha){   // DERECHA
        dirMov = -1.f;
        movement.x -= speed;

        if (actual != &run){
            //cout << "CAMBIAMOS A RUN" << endl;
            actual = &run;
            actual->sprite.setPosition(entityCenter);
        }
        actual->sprite.setScale(1.f*dirMov, 1.f);
    }

    if (a.getX() < head.getX() && !colisiona_izquierda){    // IZQUIERDA
        dirMov = 1.f;
        movement.x += speed;

        if (actual != &run){
            //cout << "CAMBIAMOS A RUN" << endl;
            actual = &run;
            actual->sprite.setPosition(entityCenter);
        }
        actual->sprite.setScale(1.f*dirMov, 1.f);
    }

    /* COMPROBAR COLISIONES CON ESQUINAS */

    // if -> head arriba : comprobar coordenadas (izq o der del siguiente) y cambiar movement.x
        // if -> esquinas[0] y coordnow.x < coordhead.x : mover izq
        // else if -> esquinas[1] y coordnow.x > coordhead.x : mover der

    if(a.getX() == head.getX() && a.getY()-1 == head.getY())
    {
        if(esquinas[0] && coordnow.x < coordhead.x-0.5)
        {

            dirMov = 1.f;
            movement.x += speed;

            if (actual != &run){
                //cout << "CAMBIAMOS A RUN" << endl;
                actual = &run;
                actual->sprite.setPosition(entityCenter);
            }
            actual->sprite.setScale(1.f*dirMov, 1.f);
        }
        else if(esquinas[1] && coordnow.x > coordhead.x+0.5)
        {
            dirMov = -1.f;
            movement.x -= speed;

            if (actual != &run){
                //cout << "CAMBIAMOS A RUN" << endl;
                actual = &run;
                actual->sprite.setPosition(entityCenter);
            }
            actual->sprite.setScale(1.f*dirMov, 1.f);
        }
    }

    // if -> head abajo : comprobar coordenadas (izq o der del siguiente) y cambiar movement.x
        // if ->  coordnow.x < coordhead.x : mover izq
        // else if -> coordnow.x > coordhead.x : mover der


    if(a.getX() == head.getX() && a.getY()+1 == head.getY())
    {
        if(esquinas[2] && coordnow.x < coordhead.x-0.5)
        {

            dirMov = 1.f;
            movement.x += speed;

            if (actual != &run){
                //cout << "CAMBIAMOS A RUN" << endl;
                actual = &run;
                actual->sprite.setPosition(entityCenter);
            }
            actual->sprite.setScale(1.f*dirMov, 1.f);
        }
        else if(esquinas[3] && coordnow.x > coordhead.x+0.5)
        {
            dirMov = -1.f;
            movement.x -= speed;

            if (actual != &run){
                //cout << "CAMBIAMOS A RUN" << endl;
                actual = &run;
                actual->sprite.setPosition(entityCenter);
            }
            actual->sprite.setScale(1.f*dirMov, 1.f);
        }
    }


    // if -> head izquierda : comprobar coordenadas (arr o aba del siguiente) y cambiar movement.y
        // if -> coordnow.y < coordhead.y : mover aba
        // else if -> coordnow.y > coordhead.y : mover arr


    if(a.getY() == head.getY() && a.getX()-1 == head.getX())
    {
        if(esquinas[0] && coordnow.y < coordhead.y-0.5)
        {

            dirMov = 1.f;
            movement.y += speed;

            if (actual != &run){
                //cout << "CAMBIAMOS A RUN" << endl;
                actual = &run;
                actual->sprite.setPosition(entityCenter);
            }
            actual->sprite.setScale(1.f*dirMov, 1.f);
        }
        else if(esquinas[2] && coordnow.y > coordhead.y+0.5)
        {
            dirMov = -1.f;
            movement.y -= speed;

            if (actual != &run){
                //cout << "CAMBIAMOS A RUN" << endl;
                actual = &run;
                actual->sprite.setPosition(entityCenter);
            }
            actual->sprite.setScale(1.f*dirMov, 1.f);
        }
    }



    // if -> head derecha : comprobar coordenadas (arr o aba del siguiente) y cambiar movement.y
        // if -> coordnow.y < coordhead.y : mover aba
        // else if -> coordnow.y > coordhead.y : mover arr

    if(a.getY() == head.getY() && a.getX()+1 == head.getX())
    {
        if(esquinas[2] && coordnow.y < coordhead.y-0.5)
        {

            dirMov = 1.f;
            movement.y += speed;

            if (actual != &run){
                //cout << "CAMBIAMOS A RUN" << endl;
                actual = &run;
                actual->sprite.setPosition(entityCenter);
            }
            actual->sprite.setScale(1.f*dirMov, 1.f);
        }
        else if(esquinas[3] && coordnow.y > coordhead.y+0.5)
        {
            dirMov = -1.f;
            movement.y -= speed;

            if (actual != &run){
                //cout << "CAMBIAMOS A RUN" << endl;
                actual = &run;
                actual->sprite.setPosition(entityCenter);
            }
            actual->sprite.setScale(1.f*dirMov, 1.f);
        }
    }



    /* --------------------------------- */

    if(movement.x == 0 & movement.y == 0) {
        if (actual != &idle){
            //cout << "CAMBIAMOS A IDLE" << endl;
            actual = &idle;
            actual->sprite.setPosition(entityCenter);
            actual->sprite.setScale(1.f*dirMov, 1.f);
        }
    }

    colisiona_abajo = false;
    colisiona_arriba = false;
    colisiona_derecha = false;
    colisiona_izquierda = false;
}

bool Enemigo::serAtacado(sf::RectangleShape hitbox){
    bool res = false;

    if (hitbox.getGlobalBounds().intersects(entidadHitbox.getGlobalBounds()))
    {

        if(vida>0){
            vida--;
            actual->sprite.setColor(sf::Color::Red);
            cd.restart();
            res = true;
        }

        std::cout<<"Tiene de vida: "<<vida<<std::endl;
        if(vida==0){
            deleteSprite = true;
            std::cout<<"Ha sido matado"<<std::endl;
        }
    }

    return res;
}

void Enemigo::compruebaColor(){
    if(cd.getElapsedTime().asSeconds() >= 0.25){
        actual->sprite.setColor(sf::Color::White);
        cd.restart();

    }
}

int Enemigo::getVida(){
    return vida;
}

void Enemigo::draw(sf::RenderWindow &app) {
    if(!deleteSprite){
        app.draw(entidadHitbox);
        app.draw(actual->sprite);
    }
}

bool Enemigo::getBorrado()
{
    return deleteSprite;
}

