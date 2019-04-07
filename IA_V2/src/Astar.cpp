#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <math.h>
#include "Astar.h"
#include "../include/Mapa.h"
#include "../include/Posicion.h"

Astar::Astar(Posicion i, Posicion f, Mapa &m)
{
    //ctor
    std::cout << "creando ia (constr)" << std::endl;
    int alt, anc;
    alt = m.getAltura();
    anc = m.getAnchura();

    mapaArr = m.getMapa();
    mapa = &m;

    listaAbierta = new std::vector<Posicion>;
    listaCerrada = new std::vector<Posicion>;
    vecinos = new std::vector<Posicion>;

    if(listaCerrada->size() == 0)
        listaCerrada->insert(listaCerrada->begin(),i);
    std::cout << "Lista Cerrada size: " << listaCerrada->size() << std::endl;
    std::cout << "Lista Abierta size: " << listaAbierta->size() << std::endl;

    ini = new Posicion(i.getX(), i.getY());
    fin = new Posicion(f.getX(), f.getY());
    std::cout << ini->getX() << " --- " << ini->getY() << std::endl;
    std::cout << "fin creando ia (constr)" << std::endl;
}

Astar::~Astar()
{
    //dtor
    /*
    delete mapaArr;
    delete mapa;
    delete listaAbierta;
    delete listaCerrada;
    delete ini;
    delete fin;
    */
}

std::vector<Posicion> Astar::mapear()
{

    int indiceIni = 0;
    bool rutaEncontrada = false;

    while(!rutaEncontrada)
    {
        std::cout << "antes de comprobar: " << mapa->getMapa()[0][0] << std::endl;
        *vecinos = comprobarVecinos(*ini, *mapa);
        std::cout << "vecinos comprobados" << std::endl;
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
                std::cout << "RES INDICE: " << res.indice << std::endl;
                break;
            }
        }
    }
    else
    {
        res.status = false;
        res.indice = 0;
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
    std::cout << "SALIDA SIZE: " << salida.size() << std::endl;
    Posicion player = padre;    //sera el ultimo en la lista abierta
    int puntosG[2] = {10, 200};
    int sonda[2] = {padre.getX(), padre.getY()};
    comprobarListaAb comprobarLista;
    bool **paredes = mapa.getMapa();
    std::cout << "comprobandoVecinos (method)" << std::endl;
    for(int a = 0; a < mapa.getAltura(); a++)
    {
        for(int b = 0; b < mapa.getAnchura(); b++)
        {
            std::cout << paredes[a][b];
        }
        std::cout << std::endl;
    }

    //faltan agregar a los que estan en la lista blanca

    // arriba izquierda
    if(sonda[0]-1 != -1 && sonda[1]-1 != -1)
    {
        // comprueba si se puede pasar o no
        if(paredes[sonda[0]-1][sonda[1]-1] != 0)    //IMPORTANTE--> != 0 si las paredes son 0; != 1 si las paredes son 1
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
                        aux.setH(heuristica(Posicion(sonda[0]-1, sonda[1]-1, padre)));

                        listaAbierta->insert(listaAbierta->begin()+comprobarLista.indice, aux);

                    }
                }
                else
                {
                    Posicion aux = Posicion(sonda[0]-1, sonda[1]-1, padre);
                    aux.setG(player, puntosG[1]);
                    aux.setH(heuristica(Posicion(sonda[0]-1, sonda[1]-1, padre)));

                    salida.insert(salida.begin()+comprobarLista.indice, aux);

                }

            }
        }
    }

    // arriba centro
    if(sonda[1]-1 != -1)
    {
        // comprueba si se puede pasar o no
        if(paredes[sonda[0]][sonda[1]-1] != 0)    //IMPORTANTE--> != 0 si las paredes son 0; != 1 si las paredes son 1
        {
            // comprueba que no se encuentre en la lista cerrada
            if(comprobarListaCerrada(Posicion(sonda[0], sonda[1]-1, padre), *listaCerrada))
            {
                /*
                Si ya esta en la lista abierta: comprobar si el camino es mas eficiente
                Si el camino es mas eficiente: cambiar el padre por el padre actual, de lo contrario no hacer nada
                Si no esta en la lista: calcular todo normalmente
                */

                comprobarLista = comprobarListaAbierta(Posicion(sonda[0], sonda[1]-1, padre), *listaAbierta);

                if(comprobarLista.status)
                {
                    if(G(player, puntosG[0]) < listaAbierta->at(comprobarLista.indice).getG())
                    {
                        //para sustituir la posicion primero se borra y luego se inserta la nueva mas eficiente

                        listaAbierta->erase(listaAbierta->begin()+comprobarLista.indice);

                        Posicion aux = Posicion(sonda[0], sonda[1]-1, padre);
                        aux.setG(player, puntosG[0]);
                        aux.setH(heuristica(Posicion(sonda[0], sonda[1]-1, padre)));

                        listaAbierta->insert(listaAbierta->begin()+comprobarLista.indice, aux);

                    }
                }
                else
                {
                    Posicion aux = Posicion(sonda[0], sonda[1]-1, padre);
                    aux.setG(player, puntosG[0]);
                    aux.setH(heuristica(Posicion(sonda[0], sonda[1]-1, padre)));

                    salida.insert(salida.begin()+comprobarLista.indice, aux);

                }

            }
        }
    }


    // arriba derecha
    if(sonda[0]+1 < mapa.getAnchura() && sonda[0]-1 != -1)
    {
        // comprueba si se puede pasar o no
        if(paredes[sonda[0]+1][sonda[1]-1] != 0)    //IMPORTANTE--> != 0 si las paredes son 0; != 1 si las paredes son 1
        {
            // comprueba que no se encuentre en la lista cerrada
            if(comprobarListaCerrada(Posicion(sonda[0]+1, sonda[1]-1, padre), *listaCerrada))
            {
                /*
                Si ya esta en la lista abierta: comprobar si el camino es mas eficiente
                Si el camino es mas eficiente: cambiar el padre por el padre actual, de lo contrario no hacer nada
                Si no esta en la lista: calcular todo normalmente
                */

                comprobarLista = comprobarListaAbierta(Posicion(sonda[0]+1, sonda[1]-1, padre), *listaAbierta);

                if(comprobarLista.status)
                {
                    if(G(player, puntosG[1]) < listaAbierta->at(comprobarLista.indice).getG())
                    {
                        //para sustituir la posicion primero se borra y luego se inserta la nueva mas eficiente

                        listaAbierta->erase(listaAbierta->begin()+comprobarLista.indice);

                        Posicion aux = Posicion(sonda[0]+1, sonda[1]-1, padre);
                        aux.setG(player, puntosG[1]);
                        aux.setH(heuristica(Posicion(sonda[0]+1, sonda[1]-1, padre)));

                        listaAbierta->insert(listaAbierta->begin()+comprobarLista.indice, aux);

                    }
                }
                else
                {
                    Posicion aux = Posicion(sonda[0]+1, sonda[1]-1, padre);
                    aux.setG(player, puntosG[1]);
                    aux.setH(heuristica(Posicion(sonda[0]+1, sonda[1]-1, padre)));

                    salida.insert(salida.begin()+comprobarLista.indice, aux);

                }

            }
        }
    }

    // centro izquierda
    if(sonda[0]-1 != -1)
    {
        // comprueba si se puede pasar o no
        if(paredes[sonda[0]-1][sonda[1]] != 0)    //IMPORTANTE--> != 0 si las paredes son 0; != 1 si las paredes son 1
        {
            // comprueba que no se encuentre en la lista cerrada
            if(comprobarListaCerrada(Posicion(sonda[0]-1, sonda[1], padre), *listaCerrada))
            {
                /*
                Si ya esta en la lista abierta: comprobar si el camino es mas eficiente
                Si el camino es mas eficiente: cambiar el padre por el padre actual, de lo contrario no hacer nada
                Si no esta en la lista: calcular todo normalmente
                */

                comprobarLista = comprobarListaAbierta(Posicion(sonda[0]-1, sonda[1], padre), *listaAbierta);

                if(comprobarLista.status)
                {
                    if(G(player, puntosG[0]) < listaAbierta->at(comprobarLista.indice).getG())
                    {
                        //para sustituir la posicion primero se borra y luego se inserta la nueva mas eficiente

                        listaAbierta->erase(listaAbierta->begin()+comprobarLista.indice);

                        Posicion aux = Posicion(sonda[0]-1, sonda[1], padre);
                        aux.setG(player, puntosG[0]);
                        aux.setH(heuristica(Posicion(sonda[0]-1, sonda[1], padre)));

                        listaAbierta->insert(listaAbierta->begin()+comprobarLista.indice, aux);

                    }
                }
                else
                {
                    Posicion aux = Posicion(sonda[0]-1, sonda[1], padre);
                    aux.setG(player, puntosG[0]);
                    aux.setH(heuristica(Posicion(sonda[0]-1, sonda[1], padre)));

                    salida.insert(salida.begin()+comprobarLista.indice, aux);

                }

            }
        }
    }

    std::cout << "salida size: " << salida.size() << std::endl;

    // centro derecha
    if(sonda[0]+1 != -1)
    {
        //std::cout << "sonda X: " << sonda[0]+1 << std::endl << mapa.getAnchura() << std::endl;
        // comprueba si se puede pasar o no
        std::cout << "paredes: " << paredes[sonda[0]][sonda[1]] << std::endl;
        if(sonda[0]+1 < mapa.getAnchura() && paredes[sonda[0]+1][sonda[1]] != 0)    //IMPORTANTE--> != 0 si las paredes son 0; != 1 si las paredes son 1
        {
            // comprueba que no se encuentre en la lista cerrada
            std::cout << "PADRE: " << padre.getX() << " --- " << padre.getY() << std::endl;
            if(comprobarListaCerrada(Posicion(sonda[0]+1, sonda[1], padre), *listaCerrada))
            {
                /*
                Si ya esta en la lista abierta: comprobar si el camino es mas eficiente
                Si el camino es mas eficiente: cambiar el padre por el padre actual, de lo contrario no hacer nada
                Si no esta en la lista: calcular todo normalmente
                */

                comprobarLista = comprobarListaAbierta(Posicion(sonda[0]+1, sonda[1], padre), *listaAbierta);

                if(comprobarLista.status)
                {
                    if(G(player, puntosG[0]) < listaAbierta->at(comprobarLista.indice).getG())
                    {
                        //para sustituir la posicion primero se borra y luego se inserta la nueva mas eficiente

                        listaAbierta->erase(listaAbierta->begin()+comprobarLista.indice);

                        Posicion aux = Posicion(sonda[0]+1, sonda[1], padre);
                        aux.setG(player, puntosG[0]);
                        aux.setH(heuristica(Posicion(sonda[0]+1, sonda[1], padre)));

                        listaAbierta->insert(listaAbierta->begin()+comprobarLista.indice, aux);

                    }
                }
                else
                {
                    Posicion *aux = new Posicion(sonda[0]+1, sonda[1], padre);
                    aux->setG(player, puntosG[0]);
                    aux->setH(heuristica(Posicion(sonda[0]+1, sonda[1], padre)));
                    std::cout << "indice lista 5: " << comprobarLista.indice << std::endl;
                    std::cout << "listaAb size 5: " << listaAbierta->size() << std::endl;
                    salida.insert(salida.begin()+comprobarLista.indice, *aux);
                    std::cout << "hemos llegado" << std::endl;
                }

            }
        }
    }

    // abajo izquierda
    if(sonda[0]-1 != -1 && sonda[1]+1 < mapa.getAltura())
    {
        // comprueba si se puede pasar o no
        if(paredes[sonda[0]-1][sonda[1]+1] != 0)    //IMPORTANTE--> != 0 si las paredes son 0; != 1 si las paredes son 1
        {
            // comprueba que no se encuentre en la lista cerrada
            if(comprobarListaCerrada(Posicion(sonda[0]-1, sonda[1]+1, padre), *listaCerrada))
            {
                /*
                Si ya esta en la lista abierta: comprobar si el camino es mas eficiente
                Si el camino es mas eficiente: cambiar el padre por el padre actual, de lo contrario no hacer nada
                Si no esta en la lista: calcular todo normalmente
                */

                comprobarLista = comprobarListaAbierta(Posicion(sonda[0]-1, sonda[1]+1, padre), *listaAbierta);

                if(comprobarLista.status)
                {
                    if(G(player, puntosG[1]) < listaAbierta->at(comprobarLista.indice).getG())
                    {
                        //para sustituir la posicion primero se borra y luego se inserta la nueva mas eficiente

                        listaAbierta->erase(listaAbierta->begin()+comprobarLista.indice);

                        Posicion aux = Posicion(sonda[0]-1, sonda[1]+1, padre);
                        aux.setG(player, puntosG[1]);
                        aux.setH(heuristica(Posicion(sonda[0]-1, sonda[1]+1, padre)));

                        listaAbierta->insert(listaAbierta->begin()+comprobarLista.indice, aux);

                    }
                }
                else
                {
                    Posicion aux = Posicion(sonda[0]-1, sonda[1]+1, padre);
                    aux.setG(player, puntosG[1]);
                    aux.setH(heuristica(Posicion(sonda[0]-1, sonda[1]+1, padre)));

                    salida.insert(salida.begin()+comprobarLista.indice, aux);

                }

            }
        }
    }

    // abajo centro
    if(sonda[1]+1 < mapa.getAltura())
    {
        // comprueba si se puede pasar o no
        if(paredes[sonda[0]][sonda[1]+1] != 0)    //IMPORTANTE--> != 0 si las paredes son 0; != 1 si las paredes son 1
        {
            // comprueba que no se encuentre en la lista cerrada
            if(comprobarListaCerrada(Posicion(sonda[0], sonda[1]+1, padre), *listaCerrada))
            {
                /*
                Si ya esta en la lista abierta: comprobar si el camino es mas eficiente
                Si el camino es mas eficiente: cambiar el padre por el padre actual, de lo contrario no hacer nada
                Si no esta en la lista: calcular todo normalmente
                */

                comprobarLista = comprobarListaAbierta(Posicion(sonda[0], sonda[1]+1, padre), *listaAbierta);

                if(comprobarLista.status)
                {
                    if(G(player, puntosG[0]) < listaAbierta->at(comprobarLista.indice).getG())
                    {
                        //para sustituir la posicion primero se borra y luego se inserta la nueva mas eficiente

                        listaAbierta->erase(listaAbierta->begin()+comprobarLista.indice);

                        Posicion aux = Posicion(sonda[0], sonda[1]+1, padre);
                        aux.setG(player, puntosG[0]);
                        aux.setH(heuristica(Posicion(sonda[0], sonda[1]+1, padre)));

                        listaAbierta->insert(listaAbierta->begin()+comprobarLista.indice, aux);

                    }
                }
                else
                {
                    Posicion aux = Posicion(sonda[0], sonda[1]+1, padre);
                    aux.setG(player, puntosG[0]);
                    aux.setH(heuristica(Posicion(sonda[0], sonda[1]+1, padre)));

                    salida.insert(salida.begin()+comprobarLista.indice, aux);

                }

            }
        }
    }

    // abajo derecha
    if(sonda[0]+1 < mapa.getAnchura() && sonda[1]+1 < mapa.getAltura())
    {
        // comprueba si se puede pasar o no
        if(paredes[sonda[0]+1][sonda[1]+1] != 0)    //IMPORTANTE--> != 0 si las paredes son 0; != 1 si las paredes son 1
        {
            // comprueba que no se encuentre en la lista cerrada
            if(comprobarListaCerrada(Posicion(sonda[0]+1, sonda[1]+1, padre), *listaCerrada))
            {
                /*
                Si ya esta en la lista abierta: comprobar si el camino es mas eficiente
                Si el camino es mas eficiente: cambiar el padre por el padre actual, de lo contrario no hacer nada
                Si no esta en la lista: calcular todo normalmente
                */

                comprobarLista = comprobarListaAbierta(Posicion(sonda[0]+1, sonda[1]+1, padre), *listaAbierta);

                if(comprobarLista.status)
                {
                    if(G(player, puntosG[1]) < listaAbierta->at(comprobarLista.indice).getG())
                    {
                        //para sustituir la posicion primero se borra y luego se inserta la nueva mas eficiente

                        listaAbierta->erase(listaAbierta->begin()+comprobarLista.indice);

                        Posicion aux = Posicion(sonda[0]+1, sonda[1]+1, padre);
                        aux.setG(player, puntosG[1]);
                        aux.setH(heuristica(Posicion(sonda[0]+1, sonda[1]+1, padre)));

                        listaAbierta->insert(listaAbierta->begin()+comprobarLista.indice, aux);

                    }
                }
                else
                {
                    Posicion aux = Posicion(sonda[0]+1, sonda[1]+1, padre);
                    aux.setG(player, puntosG[1]);
                    aux.setH(heuristica(Posicion(sonda[0]+1, sonda[1]+1, padre)));

                    std::cout << "indice lista 8: " << comprobarLista.indice << std::endl;
                    std::cout << "listaAb size 8: " << listaAbierta->size() << std::endl;
                    salida.insert(salida.begin()+comprobarLista.indice, aux);

                }

            }
        }
    }


    return salida;
}









