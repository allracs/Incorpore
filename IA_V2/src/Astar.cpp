#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include "Astar.h"

Astar::Astar(Posicion i, Posicion f, std::vector<Posicion> &m)
{
    //ctor
    *mapaArr = m;
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
        rutaEncontrada = finalizarLogica(listaCerrada);
    }

    std::reverse(listaCerrada->begin(), listaCerrada->end());

    Padre aux = listaCerrada->front().padre;
    Posicion direccionIni;
    aux.x = direccionIni.x;
    aux.y = direccionIni.y;
    std::vector<Posicion> salidaFinal;
    salidaFinal.push_back(direccionIni);

    for(int i = 1; i < sizeof(listaCerrada)-1; i++)
    {
        if(listaCerrada->at(i).x == direccionIni.x && listaCerrada->at(i).y == direccionIni.y)
        {
            aux = listaCerrada->at(i).padre;
            direccionIni.x = aux.x;
            direccionIni.y = aux.y;
            salidaFinal.push_back(direccionIni);
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
        menor = listaAbierta->at(0).f;
        for(int i = 1; i < listaAbierta->size(); i++)
        {
            if(listaAbierta->at(i).f < menor)
            {
                menor = listaAbierta->at(i).f;
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
        if(listaCerr.at(i).x == fin->x && listaCerr.at(i).y == fin->y)
        {
            res = true;
        }
    }
    return res;
}

bool Astar::comprobarListaCerrada(Padre caja, std::vector<Posicion> &listaCerr)
{
    bool res = true;

    if(listaCerr.size() >= 1)
    {
        for(int i = 0; i < listaCerr.size(); i++)
        {
            if(listaCerr.at(i).x == caja.x && listaCerr.at(i).y == caja.y)
            {
                res = false;
            }
        }
    }
    return res;
}

bool Astar::comprobarListaAbierta(Padre caja, std::vector<Posicion> &listaAbi, int &indice)
{
    bool res = false;

    if(listaAbi.size() >= 1)
    {
        for(int i = 0; i < listaAbi.size(); i++)
        {
            if(listaAbi.at(i).x == caja.x && listaAbi.at(i).y == caja.y)
            {
                res = true;
                indice = i;
            }
        }
    }
    return res;
}

int Astar::G(Padre player, int valor)
{
    int salida = 0;

    if(player.g != -1)
    {
        salida = player.g + valor;
    }
    else
    {
        salida = valor;
    }
    return salida;
}


int Astar::heuristica(Posicion inicio)
{
    int h = ()
}






