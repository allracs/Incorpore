#ifndef STATE_H
#define STATE_H

#include"SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include"SFML/System.hpp"
#include"SFML/Network.hpp"


#include<iostream>
#include<ctime>
#include<cstdlib>

#include<stack>
#include<vector>
#include<map>

#include "Entity.h"


class State
{
private:

protected:
    sf::RenderWindow* window;
    std::map<std::string, int>* supportedKeys;
    std::map<std::string, int> keybinds;
    bool quit;

    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;


    //recursos
    std::vector<sf::Texture> textures;

    //Functions
    virtual void initKeybinds()=0;


public:
    State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
    virtual ~State();

    const bool& getQuit() const;

     virtual void checkForQuit();


     virtual void endState()=0;
     virtual void updateMousePositions();
    //virtual void updateKeybinds(const float& dt)=0;
    virtual void updateInput(const float& dt)=0;
    virtual void update(const float& dt)=0;
    virtual void render(sf::RenderTarget* target = nullptr)=0;
    //virtual void render(sf::RenderTarget* target = NULL)=0;

    //los igual a 0 es como virtual
};

#endif
