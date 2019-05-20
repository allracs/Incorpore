#include <SFML/Graphics.hpp>
#include "../include/Hud.h"
#include <string>
#include <iostream>
using namespace std;
using namespace sf;

Hud::Hud(int vidas,int hs,int hd, int ha){
    //PIEZA HUD VIDA
    vida = new Texture;
    baston = new Texture;
    espada = new Texture;
    textureSwitch = new Texture;
    textureEsquivar = new Texture;
    teclaEsquivar = new Texture;
    teclaSwitch = new Texture;

    vida->loadFromFile("resources/hud/abilities.png");
    baston->loadFromFile("resources/hud/baston.png");
    espada->loadFromFile("resources/hud/sword.png");
    textureSwitch->loadFromFile("resources/hud/change.png");
    textureEsquivar->loadFromFile("resources/hud/dodge.png");
    teclaEsquivar->loadFromFile("resources/hud/shift.png");
    teclaSwitch->loadFromFile("resources/hud/q.png");

    pieza_vida = new Sprite(*vida);
    sprite_switch = new Sprite(*textureSwitch);
    sprite_switch->setScale(0.2,0.2);
    sprite_esquivar = new Sprite(*textureEsquivar);
    sprite_esquivar->setScale(0.75,0.75);
    arma = new Sprite(*baston);
    arma->setScale(0.75,0.75);

    pieza_vida->setPosition(0,0);
    IntRect dim(0,0,295,66);
    pieza_vida->setTextureRect(dim);
    pieza_vida->scale(0.21, 0.15);

    // TEXTO DE VIDA
    texto_vida = new Text;
    fuente = new Font;
    fuente->loadFromFile("resources/hud/coolvetica.ttf");
    texto_vida->setFont(*fuente);
    texto_vida->setString("HP");
    texto_vida->setScale(0.25, 0.25);

    //Switch Arma
    tecla_switch = new Sprite(*teclaSwitch);
    tecla_switch->setScale(0.5, 0.5);

    //Indicador esquivar
    tecla_esquivar = new Sprite(*teclaEsquivar);
    tecla_esquivar->setScale(0.5, 0.5);

    //ARRAY DE CORAZONES
    textura_vida = new Texture;
    textura_vida->loadFromFile("resources/hud/heart-life.png");

    habilidades = new Texture;
    habilidades->loadFromFile("resources/hud/abilities.png");

    corazon = new Sprite;
    corazon->setTexture(*textura_vida);
    corazon->setScale({0.02,0.02});

    cantidad_corazones = new vector<Sprite>;

    for(int i = 0; i < vidas; i++){
        cantidad_corazones->push_back(*corazon);
    }

    //ARRAY HABILIDADES
    vector_habilidades = new vector<Sprite>;
    vector_tipos = new vector<int>;
    textura_habilidades = new Texture;
    textura_habilidades->loadFromFile("resources/hud/habilidades.png");

    //mejora ataque
    mejora_ataque = new Sprite(*textura_habilidades);
    mejora_ataque->setTextureRect(IntRect(306, 1, 61, 61));
    mejora_ataque->setScale(0.2, 0.2);
    mejora_ataque->setOrigin(30, 30);

    //rompe-escudos
    debilita_defensa = new Sprite(*textura_habilidades);
    debilita_defensa->setTextureRect(IntRect(61, 61, 61, 61));
    debilita_defensa->setScale(0.2, 0.2);
    debilita_defensa->setOrigin(30, 30);

    //mana
    debilita_velocidad = new Sprite(*textura_habilidades);
    debilita_velocidad->setTextureRect(IntRect(306, 122, 61, 61));
    debilita_velocidad->setScale(0.2, 0.2);
    debilita_velocidad->setOrigin(30, 30);

    //mejora escudo
    escudo = new Sprite(*textura_habilidades);
    escudo->setTextureRect(IntRect(61, 1, 61, 61));
    escudo->setScale(0.2, 0.2);
    escudo->setOrigin(30, 30);

    //PIEZA HUD HABILIDADES
    pieza_habilidades = new Sprite(*habilidades); // new RectangleShape({90,16});
    pieza_habilidades->setOrigin(pieza_habilidades->getOrigin().x/2, pieza_habilidades->getOrigin().x/2);

    //Numero de buffs
    textoAttack = new Text;
    textoAttack->setFont(*fuente);
    textoAttack->setScale(0.15, 0.15);

    textoDef = new Text;
    textoDef->setFont(*fuente);
    textoDef->setScale(0.15, 0.15);

    textoSpeed = new Text;
    textoSpeed->setFont(*fuente);
    textoSpeed->setScale(0.15, 0.15);
    nAtaque = ha;
    nDef = hd;
    nSpeed = hs;
}

void Hud::compruebaTeclas(){
    ///HABILIDADES
    //borrar todas las habilidades
    if(Keyboard::isKeyPressed(Keyboard::Z)){
        borradoHabilidades();
    } else if(Keyboard::isKeyPressed(Keyboard::Num1)){
        setHabilidad(1);
    } else if(Keyboard::isKeyPressed(Keyboard::Num2)){
        setHabilidad(2);
    } else if(Keyboard::isKeyPressed(Keyboard::Num3)){
        setHabilidad(3);
    } else if(Keyboard::isKeyPressed(Keyboard::Num4)){
        setHabilidad(4);
    }/* else if(Keyboard::isKeyPressed(Keyboard::Num5)){
        setHabilidad(5);
    } else if(Keyboard::isKeyPressed(Keyboard::Num6)){
        setHabilidad(6);
    }*/
}

void Hud::modificar_vida(int cantidad, int sr){
    if(sr == 1 && cantidad_corazones->size() < 5)
    {
        for(int i = 0; i < cantidad; i++){
            cantidad_corazones->push_back(*corazon);
        }
    }
    if(sr == 2 && cantidad_corazones->size() > 0){
        if(cantidad < 0){
            updateHabilidades();
            escudo_esta = false;
        }

        for(int i = 0; i < cantidad; i++){
            cantidad_corazones->pop_back();
        }
    }

    for(int i = 0; i < cantidad_corazones->size(); i++){
        cantidad_corazones->at(i).setPosition({pieza_vida->getPosition().x + (corazon->getGlobalBounds().width -3)*i, pieza_vida->getPosition().y + 1.25});
    }
}

void Hud::setHabilidad(int habilidad){
    if(habilidad == 1){
        if(mejora_ataque_esta == false){
            vector_habilidades->push_back(*mejora_ataque);
            mejora_ataque_esta = true;
        }
        nAtaque++;
        textoAttack->setString(to_string(nAtaque));
    }
    if(habilidad == 2){
        if(debilita_defensa_esta == false){
            vector_habilidades->push_back(*debilita_defensa);
            debilita_defensa_esta = true;
        }
        nDef++;
        textoDef->setString(to_string(nDef));
    }
    if(habilidad == 3){
        if(debilita_velocidad_esta == false){
            vector_habilidades->push_back(*debilita_velocidad);
            debilita_velocidad_esta = true;
        }
        nSpeed++;
        textoSpeed->setString(to_string(nSpeed));
    }
    if(habilidad == 4 && escudo_esta == false){
        vector_habilidades->push_back(*escudo);
        escudo_esta = true;
    }

    vector_tipos->push_back(habilidad);

    for(int i = 0; i < vector_habilidades->size(); i++){
        vector_habilidades->at(i).setPosition({pieza_habilidades->getPosition().x + 60 + (i*(vector_habilidades->at(i).getGlobalBounds().width + 4)),pieza_habilidades->getPosition().y + 10});

        switch(vector_tipos->at(i)){
            case 1:
                textoAttack->setPosition({vector_habilidades->at(i).getPosition().x - 0.75, vector_habilidades->at(i).getPosition().y + 6});
                break;
            case 2:
                textoDef->setPosition({vector_habilidades->at(i).getPosition().x - 0.75, vector_habilidades->at(i).getPosition().y + 6});
                break;
            case 3:
                textoSpeed->setPosition({vector_habilidades->at(i).getPosition().x - 0.75, vector_habilidades->at(i).getPosition().y + 6});
                break;
        }
    }
}

void Hud::borradoHabilidades(){
    vector_habilidades->clear();
    mejora_ataque_esta = false;
    debilita_defensa_esta = false;
    debilita_velocidad_esta = false;
    escudo_esta = false;
}

//SETTERS

void Hud::setPosicionVida(int x, int y){
    xVida = x;
    yVida = y;
    pieza_vida->setPosition(x,y);
    texto_vida->setPosition(pieza_vida->getPosition().x + 4, pieza_vida->getPosition().y);
    for(int i = 0; i < cantidad_corazones->size(); i++)
    {
        cantidad_corazones->at(i).setPosition({pieza_vida->getPosition().x + (corazon->getGlobalBounds().width -3)*i, pieza_vida->getPosition().y + 1.25});
    }
}

void Hud::setPosicionSwitch(int x,int y){
    xVida = x;
    yVida = y;
    sprite_switch->setPosition(x,y);
    arma->setPosition(sprite_switch->getPosition().x + sprite_switch->getGlobalBounds().width + 3, sprite_switch->getPosition().y);
    tecla_switch->setPosition(sprite_switch->getPosition().x - sprite_switch->getGlobalBounds().width - 8, sprite_switch->getPosition().y - 3);

    //Esquivar
    sprite_esquivar->setPosition(x-45,y);
    tecla_esquivar->setPosition(sprite_switch->getPosition().x - sprite_switch->getGlobalBounds().width - 60, sprite_switch->getPosition().y - 3);

}

void Hud::cambiaArma(int n){
    if(n == 1)
        arma->setTexture(*espada);
    else{
        arma->setTexture(*baston);
    }
}

void Hud::updateTeclas(bool cambio, bool dash){
    if(cambio){
        tecla_switch->setColor(Color::White);
    } else {
        tecla_switch->setColor(Color(50,50,50,180));
    }

    if(dash){
        tecla_esquivar->setColor(Color::White);
    } else {
        tecla_esquivar->setColor(Color(50,50,50,180));
    }
}

void Hud::setPosicionHabilidades(int x, int y){
    xHab = x;
    yHab = y;
    pieza_habilidades->setPosition(x,y);
}

void Hud::cambioNivel(int hs,int ha,int hd, bool shield){
    if(hs > 0){
        setHabilidad(3);
        textoSpeed->setString(to_string(hs));
    }
    if(ha > 0){
        setHabilidad(1);
        textoAttack->setString(to_string(ha));
    }
    if(hd > 0){
        setHabilidad(2);
        textoDef->setString(to_string(hd));
    }

    if(shield){
        setHabilidad(4);
    }


    nAtaque = ha;
    nDef = hd;
    nSpeed = hs;
}

//GETTERS

Sprite Hud::getCorazon(){
    return *corazon;
}

Text Hud::getTextoVida(){
    return *texto_vida;
}

Sprite Hud::getPiezaVida(){
    return *pieza_vida;
}

Sprite Hud::getPiezaHabilidades(){
    return *pieza_habilidades;
}

vector<Sprite> Hud::getArrayVida(){
    return *cantidad_corazones;
}

vector<Sprite> Hud::getArrayHabilidades(){
    return *vector_habilidades;
}

int Hud::getCantidadVida(){
    return cantidad_corazones->size();
}

int Hud::getCantidadHabilidades(){
    return vector_habilidades->size();
}

void Hud::draw(RenderWindow& target){
    //target.draw(*pieza_vida);
    //target.draw(*texto_vida);
    target.draw(*tecla_switch);
    target.draw(*arma);
    target.draw(*sprite_switch);
    target.draw(*tecla_esquivar);
    target.draw(*sprite_esquivar);

    for(int i = 0; i < cantidad_corazones->size(); i++)
    {
        target.draw(cantidad_corazones->at(i));
    }

    for(int i = 0; i < vector_habilidades->size(); i++)
    {
        target.draw(vector_habilidades->at(i));
    }

    if(nSpeed > 0){
        target.draw(*textoSpeed);
    }

    if(nDef > 0){
        target.draw(*textoDef);
    }


        target.draw(*textoAttack);
}

void Hud::updateHabilidades(){
    for(int i = 0; i < vector_habilidades->size(); i++){
        if(4 == vector_tipos->at(i)){
            vector_habilidades->erase(vector_habilidades->begin() + i);
        }
    }
}

void Hud::move(Vector2f delta){
    pieza_vida->move(delta);
    texto_vida->move(delta);
    textoAttack->move(delta);
    textoDef->move(delta);
    textoSpeed->move(delta);

    tecla_esquivar->move(delta);
    sprite_esquivar->move(delta);

    tecla_switch->move(delta);
    arma->move(delta);
    sprite_switch->move(delta);

    for(int i = 0; i < cantidad_corazones->size(); i++)
    {
        cantidad_corazones->at(i).move(delta);
    }
    pieza_habilidades->move(delta);
    for(int i = 0; i < vector_habilidades->size(); i++)
    {
       vector_habilidades->at(i).move(delta);
    }
}
