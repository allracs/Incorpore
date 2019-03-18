#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <vector>

int main()
{
    //Caracteristicas de la ventana
    sf::Vector2i screenDimensions(1080,720);
    sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Incorpore");
    window.setFramerateLimit(60);

    //Crear circulo y posicionarlo
    sf::CircleShape circle(50);
    circle.setPosition(sf::Vector2f(screenDimensions / 2));
    int cooldown = 0;
    sf::Vector2f playerCenter;

    //BALLS
	sf::CircleShape projectile;
	projectile.setFillColor(sf::Color::Red);
	projectile.setRadius(20.f);

	sf::RectangleShape enemy;
	enemy.setFillColor(sf::Color::Magenta);
	enemy.setSize(sf::Vector2f(50.f, 50.f));

	std::vector<sf::CircleShape> projectiles;
	projectiles.push_back(sf::CircleShape(projectile));

	std::vector<sf::RectangleShape> enemies;
	enemies.push_back(sf::RectangleShape(enemy));
	enemies[0].setPosition(200.f, 300.f);


    sf::Clock frameClock;

    //Velocidad del jugador
    float speed = 200.f;

    while (window.isOpen())
    {
        float mouseX = sf::Mouse::getPosition().x;
        float mouseY = sf::Mouse::getPosition().y;
        playerCenter = sf::Vector2f(circle.getPosition().x+circle.getRadius(), circle.getPosition().y);
        sf::Event event;


        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
        }

        sf::Time frameTime = frameClock.restart();
        //Movimiento
        sf::Vector2f movement(0.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            movement.y -= speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            movement.y += speed;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            movement.x -= speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            movement.x += speed;
        }
        circle.move(movement * frameTime.asSeconds());

         //PROYECTILES
		if (cooldown < 30)
			cooldown++;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && cooldown >= 30) //Atacar
		{
			projectile.setPosition(playerCenter);
			projectiles.push_back(sf::CircleShape(projectile));

			cooldown = 0;
		}

		for (size_t i = 0; i < projectiles.size(); i++)
		{
			projectiles[i].move(0.f, -10.f);

			if(projectiles[i].getPosition().y <= 0)
				projectiles.erase(projectiles.begin() + i);
		}

		//COLISIONES
		if (!enemies.empty() && !projectiles.empty())
		{
			for (size_t i = 0; i < projectiles.size(); i++)
			{
				for (size_t k = 0; k < enemies.size(); k++)
				{
					if (projectiles[i].getGlobalBounds().intersects(enemies[k].getGlobalBounds()))
					{
						projectiles.erase(projectiles.begin() + i);
						enemies.erase(enemies.begin() + k);
						break;
					}
				}
			}
		}



        //Dibujar circulo
        window.clear();
        window.draw(circle);

        for (size_t i = 0; i < enemies.size(); i++)
		{
			window.draw(enemies[i]);
		}

		for (size_t i = 0; i < projectiles.size(); i++)
		{
			window.draw(projectiles[i]);
		}


        window.display();
    }

    return 0;
}
