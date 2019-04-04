
#include "Menu.h"


Menu::Menu(float ancho, float alto){

    if(!texture.loadFromFile("prueba.png")){
    std::cout <<"No carga imagen" <<std::endl;
    }
    else
    {
    std::cout <<"Cargada" <<std::endl;
    }


    if(!font.loadFromFile("KOMIKAX_.ttf")){
//        return EXIT_FAILURE;
        }


            //spriteFondoMenu = new Sprite();
        //titulo = new Sprite();
        //textTitulo = new Text();


    menu[0].setFont(font);
    menu[0].setColor(sf::Color::Red);
    menu[0].setString("Jugar");
    menu[0].setPosition(sf::Vector2f(ancho / 2, alto / (MAX_NUMBER_OF_ITEMS+1)*1));

    menu[1].setFont(font);
    menu[1].setColor(sf::Color::White);
    menu[1].setString("Controles");
    menu[1].setPosition(sf::Vector2f(ancho / 2, alto / (MAX_NUMBER_OF_ITEMS+1)*2));

    menu[2].setFont(font);
    menu[2].setColor(sf::Color::White);
    menu[2].setString("Salir");
    menu[2].setPosition(sf::Vector2f(ancho / 2, alto / (MAX_NUMBER_OF_ITEMS+1)*3));

    itemSelec=0;



}


Menu::~Menu(){

}

void Menu::draw(sf::RenderWindow &window){

    for(int i=0; i<MAX_NUMBER_OF_ITEMS;i++){

        window.draw(menu[i]);
    }
}


void Menu::MoverArriba(){

    if(itemSelec - 1>= 0){
        menu[itemSelec].setColor(sf::Color::White);
        itemSelec--;
        menu[itemSelec].setColor(sf::Color::Red);
    }
}


void Menu::MoverAbajo(){

    if(itemSelec + 1< MAX_NUMBER_OF_ITEMS){
        menu[itemSelec].setColor(sf::Color::White);
        itemSelec++;
        menu[itemSelec].setColor(sf::Color::Red);
    }
}
//void Menu::Clear(){}



//NUEVO
/*
void Menu:EqualizeMenuItems()
{
    for(int i=0;i<menu.size() ==i)
    {

    }
}

void Menu::SetAnimations()
{
    for(int i =0;i<menu.size();i++)
    {
        for(int j=0; j< animationTypes.size();j++)
        {

        }
    }
}
*/
