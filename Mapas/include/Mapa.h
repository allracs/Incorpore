#include "tinyxml2.h"
#include "Entidad.h"
#include "Jugador.h"
#include "Enemigo.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace tinyxml2;
using namespace std;

class Mapa{
    public:
        Mapa();
        ~Mapa();
        void leerMapa(int);
        void cargaObjetos();

        void setDatos();

        void cargaTexturas();
        void creaSprite();

        void posicionaObjetos();
        void generaObjetos(int, int, int);
        void colisiones();

        void getDatos();
        int getNumCapas();
        int getHeight();
        int getWidth();
        Sprite**** getMapSprite();
        bool** getColisiones();
        int getNumColisiones();
        Vector2i getPosicionEntidad(Entidad);
        bool isColision(int,int);

        FloatRect* getBounds();

        //MOSTRAMOS POR PANTALLA
        void mostrarMapaColisiones();

        //DRAW
        void draw(RenderWindow&, Jugador, Enemigo*, int);

    private:
        int width, height, tilewidth, tileheight, gid;
        int nObj, maxObj;
        int cofre, calavera;
        int* antorcha, *caja, *cajadoble, *columna;
        int nColisiones;

        int nCapas = 0; //Numero de capas del tileset
        string nombreCapa; //nombre de la capa actual

        XMLDocument docXML; //Doc tmx
        XMLElement* mapaXML; //mapa
        XMLElement* imagenTileset; //Imagen tileset
        XMLElement *data;
        XMLElement* capa; //Capa del tileset

        string ficheroImagen; //Nombre y ruta del fichero imagen
        Texture texturaTileset; //textura del tileset

        int*** tileMap; //GIDs de los tiles del mapa
        Sprite* tilesetSprite;
        Sprite**** mapSprite;

        bool** colisionMap; //true = colision
        FloatRect* colision; //Bounding Boxes de las Colisiones
        Vector2i posicion;

};
