
#include "hud.h"

hud::hud()
{
    //TEXTO DE VIDA
    texto_vida = new sf::Text;
    fuente = new sf::Font;
    fuente->loadFromFile("src/coolvetica.ttf");
    texto_vida->setFont(*fuente);
    texto_vida->setString("Life");
    texto_vida->setPosition(5,0);

    //ARRAY DE CORAZONES
    textura_vida = new sf::Texture;
    textura_vida->loadFromFile("src/heart-life.png");

    corazon = new sf::Sprite;
    corazon->setTexture(*textura_vida);
    corazon->setScale({0.06,0.06});

    cantidad_corazones = new std::vector<sf::Sprite>;

    for(int i = 0; i < 3; i++)
    {
        cantidad_corazones->push_back(*corazon);
    }
    setPosicionCorazones();

    //ARRAY HABILIDADES
    vector_habilidades = new std::vector<sf::Sprite>;
    textura_habilidades = new sf::Texture;
    textura_habilidades->loadFromFile("src/habilidades.png");

    //mejora ataque
    mejora_ataque = new sf::Sprite(*textura_habilidades);
    mejora_ataque->setTextureRect(sf::IntRect(306,1,61,61));

    //mejora cofre
    mejora_cofre = new sf::Sprite(*textura_habilidades);
    mejora_cofre->setTextureRect(sf::IntRect(61,122,61,61));

    //mejora escudo
    mejora_escudo = new sf::Sprite(*textura_habilidades);
    mejora_escudo->setTextureRect(sf::IntRect(1,1,61,61));

    //rompe-escudos
    rompe_escudos = new sf::Sprite(*textura_habilidades);
    rompe_escudos->setTextureRect(sf::IntRect(61,61,61,61));

    //mana
    mana = new sf::Sprite(*textura_habilidades);
    mana->setTextureRect(sf::IntRect(122,1,61,61));

    //espada magica
    espada_magica = new sf::Sprite(*textura_habilidades);
    espada_magica->setTextureRect(sf::IntRect(244,61,61,61));



    //PIEZA HUD VIDA
    pieza_vida = new sf::RectangleShape({280,40});
    pieza_vida->setFillColor(sf::Color::Blue);
    pieza_vida->setPosition(0,0);

    //PIEZA HUD HABILIDADES
    pieza_habilidades = new sf::RectangleShape({450,80});
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

    setPosicionCorazones();
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

//SETTERS

void hud::setPosicionCorazones()
{
    for(int i = 0; i < cantidad_corazones->size(); i++)
    {
        cantidad_corazones->at(i).setPosition({60+(i*20),5});
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

    setPosicionHabilidades();
}

void hud::setPosicionHabilidades()
{
    for(int i = 0; i < vector_habilidades->size(); i++)
    {
       vector_habilidades->at(i).setPosition({200 + (i*70),530});
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

