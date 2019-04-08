#include "tinyxml2.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace tinyxml2;
using namespace std;

class mapa{
    public:
        mapa();
        ~mapa();
        void leerMapa(int);
        void setDatos();
        void getDatos();
        void cargaTexturas();
        void creaSprite();
        int getNumCapas();
        int getHeight();
        int getWidth();
        void generaObjetos();
        void colisiones();
        Sprite**** getMapSprite();
        bool** getColisiones();
    private:
        int width, height,tilewidth, tileheight, gid;
        XMLDocument docXML; //Doc tmx
        XMLElement* mapaXML; //mapa
        XMLElement* imagenTileset; //Imagen tileset
        string ficheroImagen; //Nombre y ruta del fichero imagen
        Texture texturaTileset; //textura del tileset
        XMLElement* capa; //Capa del tileset
        bool** colisionMap; //true = colision
        int nCapas = 0; //Numero de capas del tileset
        string nombreCapa; //nombre de la capa actual
        int*** tileMap;
        XMLElement *data;
        Sprite* tilesetSprite;
        Sprite**** mapSprite;
};
