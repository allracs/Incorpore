#include "Bullet.h"

Bullet::Bullet()
{
    //ctor
}

Bullet::~Bullet()
{
    //dtor
}

void Bullet::draw(sf::RenderWindow &app,  std::vector<Bullet> bullets){

    for(size_t i = 0; i < bullets.size(); i++)
            {
                app.draw(bullets[i].hitbox);
            }

}
