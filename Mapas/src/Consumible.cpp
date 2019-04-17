#include "../include/Consumible.h"

Consumible::Consumible(sf::Vector2f pos){
    srand(time(0));

    int random = rand() % 100 + 1;
    if(random < 50){
        creaConsumible(pos);
        std::cout << "Hay Consumible" << std::endl;
    }
    else{
        hayConsumible = false;
    }

}

Consumible::~Consumible(){
    delete tex;
    delete sprite;
}

void Consumible::creaConsumible(sf::Vector2f pos){
    tex = new sf::Texture;
    tex->loadFromFile("resources/tmx/tileset.png");
    int random = rand() % 100 + 1;
    sf::IntRect dim(117,212,7,11);

    if(random < 20){
        dim.left = 196;
        dim.top = 180;
        dim.width = 9;
        dim.height = 11;
    }
    sprite = new sf::Sprite(*tex);
    sprite->setTextureRect(dim);
    sprite->setPosition(pos);
    hayConsumible = true;

}

bool Consumible::consume(sf::RectangleShape pj){
    if(sprite->getGlobalBounds().intersects(pj.getGlobalBounds())){
            hayConsumible = false;
    }


}

sf::FloatRect Consumible::getConsumibleHitbox(){
    if(hayConsumible){
        sprite->getGlobalBounds();
    }
}

bool Consumible::isConsumible(){
    return hayConsumible;
}

void Consumible::draw(sf::RenderWindow &window){
    if(hayConsumible){
        window.draw(*sprite);
    }

}
