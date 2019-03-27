#include "mapa.h"
using namespace sf;
using namespace tinyxml2;
using namespace std;

mapa::mapa(){
    leerMapa(1);
    setDatos();
    getDatos();
    cargaTexturas();
    creaSprite();
}

mapa::~mapa(){
    //Destructor
}

void mapa::leerMapa(int n){
    if(n == 1){
       docXML.LoadFile("resources/Mapa.tmx");
    }

    mapaXML = docXML.FirstChildElement("map");
}

void mapa::setDatos(){
    //Obtengo datos del tmx
    mapaXML->QueryIntAttribute("width", &width);
    mapaXML->QueryIntAttribute("height", &height);
    mapaXML->QueryIntAttribute("tilewidth", &tilewidth);
    mapaXML->QueryIntAttribute("tileheight", &tileheight);

    imagenTileset = mapaXML->FirstChildElement("tileset");
    ficheroImagen = (string)imagenTileset->FirstChildElement("image")->Attribute("source");
    capa = mapaXML->FirstChildElement("layer");
}

void mapa::cargaTexturas(){

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

    //Bucle asignacion por capas
    int n = 0; //Capa en la que nos encontramos en el bucle
    while(capa){
        data = capa->FirstChildElement("data")->FirstChildElement("tile");
        nombreCapa[n] = (string)capa->Attribute("name");
        while(data){
            for(int i = 0; i < height; i++){
                for(int j = 0; j < width; j++){
                    data->QueryIntAttribute("gid", &tileMap[n][i][j]);
                    data = data->NextSiblingElement("tile");
                }
            }
        }

        capa = capa->NextSiblingElement("layer");
        n++;
    }

}

void mapa::creaSprite(){
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

void mapa::getDatos(){
    cout << "ancho:" << width << endl;
    cout << "alto: " << height << endl;
    cout << "ancho tile: " << tilewidth << endl;
    cout << "alto tile: " << tileheight << endl;
    cout << "imagen: " << ficheroImagen << endl;
}

int mapa::getNumCapas(){
    return nCapas;
}

int mapa::getHeight(){
    return height;
}

int mapa::getWidth(){
    return width;
}

Sprite**** mapa::getMapSprite(){
    return mapSprite;
}
