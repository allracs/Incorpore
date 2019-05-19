#ifndef TUMBA_H
#define TUMBA_H
#include <SFML/Graphics.hpp>



class Tumba
{
    public:
        Tumba(sf::Vector2f pos);
        virtual ~Tumba();
        void draw(sf::RenderWindow &window);
    private:
        sf::Texture tTumba;
        sf::Sprite tumba;
};

#endif // TUMBA_H
