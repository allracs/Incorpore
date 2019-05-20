#include "../include/Mapa.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "math.h"

using namespace sf;
using namespace tinyxml2;
using namespace std;

Mapa::Mapa(int nivel){
//    std::cout << "NIVEL: " << nivel << std::endl;
    srand(time(NULL));
    if(nivel < 4){
        int random = rand() % 3 +1; //Un random del 1 al 2 (no existe el caso 0)
        leerMapa(random);
    }
    else{
        leerMapa(4);
    }

    if(tipo != 4 || true) //TODO quitar cuando no se haga delete de los objetos en el mapa 4
        cargaObjetos();
    setDatos();
    //getDatos();
    cargaTexturas();
    creaSprite();
    if(tipo != 4 || true) //TODO quitar cuando no se haga delete de los objetos en el mapa 4
        posicionaObjetos();
    colisiones();
    //mostrarMapaColisiones();
}

Mapa::~Mapa(){
    //Destructor
	delete caja;
    delete cajadoble;
    delete columna;
    delete antorcha;
    for(int i = 0; i <  nCapas; i++){
        for(int j = 0; j < height; j++){
            delete tileMap[i][j];
        }
        delete tileMap[i];

    }
	delete tileMap;

    for(int i = 0; i < height; i++){
        delete colisionMap[i];
    }
    delete colisionMap;


    for(int i = 0; i < nCapas; i++){
        for(int j = 0; j < height; j++){
            for(int z = 0; z < width; z++){
                delete mapSprite[i][j][z];          //TODO cuando sea el mapa 4 (tipo == 4) que no se borren los objetos generados porque no hay
            }
            delete mapSprite[i][j];
        }
        delete mapSprite[i];
    }
    delete mapSprite;

    for(int i = 0; i < antorchas.size(); i++){
        delete antorchas.at(i);
    }
    antorchas.clear();
    //delete tilesetSprite;
    delete colision;
    if(hayCofre)
    delete potenciadores;
   // delete colisionPortales;



}

void Mapa::cargaObjetos(){
    caja = new int[2];
    cajadoble = new int[2];
    columna = new int[2];
    antorcha = new int[2];

    antorcha[0] = 154-1;
    antorcha[1] = 170-1;

    caja[0] = 102-1;
    caja[1] = 118-1;

    cajadoble[0] = 103-1;
    cajadoble[1] = 119-1;

    calavera = 50-1;

    cofre = 224-1;

    columna[0] = 190-1;
    columna[1] = 206-1;
}

void Mapa::leerMapa(int n){
    tipo = 0;
    switch(n){
        case 1:
            docXML.LoadFile("resources/tmx/Mapa.tmx");
            tipo = 1;
            break;
        case 2:
            docXML.LoadFile("resources/tmx/Mapa2.tmx");
            tipo = 2;
            break;
        case 3:
            docXML.LoadFile("resources/tmx/Mapa3.tmx");
            tipo = 3;
            break;
        case 4:
            docXML.LoadFile("resources/tmx/MapaBoss.tmx");
            tipo = 4;
            break;
        default:
            std::cerr << "Error: Mapa no existente";
            exit(0);

    }

    mapaXML = docXML.FirstChildElement("map");
    maxObj = 12;
    nObj = 0;
    nColisiones = 0;
}

void Mapa::setDatos(){
    //Obtengo datos del tmx
    mapaXML->QueryIntAttribute("width", &width);
    mapaXML->QueryIntAttribute("height", &height);
    mapaXML->QueryIntAttribute("tilewidth", &tilewidth);
    mapaXML->QueryIntAttribute("tileheight", &tileheight);

    imagenTileset = mapaXML->FirstChildElement("tileset");
    ficheroImagen = (string)imagenTileset->FirstChildElement("image")->Attribute("source");
    capa = mapaXML->FirstChildElement("layer");
}

void Mapa::cargaTexturas(){

    while(imagenTileset){
        if(!texturaTileset.loadFromFile(ficheroImagen)){
            std::cerr << "Error cargando la textura png";
            exit(0);
        }
        imagenTileset = imagenTileset->NextSiblingElement("tileset");
    }

    //Cuento el numero de capas que hay
    while(capa){
        nCapas++;
        capa = capa->NextSiblingElement("layer");
    }


    capa = mapaXML->FirstChildElement("layer"); //Volvemos a apuntar a la primera capa
    tileMap = new int**[nCapas]; //Asignamos el numero de capas
    string* nombreCapa = new string[nCapas];

    //Bucle declaracion capas
    for(int i = 0; i <  nCapas; i++){
        tileMap[i] = new int*[height]; //Asignamos el alto
        for(int j = 0; j < height; j++){
            tileMap[i][j] = new int[width]; //Asignamos el ancho
        }
    }

    //Inicializacion mapa de colisiones
    colisionMap = new bool*[height];
    for(int i = 0; i < height; i++){
        colisionMap[i] = new bool[width];
    }

    //Bucle asignacion por capas
    int n = 0; //Capa en la que nos encontramos en el bucle
    while(capa){
        data = capa->FirstChildElement("data")->FirstChildElement("tile");
        nombreCapa[n] = (string)capa->Attribute("name");
        while(data){
            for(int i = 0; i < height; i++){
                for(int j = 0; j < width; j++){
                    data->QueryIntAttribute("gid", &tileMap[n][i][j]);
                    if(n == nCapas-1){
                        if(tileMap[n][i][j] != 0){
                            colisionMap[i][j] = true;
                            nColisiones++;
                        }
                        else{
                            colisionMap[i][j] = false;
                        }
                    }
                    data = data->NextSiblingElement("tile");
                }
            }
        }

        capa = capa->NextSiblingElement("layer");
        n++;
    }

}

void Mapa::creaSprite(){
    mapSprite = new Sprite***[nCapas];

    for(int i = 0; i < nCapas; i++){
        mapSprite[i] = new Sprite**[height];
        for(int j = 0; j < height; j++){
            mapSprite[i][j] = new Sprite*[width];
            for(int z = 0; z < width; z++){
                mapSprite[i][j][z] = new Sprite;
            }
        }
    }
    int columnas = texturaTileset.getSize().x / tilewidth;
    int filas = texturaTileset.getSize().y / tileheight;

    tilesetSprite = new Sprite[filas*columnas];
    int n = 0;
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            tilesetSprite[n].setTexture(texturaTileset);
            tilesetSprite[n].setTextureRect(IntRect(j*tilewidth,i*tileheight, tilewidth, tileheight));
            n++;
        }
    }
    srand(time(NULL));
    for(int i = 0; i < nCapas; i++){
        for(int j = 0; j < height; j++){
            for(int k = 0; k < width; k++){
                gid = tileMap[i][j][k]-1;
                if(gid>0 && gid < width*height){
                    mapSprite[i][j][k] = new Sprite(texturaTileset,tilesetSprite[gid].getTextureRect());
                    mapSprite[i][j][k]->setPosition(k*tilewidth,j*tileheight);
                }
                else{
                    mapSprite[i][j][k] = NULL;
                }
            }
        }
    }

}

void Mapa::posicionaObjetos(){
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if(colisionMap[i][j] == false && nObj < maxObj){
                int random = rand() % 100;
                //cout << random << endl;
                if(random < 25 &&
                   colisionMap[i-1][j-1] == false &&
                   colisionMap[i][j-1] == false &&
                   colisionMap[i+1][j-1] == false &&
                   colisionMap[i-1][j] == false &&
                   colisionMap[i+1][j] == false &&
                   colisionMap[i-1][j+1] == false &&
                   colisionMap[i][j+1] == false &&
                   colisionMap[i+1][j+1] == false){
                    generaObjetos(i, j, nObj);
                }
            }
        }
    }
}

sf::Vector2i Mapa::generaPortales(){
    int x;
    int y;
    switch(tipo){
        case 1:
            x = 10;
            y = 1;
        break;
        case 2:
            x = 10;
            y = 2;
        break;
        case 3:
        case 4:
            x = 10;
            y = 1;
        break;
        default:
            std::cerr << "Error: No se han podido crear Portales";
        break;
    }

    sf::Vector2i pos(x,y);
    return pos;
}

void Mapa::generaObjetos(int j, int k, int no){
    //srand(time(NULL));
    while(nObj == no) {
        int random = rand() % 100;
        if(random >= 0 && random < 29 && tipo != 4){
            //Antorcha
            posAnt.x = k*tilewidth;
            posAnt.y = j*tileheight;
            antorchas.push_back(new Antorcha(posAnt));
            colisionMap[j][k] = true;
            nColisiones++;
        }
        else  if(random >= 0 && random < 50){
            //Cofres
            if(!hayCofre){
                posAnt.x = k*tilewidth;
                posAnt.y = j*tileheight;
                potenciadores = new Potenciadores(posAnt);
                hayCofre = true;
            }
            //colisionMap[j][k] = true;
            //nColisiones++;
        }
        else if(random >= 39 && random < 59 && tipo != 4){
            //Caja
            mapSprite[3][j][k] = new Sprite(texturaTileset,tilesetSprite[caja[1]].getTextureRect());
            mapSprite[3][j][k]->setPosition(k*tilewidth,j*tileheight);

            mapSprite[6][j-1][k] = new Sprite(texturaTileset,tilesetSprite[caja[0]].getTextureRect());
            mapSprite[6][j-1][k]->setPosition(k*tilewidth,(j-1)*tileheight);
            colisionMap[j][k] = true;
            nColisiones++;
        }
        else if(random >= 59 && random < 74 && tipo != 4){
            //CajaDoble
            mapSprite[3][j][k] = new Sprite(texturaTileset,tilesetSprite[cajadoble[1]].getTextureRect());
            mapSprite[3][j][k]->setPosition(k*tilewidth,j*tileheight);

            mapSprite[6][j-1][k] = new Sprite(texturaTileset,tilesetSprite[cajadoble[0]].getTextureRect());
            mapSprite[6][j-1][k]->setPosition(k*tilewidth,(j-1)*tileheight);
            colisionMap[j][k] = true;
            nColisiones++;
        }
        else if(random >= 74 && random < 89 && tipo != 4){
            //Calavera
            mapSprite[3][j][k] = new Sprite(texturaTileset,tilesetSprite[calavera].getTextureRect());
            mapSprite[3][j][k]->setPosition(k*tilewidth,j*tileheight);
        }
        else if(random >= 0 && random < 100 && tipo != 4){
            //Columna
            mapSprite[3][j][k] = new Sprite(texturaTileset,tilesetSprite[columna[1]].getTextureRect());
            mapSprite[3][j][k]->setPosition(k*tilewidth,j*tileheight);

            mapSprite[6][j-1][k] = new Sprite(texturaTileset,tilesetSprite[columna[0]].getTextureRect());
            mapSprite[6][j-1][k]->setPosition(k*tilewidth,(j-1)*tileheight);
            colisionMap[j][k] = true;
            nColisiones++;
        }
        nObj++;
    }

}

void Mapa::colocaConsumibles(){
    int random = rand() % 100 +1;
    Vector2f pos;

    do{
        pos = generaPosicion();
    }while(isColision(pos.x/16, pos.y/16));

    int x = pos.x/16;
    int y = pos.y/16;

    if(random < 20){
        mapSprite[3][y][x] = new Sprite(texturaTileset,tilesetSprite[pocion].getTextureRect());
        mapSprite[3][y][x]->setPosition(x*tilewidth,y*tileheight);
    }
    else{
        mapSprite[3][y][x] = new Sprite(texturaTileset,tilesetSprite[pocionmini].getTextureRect());
        mapSprite[3][y][x]->setPosition(x*tilewidth,y*tileheight);
    }


}

void Mapa::colisiones(){
    int n = 0;

    colision = new FloatRect[nColisiones];
    Sprite box;

    for(int capa = 0; capa < nCapas; capa++){
        for(int alto = 0; alto < height; alto++){
            for(int ancho = 0; ancho < width; ancho++){
                if(n < nColisiones && colisionMap[alto][ancho] == true && mapSprite[capa][alto][ancho] != NULL){
                    box = *mapSprite[capa][alto][ancho];
                    colision[n] = box.getGlobalBounds();
                    n++;
                }
            }
        }
    }
}

void Mapa::getDatos(){
    cout << "ancho:" << width << endl;
    cout << "alto: " << height << endl;
    cout << "ancho tile: " << tilewidth << endl;
    cout << "alto tile: " << tileheight << endl;
    cout << "imagen: " << ficheroImagen << endl;
}

int Mapa::getNumCapas(){
    return nCapas;
}

int Mapa::getHeight(){
    return height;
}

int Mapa::getWidth(){
    return width;
}

Sprite**** Mapa::getMapSprite(){
    return mapSprite;
}

bool** Mapa::getColisiones(){
    return colisionMap;
}

int Mapa::getNumColisiones(){
    return nColisiones;
}

FloatRect* Mapa::getBounds(){
    return colision;
}

vector<Antorcha*> Mapa::getAntorchas(){
    return antorchas;
}

bool Mapa::existeCofre(){
    return hayCofre;
}
Potenciadores* Mapa::getCofre(){
    return potenciadores;
}


void Mapa::mostrarMapaColisiones(){
    cout << endl << "Mapa de colisiones:" << endl;
    cout <<  "------------------------" << endl;
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            cout << colisionMap[y][x];
        }
       cout << endl;
    }
    cout <<  "------------------------" << endl;
}

void Mapa::draw(RenderWindow& target, Jugador player, std::vector<Enemigo*> enemigos, int nEnemigos, std::vector<Tumba*> tumbas){
    for(int l = 0; l < nCapas; l++){
        for(int y = 0; y < height; y++){
            for(int x = 0; x < width; x++){
                if(mapSprite[l][y][x]!=NULL){

                    if(tipo == 4){
                        player.draw(target);
                        for(int i = 0; i < nEnemigos; i++){
                            enemigos.at(i)->draw(target);
                        }
                    }
                    target.draw(*(mapSprite[l][y][x]));
                    if(l == 3){
                        for(int i = 0; i < tumbas.size(); i++) {
                            tumbas.at(i)->draw(target);
                        }

                        if(hayCofre){
                            potenciadores->draw(target);
                        }

                        player.draw(target);

                        for(int i = 0; i < nEnemigos; i++){
                            enemigos.at(i)->draw(target);
                        }

                    } else if(l == 2){
                        for(int i = 0; i < antorchas.size(); i++){
                            antorchas.at(i)->draw(target);
                        }
                    } else if(l == 6){
                        for(int i = 0; i < antorchas.size(); i++){
                            antorchas.at(i)->drawFire(target);
                        }
                    }
                }
            }
        }
    }
}

Vector2i Mapa::getPosicionEntidad(Entidad e){
    Vector2f pos = e.getCenter();

    posicion.x = round(pos.x)/16;
    posicion.y = round(pos.y+0.05)/16;

    //cout << "X: " << posicion.x << endl;
    //cout << "Y: " << posicion.y << endl;

    return posicion;
}

bool Mapa::isColision(int x, int y){
    return colisionMap[y][x];
}

Vector2f Mapa::generaPosicion(){
    int randX, randY;
    do{
        randX = rand() % getWidth();
        randY = rand() % getHeight();
    }while(isColision(randX,randY));
    //cout <<"X: "<< randX << ", " <<"Y: "<< randY << " --> " << isColision(randX,randY) << endl;
    Vector2f pos({randX*16, randY*16});
    return pos;
}


