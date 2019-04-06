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

comprobarListaAb Astar::comprobarListaAbierta(Posicion caja, std::vector<Posicion> &listaAbi)
{
    comprobarListaAb res;

    if(listaAbi.size() >= 1)
    {
        for(int i = 0; i < listaAbi.size(); i++)
        {
            if(listaAbi.at(i).getX() == caja.getX() && listaAbi.at(i).getY() == caja.getY())
            {
                res.status = true;
                res.indice = i;
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

std::vector<Posicion> Astar::comprobarVecinos(Posicion padre, Mapa mapa)
{

    std::vector<Posicion> salida;
    Posicion player = padre;    //sera el ultimo en la lista abierta
    int puntosG[2] = {10, 200};
    int sonda[2] = {padre.getX(), padre.getY()};
    comprobarListaAb comprobarLista;
    bool **paredes = mapa.getMapa();

    //faltan agregar a los que estan en la lista blanca

    // arriba izquierda
    if(sonda[0]-1 != -1 && sonda[1]-1 != -1)
    {
        // comprueba si se puede pasar o no
        if(paredes[sonda[0]-1][sonda[1]-1] != 1)    //IMPORTANTE--> != 0 si las paredes son 0; != 1 si las paredes son 1
        {
            // comprueba que no se encuentre en la lista cerrada
            if(comprobarListaCerrada(Posicion(sonda[0]-1, sonda[1]-1, padre), *listaCerrada))
            {
                /*
                Si ya esta en la lista abierta: comprobar si el camino es mas eficiente
                Si el camino es mas eficiente: cambiar el padre por el padre actual, de lo contrario no hacer nada
                Si no esta en la lista: calcular todo normalmente
                */

                comprobarLista = comprobarListaAbierta(Posicion(sonda[0]-1, sonda[1]-1, padre), *listaAbierta);

                if(comprobarLista.status)
                {
                    if(G(player, puntosG[1]) < listaAbierta->at(comprobarLista.indice).getG())
                    {
                        //para sustituir la posicion primero se borra y luego se inserta la nueva mas eficiente

                        listaAbierta->erase(listaAbierta->begin()+comprobarLista.indice);

                        Posicion aux = Posicion(sonda[0]-1, sonda[1]-1, padre);
                        aux.setG(player, puntosG[1]);
                        aux.setH(heuristica(*ini));

                        listaAbierta->insert(listaAbierta->begin()+comprobarLista.indice, aux);

                    }
                }
                else
                {
                    Posicion aux = Posicion(sonda[0]-1, sonda[1]-1, padre);
                    aux.setG(player, puntosG[1]);
                    aux.setH(heuristica(*ini));

                    salida.insert(listaAbierta->begin()+comprobarLista.indice, aux);

                }

            }
        }
    }

    // arriba centro

    // arriba derecha

    // ...


    return salida;
}









