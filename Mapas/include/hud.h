
#include <SFML/Graphics.hpp>
#include <vector>

class hud
{
public:
    hud();
    ~hud();
    sf::Text getTextoVida();
    std::vector<sf::Sprite> getArrayVida();
    std::vector<sf::Sprite> getArrayHabilidades();
    sf::Sprite getCorazon();
    void setPosicionCorazones();
    void setPosicionHabilidades();
    void modificar_vida(int,int);
    void setHabilidad(int);
    void borradoHabilidades();
    int getCantidadVida();
    int getCantidadHabilidades();
    sf::RectangleShape getPiezaVida();
    sf::RectangleShape getPiezaHabilidades();
    void compruebaTeclas();
    void setPosition(int, int);

private:
    sf::Text *texto_vida;
    sf::Font *fuente;
    sf::RectangleShape * pieza_vida;
    sf::RectangleShape * pieza_habilidades;

    sf::Texture *textura_vida;
    sf::Sprite *corazon;
    sf::Texture *textura_habilidades;
    sf::Sprite *mejora_escudo;
    sf::Sprite *mejora_ataque;
    sf::Sprite *rompe_escudos;
    sf::Sprite *mana;
    sf::Sprite *mejora_cofre;
    sf::Sprite *espada_magica;

    bool mejora_escudo_esta = false;
    bool mejora_ataque_esta = false;
    bool rompe_escudos_esta = false;
    bool mana_esta = false;
    bool mejora_cofre_esta = false;
    bool espada_magica_esta = false;

    std::vector<sf::Sprite> *cantidad_corazones;
    std::vector<sf::Sprite> *vector_habilidades;
};
