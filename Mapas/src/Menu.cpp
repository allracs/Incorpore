#include "Menu.h"
#include "MaquinaEstados.h"
#include<memory>
#include<iostream>
#include "Juego.h"

Menu::Menu(MaquinaEstados& maquina, sf::RenderWindow& window, bool cambio): Estado {maquina, window, cambio}
{
    fuente = new sf::Font;
    fuente->loadFromFile("resources/menu/manaspc.ttf");
    jugar = new sf::Text;
    opciones = new sf::Text;
    salir = new sf::Text;

    //titulo
    titulofuente = new sf::Font;
    titulofuente->loadFromFile("resources/menu/Blockheads.ttf");
    titulo = new sf::Text;
    titulo->setFont(*titulofuente);
    titulo->setString("INCORPORE");
    titulo->setCharacterSize(150);
    //titulo->setPosition({500,50});
    titulo->setPosition({430,100});
    titulo->setScale(1,1);
    titulo->setColor(sf::Color::White);

    //fuente
    jugar->setFont(*fuente);
    opciones->setFont(*fuente);
    salir->setFont(*fuente);

    //color
    jugar->setColor(sf::Color::White);
    opciones->setColor(sf::Color::White);
    salir->setColor(sf::Color::White);

    //strings
    jugar->setString("Jugar");
    opciones->setString("Controles");
    salir->setString("Salir");

    //fondo
    texfondo = new sf::Texture();
    //texfondo->loadFromFile("src/menu2.jpeg");
    texfondo->loadFromFile("resources/menu/fondos.png");
    sprfondo = new sf::Sprite;
    sprfondo->setTexture(*texfondo);

    //fondo opciones
    texopciones = new sf::Texture();
    texopciones->loadFromFile("resources/menu/controles.png");
    spropciones = new sf::Sprite;
    spropciones->setTexture(*texopciones);

    botones = new std::vector<sf::Text>;
    for(int i = 0; i < 3; i++)
    {
        if(i ==0)
        botones->push_back(*jugar);

        if(i ==1)
        botones->push_back(*opciones);

        if(i ==2)
        botones->push_back(*salir);
    }

    std::cout << "Se inicializa el menu" << std::endl;
}

Menu::~Menu()
{
    //dtor
}

void Menu::cambio()
{
    if(clkmenu.getElapsedTime().asSeconds() > 0.15)
    {
        if(linea == 3 && num > 5)
        {
            linea = 1;
            num = 0;
        }
        if(num > 5 && linea < 3)
        {
            linea++;
            num = 1;
        }
        recortes(num);
        num++;
        clkmenu.restart();
    }

}

void Menu::recortes(int num)
{
    if(linea == 1)
    {
        sprfondo->setTextureRect(sf::IntRect(7200/6*num,0,7200/6,720));
        sprfondo->setScale(1.07,1.0);
    }

    if(linea == 2)
    {
        sprfondo->setTextureRect(sf::IntRect(7200/6*num,720,7200/6,720));
        sprfondo->setScale(1.07,1.0);
    }

    if(linea == 3)
    {
        sprfondo->setTextureRect(sf::IntRect(7200/6*num,1440,7200/6,720));
        sprfondo->setScale(1.07,1.0);
    }

}

void Menu::pause()
{
    std::cout << "Menu pausa" << std::endl;
}

void Menu::resume()
{
    std::cout << "Menu resume" << std::endl;
}

void Menu::update()
{
    eventos_raton();
    evento = new sf::Event;
    procesar_eventos();
    setColorOp();
    setPosicion(m_window.mapPixelToCoords((sf::Vector2i)m_window.getSize()).x, m_window.mapPixelToCoords((sf::Vector2i)m_window.getSize()).y /2);
}


void Menu::procesar_eventos()
{
    while(m_window.pollEvent(*evento))
    {
        switch(evento->type)
        {
        case sf::Event::Closed:
            m_window.close();
            break;
        case sf::Event::KeyReleased:
            switch(evento->key.code)
            {
                case sf::Keyboard::Up:
                    if(opcion_seleccionada == 0)
                    {
                        opcion_seleccionada = 2;
                    }else{
                        opcion_seleccionada -= 1;
                    }
                    break;

                case sf::Keyboard::W:
                    if(opcion_seleccionada == 0)
                    {
                        opcion_seleccionada = 2;
                    }else{
                        opcion_seleccionada -= 1;
                    }
                    break;

                case sf::Keyboard::Down:
                    if(opcion_seleccionada == 2)
                    {
                        opcion_seleccionada = 0;
                    }else{
                        opcion_seleccionada += 1;
                    }
                    break;

                case sf::Keyboard::S:
                    if(opcion_seleccionada == 2)
                    {
                        opcion_seleccionada = 0;
                    }else{
                        opcion_seleccionada += 1;
                    }
                    break;

                case sf::Keyboard::Space:
                    if(opcion_seleccionada == 0)
                    {
                        m_siguiente = MaquinaEstados::build<Juego>(m_maquina, m_window, true);
                    }
                    if(opcion_seleccionada == 1)
                    {
                        menuprincipal = false;
                    }
                    if(opcion_seleccionada == 2)
                    {
                        m_maquina.quit();
                        m_window.close();
                    }
                    break;

                case sf::Keyboard::Escape:
                    if(menuprincipal == true)
                    {
                        m_window.close();
                    }
                    if(menuprincipal == false){
                        menuprincipal = true;
                    }
                    break;
                default:
                    break;
            }
            break;
                case sf::Event::MouseButtonReleased:
                    if(opcion_seleccionada == 0)
                    {
                        m_siguiente = MaquinaEstados::build<Juego>(m_maquina, m_window, true);
                    }
                    if(opcion_seleccionada == 1)
                    {
                        menuprincipal = false;
                    }
                    if(opcion_seleccionada == 2)
                    {
                        m_maquina.quit();
                        m_window.close();
                    }
                    break;
                default:
                    break;
        }
    }
}


void Menu::eventos_raton()
{
    sf::FloatRect rectjugar;
    sf::FloatRect rectopciones;
    sf::FloatRect rectsalir;

    sf::RectangleShape recjugar;


    for(int i = 0; i < 3; i++)
    {
        if(i == 0)
        {
            rectjugar = jugar->getGlobalBounds();
            //std::cout << getOpciones().at(i).getPosition().x << "," << getOpciones().at(i).getPosition().x << std::endl;
        }
        if(i == 1)
        {
            rectopciones = opciones->getGlobalBounds();
        }
        if(i == 2)
        {
            rectsalir = salir->getGlobalBounds();
        }
    }

    //getOpciones().at(i).getGlobalBounds().contains( raton->getPosition().x - m_window.getPosition().x, raton->getPosition().y - m_window.getPosition().y)
    sf::Vector2i pixelPos = raton->getPosition(m_window);

    sf::Vector2f pPos = m_window.mapPixelToCoords(pixelPos);

    if(rectjugar.contains(pPos.x, pPos.y) && menuprincipal == true)
    {
        opcion_seleccionada = 0;
        sel_raton = true;
        sel_teclado = false;
    }
    else if(rectopciones.contains(pPos.x, pPos.y) && menuprincipal == true)
    {
        opcion_seleccionada = 1;
        sel_raton = true;
        sel_teclado = false;
    }
    else if(rectsalir.contains(pPos.x, pPos.y) && menuprincipal == true)
    {
        opcion_seleccionada = 2;
        sel_raton = true;
        sel_teclado = false;
    }

    //recjugar.setSize({opciones->width, opciones->height});
}



void Menu::setOpcionMenu(int num)
{
    if(num == 0)
    {
       seleccion = 0;
    }
    if(num == 1)
    {
       seleccion = 1;
    }
    if(num == 2)
    {
       seleccion = 2;
    }
    if(num == 3)
    {
        seleccion = 3;
    }
}

void Menu::setColorOp()
{
    botones->clear();

    if(opcion_seleccionada == 0)
    {
        jugar->setColor(sf::Color::Red);
       opciones->setColor(sf::Color::White);
       opciones->setScale(1,1);
       salir->setColor(sf::Color::White);
       salir->setScale(1,1);
    }
    else if(opcion_seleccionada == 1)
    {
        jugar->setColor(sf::Color::White);
        jugar->setScale(1,1);
       opciones->setColor(sf::Color::Red);
       salir->setColor(sf::Color::White);
         salir->setScale(1,1);
    }
    else if(opcion_seleccionada == 2)
    {
        jugar->setColor(sf::Color::White);
        jugar->setScale(1,1);
       opciones->setColor(sf::Color::White);
       opciones->setScale(1,1);
       salir->setColor(sf::Color::Red);
    }
    else if(seleccion == 3)
    {
        jugar->setColor(sf::Color::White);
        jugar->setScale(1,1);
        opciones->setColor(sf::Color::White);
        opciones->setScale(1,1);
        salir->setColor(sf::Color::White);
        salir->setScale(1,1);
    }

    for(int i = 0; i < 3; i++)
    {
        if(i ==0)
        botones->push_back(*jugar);

        if(i ==1)
        botones->push_back(*opciones);

        if(i ==2)
        botones->push_back(*salir);
    }
}

void Menu::setPosicion(int x, int y)
{
    jugar->setPosition((x/2) - (jugar->getGlobalBounds().width/2), y);
    opciones->setPosition((x/2) - (opciones->getGlobalBounds().width/2), y + 100);
    salir->setPosition((x/2) - (salir->getGlobalBounds().width/2), y + 200);
}




///DRAW
void Menu::draw()
{
    m_window.clear();

    //menu principal
    if(menuprincipal == true)
    {
        m_window.draw(*sprfondo);
        m_window.draw(*titulo);
        m_window.draw(*jugar);
        m_window.draw(*opciones);
        m_window.draw(*salir);
    }

    //menu opciones
    else if (menuprincipal == false)
    {
        m_window.draw(*spropciones);
    }

    m_window.display();
}

