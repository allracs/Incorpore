#include <SFML/Graphics.hpp>
#include <cmath>

int main()
{
    sf::RenderWindow App(sf::VideoMode(800, 600), "SFML rect rotation");
    App.setFramerateLimit(5);
    float angle(0.f);
     sf::RectangleShape thing;
        thing.setFillColor(sf::Color::Green);
        thing.setSize(sf::Vector2f(50.f, 50.f));
        thing.setPosition(300, 300);
        thing.setPosition(250,250);
         sf::Event event;
         sf::Vector2i mousePos;
         sf::Vector2f playerCenter;


    while (App.isOpen())
    {
        playerCenter = sf::Vector2f(thing.getPosition());
        mousePos = sf::Mouse::getPosition(App);

        float PI = 3.14159265;

        float dx = mousePos.x - playerCenter.x;
        float dy = mousePos.y - playerCenter.y;


        float rotation = (atan2(dy, dx)) * 180 / PI;

        while (App.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                App.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                App.close();
        }

        thing.setRotation(rotation);

        App.clear();
        angle += 0.1f;
        App.draw(thing);
        App.display();
    }
}
