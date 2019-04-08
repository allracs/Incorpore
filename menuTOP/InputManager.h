#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <vector>
#include<SFML/Graphics.hpp>

class InputManager
{
    public:
        InputManager();
        ~InputManager();
        void Update(sf::Event event);

        bool KeyPressed(int key);
        bool KeyPressed(std::vector<int> keys);

        bool KeyReleased(int key);
        bool KeyReleased(std::vector<int> keys);

        bool KeyDown(sf::RenderWindow &Window,sf::Keyboard::Key key);
        bool KeyDown(sf::RenderWindow &Window,std::vector<sf::Keyboard::Key> keys);


    protected:

    private:
    sf::Event event;
};

#endif // INPUTMANAGER_H
