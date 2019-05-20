#include "Jefe.h"
#include <math.h>

Jefe::Jefe(sf::Vector2f ini)
{
    //ctor
    estado = 0;
    vida = 10;
    atacando = false;

    posFdash = {-1.f, -1.f};
    collision = new sf::RectangleShape();
    collision->setSize({30.f, 30.f});
    collision->setOrigin(collision->getGlobalBounds().width/2, collision->getGlobalBounds().height/2);
    collision->setFillColor(sf::Color::Red);
    collision->setPosition(ini);

    srand(time(NULL));
    dirCaminar = rand() % 8;

    idle.setAnimacion("resources/sprites/medusa-idle.png", sf::IntRect(0,0,48,56), sf::IntRect(384,0,48,56), 48, 0.1f);
    idle.sprite.setOrigin(48/2, 48/2);
    idle.sprite.setScale({0.65f, 0.65f});

    disparar.setAnimacion("resources/sprites/medusa-ataque.png", sf::IntRect(0,0,48,56), sf::IntRect(0,0,48,56), 0, 0.1f);
    disparar.sprite.setOrigin(48/2, 60/2);
    disparar.sprite.setScale({0.65f, 0.65f});

    actual = &idle;
    actual->sprite.setPosition(collision->getPosition().x, collision->getPosition().y);
}

Jefe::~Jefe()
{
    //dtor
    delete collision, actual;
}

void Jefe::update(sf::Vector2f posJ, int nCol, sf::FloatRect* colisiones)
{
    estados(posJ);
    manejarDisp(nCol, colisiones);
    actual->update();
}

void Jefe::draw(sf::RenderWindow& w)
{
    //w.draw(*collision);
    for(int a = 0; a < balas.size(); a++)
    {
        balas.at(a)->draw(w);
    }
    w.draw(actual->sprite);
}

void Jefe::estados(sf::Vector2f posJ)
{

    switch(estado)
    {
        case 0:
            caminar();

            if(cestados.getElapsedTime().asSeconds() >= 4)
            {
                actual = &idle; //cambiar a dahsAnimacion
                actual->sprite.setPosition(collision->getPosition());
                cestados.restart();
                estado = 1;
                atacando = true;
            }
            break;

        case 1:
            if(posFdash.x == -1 && posFdash.y == -1)
            {
                posFdash = posJ;
            }
            dash();

            if(finDash)
            {
                posFdash = {-1.f, -1.f};
                finDash = !finDash;

                srand(time(NULL));
                dirCaminar = rand() % 8;
                atacando = false;
                cestados.restart();
                estado = 2;
                actual = &idle;
                actual->sprite.setPosition(collision->getPosition());
                cmov.restart(); // el siguiente estado es moverse
            }
            break;

        case 2:
            caminar();

            if(cestados.getElapsedTime().asSeconds() >= 4)
            {
                cestados.restart();
                estado = 3;
                actual = &disparar;
                actual->sprite.setPosition(collision->getPosition());
                cdispCD.restart();
            }
            break;

        case 3:
            disparo8dir();

            if(cestados.getElapsedTime().asSeconds() >= 3)
            {
                srand(time(NULL));
                dirCaminar = rand() % 8;
                actual = &idle;
                actual->sprite.setPosition(collision->getPosition());
                cestados.restart();
                estado = 0;

                cmov.restart(); // el siguiente estado es moverse
            }
            break;
    }

}

void Jefe::dash()
{
    sf::Time time = cmov.getElapsedTime();

    int x = posFdash.x;
    int y = posFdash.y;

    int dx, dy;
    dx = collision->getPosition().x - x;
    dy = collision->getPosition().y - y;

    float h = sqrt((pow(dx, 2))+(pow(dy, 2)));
    float xe = dx * he / h;
    float ye = dy * he / h;

    if(h > 0){
        if(dx > collision->getPosition().x)
        {
            if(dy > collision->getPosition().y) //si el jugador esta arriba - derecha
            {
                collision->move(xe * time.asMilliseconds(), ye * time.asMilliseconds());
                actual->sprite.move(xe * time.asMilliseconds(), ye * time.asMilliseconds());
                actual->sprite.setScale({-0.65f, 0.65f});
            }
            else                            //si el jugador esta abajo - derecha
            {
                collision->move(xe * time.asMilliseconds(), -ye * time.asMilliseconds());
                actual->sprite.move(xe * time.asMilliseconds(), -ye * time.asMilliseconds());
                actual->sprite.setScale({-0.65f, 0.65f});
            }
        }
        else
        {
            if(dy > collision->getPosition().y) //si el jugador esta arriba - izquierda
            {
                collision->move(-xe * time.asMilliseconds(), ye * time.asMilliseconds());
                actual->sprite.move(-xe * time.asMilliseconds(), ye * time.asMilliseconds());
                actual->sprite.setScale({0.65f, 0.65f});
            }
            else                            //si el jugador esta abajo - izquierda
            {
                collision->move(-xe * time.asMilliseconds(), -ye * time.asMilliseconds());
                actual->sprite.move(-xe * time.asMilliseconds(), -ye * time.asMilliseconds());
                actual->sprite.setScale({0.65f, 0.65f});
            }
        }
    }


    if(collision->getPosition().x >= posFdash.x - 5 && collision->getPosition().x <= posFdash.x + 5 &&
       collision->getPosition().y >= posFdash.y - 5 && collision->getPosition().y <= posFdash.y + 5)
    {
        finDash = true;
    }

    cmov.restart();
}

void Jefe::caminar()
{

    if(collision->getPosition().x <= 70 || collision->getPosition().x >= 345 ||
       collision->getPosition().y <= 40 || collision->getPosition().y >= 240)
    {
        srand(time(NULL));
        dirCaminar = rand() % 8;
    }

    int x = 0, y = 0;
    switch(dirCaminar)
    {
        case 0:
            x = -1;
            y = -1;
            actual->sprite.setScale({0.65f, 0.65f});
            break;

        case 1:
            y = -1;
            break;

        case 2:
            x = 1;
            y = -1;
            actual->sprite.setScale({-0.65f, 0.65f});
            break;

        case 3:
            x = 1;
            actual->sprite.setScale({-0.65f, 0.65f});
            break;

        case 4:
            x = 1;
            y = 1;
            actual->sprite.setScale({-0.65f, 0.65f});
            break;

        case 5:
            y = 1;
            break;

        case 6:
            x = -1;
            y = 1;
            actual->sprite.setScale({0.65f, 0.65f});
            break;

        case 7:
            x = -1;
            actual->sprite.setScale({0.65f, 0.65f});
            break;
    }

    sf::Time time = cmov.getElapsedTime();
    if(collision->getPosition().x >= 50 && collision->getPosition().x <= 345 &&
       collision->getPosition().y >= 40 && collision->getPosition().y <= 260)
    {
        collision->move(x * he/4 * time.asMilliseconds(), y * he/4 * time.asMilliseconds());
        actual->sprite.move(x * he/4 * time.asMilliseconds(), y * he/4 * time.asMilliseconds());

    }
    cmov.restart();
}

void Jefe::disparo8dir()
{
    if(cdispCD.getElapsedTime().asSeconds() >= 0.15)
    {
        /*CREAR 8 PROYECTILES*/
        //balas.push_back(new P...) en 8 dir
        sf::Vector2f pos = {collision->getPosition().x - 8, collision->getPosition().y - 8};

        balas.push_back(new Proyectil(pos, {-0.2, -0.2}, 0.f, 2));
        balas.push_back(new Proyectil(pos, {   0, -0.2}, 0.f, 2));
        balas.push_back(new Proyectil(pos, { 0.2, -0.2}, 0.f, 2));
        balas.push_back(new Proyectil(pos, { 0.2,    0}, 0.f, 2));
        balas.push_back(new Proyectil(pos, { 0.2,  0.2}, 0.f, 2));
        balas.push_back(new Proyectil(pos, {   0,  0.2}, 0.f, 2));
        balas.push_back(new Proyectil(pos, {-0.2,  0.2}, 0.f, 2));
        balas.push_back(new Proyectil(pos, {-0.2,    0}, 0.f, 2));

        cdispCD.restart();
    }
}

void Jefe::manejarDisp(int nCol, sf::FloatRect* colisiones)
{
    for(int a = 0; a < balas.size(); a++)
    {
        balas.at(a)->update(nCol, colisiones);
        if(balas.at(a)->getColision().getPosition().x <= 20 || balas.at(a)->getColision().getPosition().x >= 370 ||
           balas.at(a)->getColision().getPosition().y <= 20 || balas.at(a)->getColision().getPosition().y >= 270)
        {
            destruirBala(a);
        }
    }
}

void Jefe::destruirBala(int a)
{
    delete balas.at(a);
    balas.erase(balas.begin()+a);
}

bool Jefe::restarVida(sf::RectangleShape arma)
{
    bool res = false;
    if(collision->getGlobalBounds().intersects(arma.getGlobalBounds()) && vida-- <= 0)
    {
        res = true;
    }
    return res;
}

bool Jefe::restarVida(std::vector<Proyectil*> pr)
{
    bool res = false;
    for(int a = 0; a < pr.size(); a++)
    {
        if(collision->getGlobalBounds().intersects(pr.at(a)->getColision().getGlobalBounds()))
        {
            pr.at(a)->setHacolisionado(true);
            if(vida-- <= 0)
            {
                res = true;
            }
            break;
        }
    }
    return res;
}

int Jefe::getVida()
{
    return vida;
}

bool Jefe::getAtaque()
{
    return atacando;
}

sf::RectangleShape* Jefe::getCollision()
{
    return collision;
}

std::vector<Proyectil*> Jefe::getBalas()
{
    return balas;
}
