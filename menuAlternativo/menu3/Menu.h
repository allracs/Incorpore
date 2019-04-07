

#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

#define MAX_NUMBER_OF_ITEMS 3

class Menu
{

public:
Menu(float ancho, float alto);
~Menu();

void draw(sf::RenderWindow &window);
void borra(sf::RenderWindow &window);
void MoverArriba();
void MoverAbajo();
int GetPressedItem()
{
return itemSelec;
}
void Inicializar();
void Clear();

//void render
void Update(sf::Time elapsedTime);

void HandleEvents(sf::Event& event);
void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
//void handleMOuseInput(sf::MOuse::button button, bool isPressed);
sf::Vector2f getPosition();
void UpdateView();

int getSelectedItemIndex()
{   return selectedItemIndex;
}

int SetSelectedItemIndex(int a)
{
    selectedItemIndex = a;
}
void pararMusica();



private:
    int itemSelec;
    sf::Font font;
    sf::Texture texture;
  //  sf::Texture texture;
//    sf::Sprite sprite(texture);
    sf::Text menu[MAX_NUMBER_OF_ITEMS];
    bool tecladoActivo;
    sf::Sprite *spriteFondoMenu;
    sf::Sprite *spriteFondo;
    sf::Sprite *spriteRelleno;
    sf::Sprite *titulo;
    int selectedItemIndex;
    sf::RectangleShape rectanguloFondo;




};
