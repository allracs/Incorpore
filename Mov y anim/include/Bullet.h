#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <cmath>
#ifndef BULLET_H
#define BULLET_H


class Bullet
{

public:
    Bullet();
    ~Bullet();


    sf::CircleShape hitbox;
    sf::Vector2f currVelocity;
    float maxSpeed;
    void draw(sf::RenderWindow &app, std::vector<Bullet> bullets);

    Bullet(float radius = 5.f): currVelocity(0.f,0.f), maxSpeed(15.f)

    {
        this-> hitbox.setRadius(radius);
        this-> hitbox.setFillColor(sf::Color::Blue);
    }
};

#endif // BULLET_H
