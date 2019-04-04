#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include "Astar.h"
#include "../include/Mapa.h"
#include "../include/Posicion.h"

Astar::Astar(Posicion i, Posicion f, Mapa *m)
{
    //ctor
    int alt, anc;
    alt = m->getAltura();
    anc = m->getAnchura();

    mapaArr = new bool*[alt];
    for(int a = 0; a < alt; a++)
    {
        mapaArr[a] = new bool[anc];
    }

    for(int a = 0; a < alt; a++)
    {
        for(int b = 0; b < anc; b++)
        {
            mapaArr[a][b] = m->getMapa()[a][b];
        }
    }

    // mapaArr = m->getMapa();

    listaCerrada->push_back(i);
    *ini = i;
    *fin = f;
}

Astar::~Astar()
{
    //dtor
    delete mapaArr;
    delete ini;
    delete fin;
}

std::vector<Posicion> Astar::mapear()
{

    int indiceIni = 0;
    bool rutaEncontrada = false;

    while(!rutaEncontrada)
    {
        vecinos = comprobarVecinos(ini, mapaArr);
        listaAbierta->insert(listaAbierta->begin(), vecinos->begin(), vecinos->end());
        indiceIni = obtenerMenorF();
        *ini = listaAbierta->at(indiceIni);
        removerLista(indiceIni);
        rutaEncontrada = finalizarLogica(*listaCerrada);
    }

    std::reverse(listaCerrada->begin(), listaCerrada->end());
    Posicion direccionIni = listaCerrada->front().getPadre();
    std::vector<Posicion> salidaFinal;
    salidaFinal.push_back(direccionIni);

    for(int i = 1; i < sizeof(listaCerrada)-1; i++)
    {
        if(listaCerrada->at(i).getX() == direccionIni.getX() && listaCerrada->at(i).getY() == direccionIni.getY())
        {
            salidaFinal.push_back(listaCerrada->at(i).getPadre());
        }
    }

    return salidaFinal;
}

int Astar::obtenerMenorF()
{
    int menor = 0;
    int indiceMenor = 0;

    if(listaAbierta->size() > 0)
    {
        menor = listaAbierta->at(0).getF();
        for(int i = 1; i < listaAbierta->size(); i++)
        {
            if(listaAbierta->at(i).getF() < menor)
            {
                menor = listaAbierta->at(i).getF();
                indiceMenor = i;
            }
        }
    }
    return indiceMenor;
}

void Astar::removerLista(int indicePadre)
{
    listaCerrada->push_back(listaAbierta->at(indicePadre));
    listaAbierta->erase(listaAbierta->begin()+indicePadre);
}

bool Astar::finalizarLogica(std::vector<Posicion> &listaCerr)
{
    bool res = false;

    for(int i = 0; i < listaCerr.size(); ++i)
    {
        if(listaCerr.at(i).getX() == fin->getX() && listaCerr.at(i).getY() == fin->getY())
        {
            res = true;
        }
    }
    return res;
}

bool Astar::comprobarListaCerrada(Posicion caja, std::vector<Posicion> &listaCerr)
{
    bool res = true;

    if(listaCerr.size() >= 1)
    {
        for(int i = 0; i < listaCerr.size(); i++)
        {
            if(listaCerr.at(i).getX() == caja.getX() && listaCerr.at(i).getY() == caja.getY())
            {
                res = false;
            }
        }
    }
    return res;
}

bool Astar::comprobarListaAbierta(Posicion caja, std::vector<Posicion> &listaAbi, int &indice)
{
    bool res = false;

    if(listaAbi.size() >= 1)
    {
        for(int i = 0; i < listaAbi.size(); i++)
        {
            if(listaAbi.at(i).getX() == caja.getX() && listaAbi.at(i).getY() == caja.getY())
            {
                res = true;
                indice = i;
            }
        }
    }
    return res;
}

int Astar::G(Posicion player, int valor)
{
    int salida = 0;

    if(player.getG() != -1)
    {
        salida = player.getG() + valor;
    }
    else
    {
        salida = valor;
    }
    return salida;
}


int Astar::heuristica(Posicion inicio)
{

    int h = (abs(inicio.getX() - fin->getX())) + (abs(inicio.getX() - fin->getY()));
    return h * 10;
}

