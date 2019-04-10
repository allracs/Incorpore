
#include "hud.h"

hud::hud()
{
    //PIEZA HUD VIDA
    pieza_vida = new sf::RectangleShape({115,20});
    pieza_vida->setFillColor(sf::Color::Blue);
    pieza_vida->setPosition(0,0);

    //TEXTO DE VIDA
    texto_vida = new sf::Text;
    fuente = new sf::Font;
    fuente->loadFromFile("resources/hud/coolvetica.ttf");
    texto_vida->setFont(*fuente);
    texto_vida->setString("Life");
    texto_vida->setScale(0.5, 0.5);
    texto_vida->setPosition(5, 0);

    //ARRAY DE CORAZONES
    textura_vida = new sf::Texture;
    textura_vida->loadFromFile("resources/hud/heart-life.png");

    corazon = new sf::Sprite;
    corazon->setTexture(*textura_vida);
    corazon->setScale({0.03,0.03});

    cantidad_corazones = new std::vector<sf::Sprite>;

    for(int i = 0; i < 3; i++)
    {
        cantidad_corazones->push_back(*corazon);
    }

    //ARRAY HABILIDADES
    vector_habilidades = new std::vector<sf::Sprite>;
    textura_habilidades = new sf::Texture;
    textura_habilidades->loadFromFile("resources/hud/habilidades.png");

    //mejora ataque
    mejora_ataque = new sf::Sprite(*textura_habilidades);
    mejora_ataque->setTextureRect(sf::IntRect(306,1,61,61));
    mejora_ataque->setScale(0.2, 0.2);

    //mejora cofre
    mejora_cofre = new sf::Sprite(*textura_habilidades);
    mejora_cofre->setTextureRect(sf::IntRect(61,122,61,61));
    mejora_cofre->setScale(0.2, 0.2);

    //mejora escudo
    mejora_escudo = new sf::Sprite(*textura_habilidades);
    mejora_escudo->setTextureRect(sf::IntRect(1,1,61,61));
    mejora_escudo->setScale(0.2, 0.2);

    //rompe-escudos
    rompe_escudos = new sf::Sprite(*textura_habilidades);
    rompe_escudos->setTextureRect(sf::IntRect(61,61,61,61));
    rompe_escudos->setScale(0.2, 0.2);

    //mana
    mana = new sf::Sprite(*textura_habilidades);
    mana->setTextureRect(sf::IntRect(122,1,61,61));
    mana->setScale(0.2, 0.2);

    //espada magica
    espada_magica = new sf::Sprite(*textura_habilidades);
    espada_magica->setTextureRect(sf::IntRect(244,61,61,61));
    espada_magica->setScale(0.2, 0.2);


    //PIEZA HUD HABILIDADES
    pieza_habilidades = new sf::RectangleShape({90,16});
    pieza_habilidades->setFillColor(sf::Color::Blue);
    pieza_habilidades->setOrigin(pieza_habilidades->getOrigin().x/2, pieza_habilidades->getOrigin().x/2);
    pieza_habilidades->setPosition(180,520);

}


void hud::modificar_vida(int cantidad, int sr)
{
    //sr = 1 -> suma vida
    //sr = 2 -> resta vida

    if(sr == 1 && cantidad_corazones->size() < 10)
    {
        cantidad_corazones->push_back(*corazon);
    }
    if(sr == 2 && cantidad_corazones->size() > 0)
    {
        cantidad_corazones->pop_back();
    }

}

void hud::borradoHabilidades()
{
    vector_habilidades->clear();
    mejora_escudo_esta = false;
    mejora_cofre_esta = false;
    mejora_ataque_esta = false;
    mana_esta = false;
    espada_magica_esta = false;
    rompe_escudos_esta = false;
}


void hud::compruebaTeclas(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        modificar_vida(1,1);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        modificar_vida(1,2);
    }

    ///HABILIDADES
    //borrar todas las habilidades
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        borradoHabilidades();
    }
    //coger habilidades
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
    {
        setHabilidad(1);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
    {
        setHabilidad(2);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
    {
        setHabilidad(3);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
    {
        setHabilidad(4);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
    {
        setHabilidad(5);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
    {
        setHabilidad(6);
    }
}


//SETTERS

void hud::setPosicionVida(int x, int y){
    pieza_vida->setPosition(x,y);
    texto_vida->setPosition(pieza_vida->getPosition().x, pieza_vida->getPosition().y);
    for(int i = 0; i < cantidad_corazones->size(); i++)
    {
        cantidad_corazones->at(i).setPosition({pieza_vida->getPosition().x + 24 + (i * 8), pieza_vida->getPosition().y + 2});
    }
}

void hud::setPosicionHabilidades(int x, int y){
    pieza_habilidades->setPosition(x,y);
    for(int i = 0; i < vector_habilidades->size(); i++)
    {
       vector_habilidades->at(i).setPosition({pieza_habilidades->getPosition().x + (i*15.5),pieza_habilidades->getPosition().y});
    }
}

void hud::setHabilidad(int habilidad)
{
    if(habilidad == 1 && mejora_escudo_esta == false)
    {
        vector_habilidades->push_back(*mejora_escudo);
        mejora_escudo_esta = true;
    }
    if(habilidad == 2 && mejora_cofre_esta == false)
    {
        vector_habilidades->push_back(*mejora_cofre);
        mejora_cofre_esta = true;
    }
    if(habilidad == 3 && mejora_ataque_esta == false)
    {
        vector_habilidades->push_back(*mejora_ataque);
        mejora_ataque_esta = true;
    }
    if(habilidad == 4 && mana_esta == false)
    {
        vector_habilidades->push_back(*mana);
        mana_esta = true;
    }
    if(habilidad == 5 && rompe_escudos_esta == false)
    {
        vector_habilidades->push_back(*rompe_escudos);
        rompe_escudos_esta = true;
    }
    if(habilidad == 6 && espada_magica_esta == false)
    {
        vector_habilidades->push_back(*espada_magica);
        espada_magica_esta = true;
    }
}

void hud::setPosition(int x, int y){
    pieza_vida->setPosition(x,y);
}

//GETTERS

sf::Text hud::getTextoVida()
{
    return *texto_vida;
}

std::vector<sf::Sprite> hud::getArrayVida()
{
    return *cantidad_corazones;
}

std::vector<sf::Sprite> hud::getArrayHabilidades()
{
    return *vector_habilidades;
}

sf::RectangleShape hud::getPiezaVida()
{
    return *pieza_vida;
}

sf::RectangleShape hud::getPiezaHabilidades()
{
    return *pieza_habilidades;
}

int hud::getCantidadVida()
{
    return cantidad_corazones->size();
}

int hud::getCantidadHabilidades()
{
    return vector_habilidades->size();
}

sf::Sprite hud::getCorazon()
{
    return *corazon;
}
