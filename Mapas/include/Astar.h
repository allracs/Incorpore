#ifndef ASTAR_H
#define ASTAR_H
#include <vector>
#include <string>
#include "Posicion.h"

typedef struct comprobarListaAb
{
    bool status;
    int indice;
};

class Astar
{
    public:
        Astar(Posicion i, Posicion f, bool** mapa, int n, int m);
        virtual ~Astar();
        std::vector<Posicion> mapear();
        int obtenerMenorF();
        void removerLista(int indicePadre);
        bool finalizarLogica(std::vector<Posicion> &listaCerr);
        bool comprobarListaCerrada(Posicion caja, std::vector<Posicion> &listaCerr);
        comprobarListaAb comprobarListaAbierta(Posicion caja, std::vector<Posicion> &listaAbi);
        int G(Posicion player, int valor);
        int heuristica(Posicion inicio);
        std::vector<Posicion> comprobarVecinos(Posicion padre);

    protected:

    private:
        std::vector<Posicion> *listaAbierta, *listaCerrada;
        bool **mapaArr;
        int m_alt, m_anc;
        std::vector<Posicion> *vecinos;
        Posicion *ini;
        Posicion *fin;
};

#endif // ASTAR_H
