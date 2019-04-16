#include "../include/Enemigo.h"

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

void Enemigo::update(float delta, RenderWindow& window, int nCol, FloatRect* colisiones, Posicion pos_a, sf::RectangleShape enemigoHitbox){
    entityCenter = Vector2f(entidadHitbox.getPosition().x, entidadHitbox.getPosition().y);

    /*if(cd.getElapsedTime().asSeconds()>=0.3f){
        //serAtacado(enemigoHitbox);
        cd.restart();
    }*/

    // MOVIMIENTO
    seguirCamino(pos_a); // comprobar que el jugador se mueve

    entidadHitbox.move(movement * delta); // mover al jugador.
    ataqueHitbox.move(movement * delta);
    moverColisionadores(movement * delta);
    procesarColisiones(nCol, colisiones);
    actual->update(delta, movement);
    compruebaColor();
}

void Enemigo::seguirCamino(Posicion a){
    //aqui el enemigo sigue el camino
    movement = Vector2f(0.f, 0.f);
    Posicion s = path.at(0);
    //std::cout << colisiona_arriba << std::endl;
    if (a.getY() > s.getY() && !colisiona_abajo){    // ABAJO
        movement.y -= speed;
        if (actual != &run){
            //cout << "CAMBIAMOS A RUN" << endl;
            actual = &run;
            actual->sprite.setPosition(entityCenter);
        }
    }

    if (a.getY() < s.getY() && !colisiona_arriba){   // ARRIBA
        movement.y += speed;

        if (actual != &run){
            //cout << "CAMBIAMOS A RUN" << endl;
            actual = &run;
            actual->sprite.setPosition(entityCenter);
        }
    }

    if(a.getX() > s.getX() && !colisiona_derecha){   // DERECHA
        dirMov = -1.f;
        movement.x -= speed;

        if (actual != &run){
            //cout << "CAMBIAMOS A RUN" << endl;
            actual = &run;
            actual->sprite.setPosition(entityCenter);
        }
        actual->sprite.setScale(1.f*dirMov, 1.f);
    }

    if (a.getX() < s.getX() && !colisiona_izquierda){    // IZQUIERDA
        dirMov = 1.f;
        movement.x += speed;

        if (actual != &run){
            //cout << "CAMBIAMOS A RUN" << endl;
            actual = &run;
            actual->sprite.setPosition(entityCenter);
        }
        actual->sprite.setScale(1.f*dirMov, 1.f);
    }

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

void Enemigo::serAtacado(sf::RectangleShape hitbox){
    //El enemigo muere cuando la hitbox le toca y hacemos click
    if (hitbox.getGlobalBounds().intersects(entidadHitbox.getGlobalBounds()))
    {

        if(vida>0){
            vida--;
            actual->sprite.setColor(sf::Color::Red);
            cd.restart();
        }

        std::cout<<"Tiene de vida: "<<vida<<std::endl;
        if(vida==0){
            deleteSprite = true;
            std::cout<<"Ha sido matado"<<std::endl;
        }
    }
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

