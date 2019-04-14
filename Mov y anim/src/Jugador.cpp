#include <SFML/Graphics.hpp>

#include "Jugador.h"

Jugador::Jugador(sf::Vector2f pos)
{
    // Variables del jugador

    this->jugadorHitbox = sf::RectangleShape(sf::Vector2f(12, 12));
    this->jugadorHitbox.setPosition(pos);
    this->jugadorHitbox.setOrigin(12/2, 12/2);
    this->jugadorHitbox.setFillColor(sf::Color::Transparent);
    this->jugadorHitbox.setOutlineThickness(1.f);
    this->jugadorHitbox.setOutlineColor(sf::Color::Green);
    this->rangeON = false;

    float dirMov = 1.f;


    speed = 100.f;
    movement = sf::Vector2f(0.f, 0.f);

    // Animaciones
    idle.setAnimacion("sprites/caballero.png", sf::IntRect(0,0,16,28), sf::IntRect(48,0,16,28), 16, 0.1f);
    idle.sprite.setOrigin(9,20);
    run.setAnimacion("sprites/caballero.png", sf::IntRect(0, 28, 16, 28), sf::IntRect(48, 28, 16, 28), 16, 0.1f);
    run.sprite.setOrigin(9,20);


    actual = &idle;

    actual->sprite.setPosition(pos);


    // Hitbox de ataque
    hitboxAtaque.setOutlineThickness(1);
    hitboxAtaque.setOutlineColor(sf::Color::Blue);
    hitboxAtaque.setFillColor(sf::Color::Transparent);
    hitboxAtaque.setSize(sf::Vector2f(20.f, 12.f));
    hitboxAtaque.setOrigin(0,6.f);
    hitboxAtaque.setPosition(pos);


    if(!swordText.loadFromFile("sprites/sword.png")){
        std::cout << "ERROR AL CARGAR TEXTURA: sword" << std::endl;
    }
    espada.setTexture(swordText);
    espada.setOrigin(14,14);
    espada.setPosition(hitboxAtaque.getPosition());
    espada.setScale(-1.f, -1.f);
    //espada.rotate(25.f);

}

Jugador::~Jugador()
{
    //dtor

}


void Jugador::rotacionAtaque(sf::RenderWindow &app) {
    sf::Vector2i pixelPos = sf::Vector2i(sf::Mouse::getPosition(app));

    mousePos = app.mapPixelToCoords(pixelPos);
    aimDir = mousePos - playerCenter;
    aimDirNorm = aimDir / (float)sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));

    float PI = 3.14159265;

    float dx = mousePos.x - playerCenter.x;
    float dy = mousePos.y - playerCenter.y;


    float rotation = (atan2(dy, dx)) * 180 / PI;
    hitboxAtaque.setRotation(rotation);
    espada.setRotation(rotation - 45.f);
    //std::cout << "ROTACION DE LA HITBOX: " << hitboxAtaque.getRotation() << std::endl;
    if(hitboxAtaque.getRotation() >= 90 && hitboxAtaque.getRotation() <= 270) {dirMov = -1;} else { dirMov = 1;}



}


void Jugador::moverse(){


    movement = sf::Vector2f(0.f, 0.f);
    //Movimiento del jugador

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        movement.y -= speed;
        if (actual != &run){
            //std::cout << "CAMBIAMOS A RUN" << std::endl;
            actual = &run;
            actual->sprite.setPosition(playerCenter);
        }

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        movement.y += speed;
        if (actual != &run){
            //std::cout << "CAMBIAMOS A RUN" << std::endl;
            actual = &run;
            actual->sprite.setPosition(playerCenter);
        }


    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        this->movement.x -= speed;

        if (actual != &run){
            //std::cout << "CAMBIAMOS A RUN" << std::endl;
            actual = &run;
            actual->sprite.setPosition(playerCenter);
        }




    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        this->movement.x += speed;

        if (actual != &run){
            //std::cout << "CAMBIAMOS A RUN" << std::endl;
            actual = &run;
            actual->sprite.setPosition(playerCenter);
        }


    }

    if(movement.x == 0 & movement.y == 0) {
        if (actual != &idle){
            //std::cout << "CAMBIAMOS A IDLE" << std::endl;
            actual = &idle;
            actual->sprite.setPosition(playerCenter);
        }
    }

}

/*
void Jugador::range(sf::RenderWindow &app){ //Activacion de ataque a distancia

//    Bullet::Bullet() b1;


    if(rangeON){
     if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                b1.hitbox.setPosition(playerCenter);
                b1.currVelocity = aimDirNorm * b1.maxSpeed;

                bullets.push_back(Bullet(b1));


            }
        }

         for(size_t i = 0; i < bullets.size(); i++){
            bullets[i].hitbox.move(bullets[i].currVelocity);
            //Para borrar los proyectiles
            if(bullets[i].hitbox.getPosition().x < 0 || bullets[i].hitbox.getPosition().x > app.getSize().x ||
               bullets[i].hitbox.getPosition().y < 0 || bullets[i].hitbox.getPosition().y > app.getSize().y )
               {
                bullets.erase(bullets.begin()+i);
               }
    }
}
*/

sf::Vector2f Jugador::getCenter(){
    //std::cout << "HA DEVUELTO EL PLAYER CENTER: " << playerCenter.x << "--" << playerCenter.y << std::endl;
    return playerCenter;
}

sf::Vector2f Jugador::getMousePos(){
    return this->mousePos;
}

sf::Vector2f Jugador::getMovement() {
    return this->movement;
}

sf::RectangleShape Jugador::getHitboxAtaque(){
    return this->hitboxAtaque;
}



void Jugador::update(float delta, sf::RenderWindow &app){

    playerCenter = sf::Vector2f(jugadorHitbox.getPosition().x, jugadorHitbox.getPosition().y);
    rotacionAtaque(app);
    actual->sprite.setScale(1.f*dirMov, 1.f);


    // MOVIMIENTO
    moverse(); // comprobar que el jugador se mueve
    jugadorHitbox.move(movement * delta); // mover al jugador.
    hitboxAtaque.move(movement * delta);
    espada.move(movement * delta);


    actual->update(delta, movement);


    /*
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        if(rangeON)
            rangeON = false;
         else
            rangeON = true;
    }


    if(rangeON){
        range(app);
    }
    */
}


void Jugador::draw(sf::RenderWindow &app) {
    app.draw(jugadorHitbox);

    if(hitboxAtaque.getRotation() >= 0 && hitboxAtaque.getRotation() <= 180) {
        app.draw(actual->sprite);
        app.draw(espada);
    } else {
        app.draw(espada);
        app.draw(actual->sprite);
    }
    app.draw(hitboxAtaque);

    //app.draw(app,bullets);
}



