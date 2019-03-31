#include <iostream>
#include <vector>
#include <algorithm>
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
        indiceIni = obertenerMenorF();
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
