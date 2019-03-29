#include "InputManager.h"

InputManager::InputManager()
{
    //ctor
}

InputManager::~InputManager()
{
    //dtor
}
void InputManager::Update(sf::Event event)
{
    this->event = event;
}

bool InputManager::KeyPressed(int key)
{
    if(event.key.code==key && event.type == sf::Event::KeyPressed)
    {
        return true;
    }
    return false;

}

bool InputManager::KeyPressed(std::vector<int> keys)
{
    for(int i=0;i< keys.size();i++)
    {
       // if(event.key.code == keys[i])
       if(KeyPressed(keys[i]))
            return true;
    }
    return false;
}



bool InputManager::KeyReleased(int key)
{
    if(event.key.code == key && event.type == sf::Event::KeyReleased)
        return true;
    return false;
}
bool InputManager::KeyReleased(std::vector<int> keys)
{
    for(int i =0;i<keys.size();i++)
    {
        //if(event.key.code==keys[i] && event.type== sf::Event::KeyReleased)
        if(KeyReleased(keys[i]))
            return true;
    }
    return false;
}

bool InputManager::KeyDown(sf::RenderWindow &Window, sf::Keyboard::Key key)
{
 //   sf::RenderWindow &Window
//    if(Window.GetInput().IsKeyDown(key))
    if(sf::Keyboard::isKeyPressed(key))
    // (sf::Keyboard::)==key
    //OJO
    {
        return true;
    }
    return false;
}
bool InputManager::KeyDown(sf::RenderWindow &Window, std::vector<sf::Keyboard::Key> keys)
{
    for(int i =0;i<keys.size();i++)
    {
    //OJO
        if(sf::Keyboard::isKeyPressed(keys[i]))
            return true;
    }
    return false;
}





