#ifndef ASTAR_H
#define ASTAR_H
#include <vector>
#include <string>

typedef struct Padre
{
    int x, y;
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
        //TODO::-------------------------------------------------------------
        int obtenerMenorF();
        void removerLista(int indicePadre);
        bool finalizarLogica(std::vector<Posicion> &listaCerr);
        bool comprobarListaCerrada(Padre caja, std::vector<Posicion> &listaCerr);
        bool comprobarListaAbierta(Padre caja, std::vector<Posicion> &listaAbi);
        std::vector<Posicion> comprobarVecinos(Padre padre, std::vector<Posicion> mapa);
        int G(Padre player, std::vector<Posicion> puntosG);
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
