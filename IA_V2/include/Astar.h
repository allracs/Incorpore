#ifndef ASTAR_H
#define ASTAR_H
#include <vector>
#include <string>

//TODO: convertir Posicion en clase
typedef struct Padre
{
    int x, y;
    int g, h, f;
    std::string tag;
};

typedef struct Posicion
{
    int x, y;
    int g, h, f;
    std::string tag;
    Padre padre;
};

class Astar
{
    public:
        Astar(Posicion i, Posicion f, std::vector<Posicion> &m);
        virtual ~Astar();
        std::vector<Posicion> mapear();
        int obtenerMenorF();
        void removerLista(int indicePadre);
        bool finalizarLogica(std::vector<Posicion> &listaCerr);
        bool comprobarListaCerrada(Padre caja, std::vector<Posicion> &listaCerr);
        bool comprobarListaAbierta(Padre caja, std::vector<Posicion> &listaAbi, int &indice); //indice: valor para recoger
        int G(Padre player, int valor);
        int heuristica(Posicion inicio);
        //TODO::-------------------------------------------------------------
        std::vector<Posicion> comprobarVecinos(Padre padre, std::vector<Posicion> mapa);
        //-------------------------------------------------------------------

    protected:

    private:
        std::vector<Posicion> *listaAbierta, *listaCerrada;
        std::vector<Posicion> *mapaArr;
        std::vector<Posicion> *vecinos;
        Posicion *ini;
        Posicion *fin;
};

#endif // ASTAR_H
