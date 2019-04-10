
#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;
using namespace sf;

class Hud{
public:
    Hud();
    ~Hud();
    Text getTextoVida();
    vector<Sprite> getArrayVida();
    vector<Sprite> getArrayHabilidades();
    Sprite getCorazon();
    void modificar_vida(int,int);
    void borradoHabilidades();
    int getCantidadVida();
    int getCantidadHabilidades();
    RectangleShape getPiezaVida();
    RectangleShape getPiezaHabilidades();
    void compruebaTeclas();
    void setHabilidad(int);
    void setPosition(int, int);
    void setPosicionVida(int, int);
    void setPosicionHabilidades(int, int);
    void draw(RenderWindow&);
private:
    Text *texto_vida;
    Font *fuente;
    RectangleShape * pieza_vida;
    RectangleShape * pieza_habilidades;

    Texture *textura_vida;
    Sprite *corazon;
    Texture *textura_habilidades;
    Sprite *mejora_escudo;
    Sprite *mejora_ataque;
    Sprite *rompe_escudos;
    Sprite *mana;
    Sprite *mejora_cofre;
    Sprite *espada_magica;

    bool mejora_escudo_esta = false;
    bool mejora_ataque_esta = false;
    bool rompe_escudos_esta = false;
    bool mana_esta = false;
    bool mejora_cofre_esta = false;
    bool espada_magica_esta = false;

    vector<Sprite> *cantidad_corazones;
    vector<Sprite> *vector_habilidades;
};
