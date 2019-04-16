#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <math.h>
#include "../include/Astar.h"
#include "../include/Posicion.h"

Astar::Astar(Posicion i, Posicion f, bool** mapa, int n, int m)
{
    //ctor
    ////std::cout << "creando ia (constr)" << std::endl;
    m_alt = n;
    m_anc = m;

    mapaArr = new bool *[n];
	for(int a = 0; a < n; a++){
        mapaArr[a] = new bool[m];
	}

    for(int a = 0; a < n; a++)
    {
        for(int b = 0; b < m; b++)
        {
            mapaArr[a][b] = mapa[a][b];
        }
    }

    listaAbierta = new std::vector<Posicion>;
    listaCerrada = new std::vector<Posicion>;
    vecinos = new std::vector<Posicion>;

    if(listaCerrada->size() == 0)
        listaCerrada->insert(listaCerrada->begin(),i);

    //////std::cout << "Lista Cerrada size: " << listaCerrada->size() << std::endl;
    //////std::cout << "Lista Abierta size: " << listaAbierta->size() << std::endl;

    ini = new Posicion(i.getX(), i.getY());
    fin = new Posicion(f.getX(), f.getY());
    ////std::cout << ini->getX() << " --- " << ini->getY() << std::endl;
    //////std::cout << "fin creando ia (constr)" << std::endl << "-------------" << std::endl;
}

Astar::~Astar()
{
    //dtor
    listaAbierta->clear();
    listaCerrada->clear();
    vecinos->clear();
    delete listaAbierta;
    delete listaCerrada;
    delete vecinos;
    delete ini, fin;
	for(int a = 0; a < m_alt; a++){
        delete mapaArr[a];
	}
    delete mapaArr;
}

std::vector<Posicion> Astar::mapear()
{
    std::vector<Posicion> salidaFinal;
    int indiceIni = 0;
    bool rutaEncontrada = false;
    int contador = 1;
    bool flag=true;
    int anterior = listaAbierta->size();

    while(!rutaEncontrada)
    {
        //////std::cout << "¿RUTA ENCONTRADA inicio? " << rutaEncontrada << std::endl;
        //////std::cout << "antes de comprobar: " << mapa->getMapa()[0][0] << std::endl;
        vecinos->clear();
        //listaAbierta->clear();
        //////std::cout << listaAbierta->size() << " /// " << vecinos->size() << std::endl;
        *vecinos = comprobarVecinos(*ini);
       // ////std::cout << "vecinos comprobados " << listaAbierta->size() << std::endl;
        listaAbierta->insert(listaAbierta->begin(), vecinos->begin(), vecinos->end());



        if(anterior==listaAbierta->size()){
            ////std::cout << "Vecinos es cero" << std::endl;
            flag=false;
            break;
        }



        indiceIni = obtenerMenorF();
        ////std::cout << "indiceIni: " << indiceIni << std::endl;
        *ini = listaAbierta->at(indiceIni);
        removerLista(indiceIni);
        rutaEncontrada = finalizarLogica(*listaCerrada);
        ////std::cout << "¿RUTA ENCONTRADA? " << rutaEncontrada << std::endl;
        ////std::cout << "RUTA ENCONTRADA CONTADOR: " << contador << std::endl;
        contador++;
    }
    if(flag){

    ////std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl << "SE VIENE EL REVERSE" << std::endl;
    std::reverse(listaCerrada->begin(), listaCerrada->end());
    ////std::cout << "REVERSE EL VIENE SE " << listaCerrada->size() << std::endl;

    //-------------------------------------------------------------------------

    Posicion direccionDePadres = listaCerrada->at(0).getPadre();

    salidaFinal.insert(salidaFinal.begin(), direccionDePadres);
    //////std::cout << listaCerrada->at(0).getPadre().getPadre().getX() << " --- " << listaCerrada->at(0).getPadre().getPadre().getY() << std::endl << std::endl;
    ////std::cout << listaCerrada->at(0).getX() << " --- " << listaCerrada->at(0).getY() << std::endl << std::endl;

    for(int i = 1; i < listaCerrada->size()-1; i++)
    {
        ////std::cout <<"//POSICION: "<< listaCerrada->at(i).getY() << " --- " << listaCerrada->at(i).getX() << std::endl;
        ////std::cout <<"// PADRE: " << listaCerrada->at(i-1).getPadre().getY()<< " - " << listaCerrada->at(i-1).getPadre().getX()<< std::endl;
        //////std::cout << direccionDePadres.getPadre().getX() << " --- " << direccionDePadres.getPadre().getY() << std::endl << std::endl;

        ////std::cout << "Padre existe:" << std::endl;
        if(listaCerrada->at(i).getX() == direccionDePadres.getX() && listaCerrada->at(i).getY() == direccionDePadres.getY())
        {
            ////std::cout << "ENTRO EN EL BUCLE LOCO: " << i << std::endl;
            ////std::cout <<"Posicion Final: " << fin->getX() << " - " << fin->getY() << std::endl;
            ////std::cout <<"Posicion que entra: " << listaCerrada->at(i).getY() << " - " << listaCerrada->at(i).getX() << std::endl;

                salidaFinal.insert(salidaFinal.end(),listaCerrada->at(i).getPadre());
                direccionDePadres = listaCerrada->at(i).getPadre();

               // ////std::cout<< "estoy en la posicion final" << std::endl;

        }
    }

    //-------------------------------------------------------------------------

    ////std::cout << "///////////////SALIDA FINALISIMA/////////////////" << std::endl;


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
        if(listaAbierta->size() > 0)
        {
            for(int i = 1; i < listaAbierta->size(); i++)
            {
                if(listaAbierta->at(i).getF() < menor)
                {
                    menor = listaAbierta->at(i).getF();
                    indiceMenor = i;
                }
            }
        }
    }
    return indiceMenor;
}

void Astar::removerLista(int indicePadre)
{
    listaCerrada->push_back(listaAbierta->at(indicePadre));
    ////std::cout << "SE METE EN LISTA CERRADA: " <<std::endl;
    for(int a = 0; a < listaCerrada->size(); a++)
    {
        ////std::cout << listaCerrada->at(a).getY() << " --- " << listaCerrada->at(a).getX()<< std::endl;
        //////std::cout <<" // PADRE: " << listaCerrada->at(a).getPadre().getY()<< " - " << listaCerrada->at(a).getPadre().getX()<< std::endl;
    }
    listaAbierta->erase(listaAbierta->begin()+indicePadre);
}

bool Astar::finalizarLogica(std::vector<Posicion> &listaCerr)
{
    bool res = false;
    //////std::cout <<" posicion final: "<< fin->getX() << " - " << fin->getY() <<std::endl;


    for(int i = 0; i < listaCerr.size(); ++i)
    {
        //////std::cout <<" posiciones buscadas: "<<listaCerr.at(i).getX() << " - " << listaCerr.at(i).getY() <<std::endl;
        if(listaCerr.at(i).getX() == fin->getX() && listaCerr.at(i).getY() == fin->getY())
        {
            res = true;
            break;
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
    res.status = false;
    res.indice = 0;
    if(listaAbi.size() >= 1)
    {
        ////std::cout << "Lista Abierta size: " << listaAbi.size() << std::endl;
        for(int i = 0; i < listaAbi.size(); i++)
        {
            if(listaAbi.at(i).getX() == caja.getX() && listaAbi.at(i).getY() == caja.getY())
            {
                res.status = true;
                res.indice = i;
                //////std::cout << "RES INDICE: " << res.indice << std::endl;
                break;
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
    int h = (abs(inicio.getX() - fin->getX())) + (abs(inicio.getY() - fin->getY()));
    ////std::cout << "HEURISTICA: " << h << std::endl;
    ////std::cout << inicio.getX() << " --- " << inicio.getY() << std::endl;
    ////std::cout << fin->getY() << " --- " << fin->getX() << std::endl;
    return h * 10;
}

std::vector<Posicion> Astar::comprobarVecinos(Posicion padre)
{
    std::vector<Posicion> salida;
    ////std::cout << "EMPIEZA COMPROBAR VECINOS - SALIDA SIZE: " << salida.size() << std::endl;
    Posicion player = padre;    //sera el ultimo en la lista abierta
    int puntosG[2] = {10, 10};
    int sonda[2] = {padre.getX(),padre.getY()};
    int pared = 1;
    comprobarListaAb comprobarLista;
    ////std::cout << "ACTUAL: " << padre.getX() << " --- " << padre.getY() << " --- " << mapaArr[padre.getY()][padre.getX()] << std::endl;
    /*
    for(int a = 0; a < m_alt; a++)
    {
        for(int b = 0; b < m_anc; b++)
        {

            ////std::cout << mapaArr[a][b];
        }
        ////std::cout << std::endl;
    }
    ////std::cout << "pos 0-0: " << mapaArr[0][0] << std::endl;
    ////std::cout << "pos 0-1: " << mapaArr[0][1] << std::endl;
    ////std::cout << "pos 1-0: " << mapaArr[1][0] << std::endl;
    ////std::cout << "pos 8-9: " << mapaArr[m_alt-1][m_anc-1] << std::endl;
    for(int k = 0; k < 9; k++)
    {
        ////std::cout << mapaArr[k][0];
    }
    ////std::cout << std::endl;
    */
    /*
    ////std::cout << "::EL VEÏNS MEUS::" << std::endl;

    if(sonda[0]-1 >= 0 && sonda[1]-1 >= 0)
        ////std::cout << mapaArr[sonda[0]-1][sonda[1]-1];
    if(sonda[1]-1 >= 0)
        ////std::cout << mapaArr[sonda[0]][sonda[1]-1];
    if(sonda[1]-1 >= 0)
        ////std::cout << mapaArr[sonda[0]+1][sonda[1]-1] << std::endl;
    if(sonda[0]-1 >= 0)
        ////std::cout << mapaArr[sonda[0]-1][sonda[1]];
    ////std::cout << mapaArr[sonda[0]][sonda[1]];
    ////std::cout << mapaArr[sonda[0]+1][sonda[1]] << std::endl;
    if(sonda[0]-1 >= 0)
        ////std::cout << mapaArr[sonda[0]-1][sonda[1]+1];
    ////std::cout << mapaArr[sonda[0]][sonda[1]+1];
    ////std::cout << mapaArr[sonda[0]+1][sonda[1]+1] << std::endl;


    ////std::cout << "---------------------------" << std::endl;
    */


    //faltan agregar a los que estan en la lista blanca
    ////std::cout << "=== arriba izquierda ===" << std::endl;
    ////std::cout << sonda[0]-1 << " - " << sonda[1]-1 << std::endl;
    // arriba izquierda
    if(sonda[0]-1 > -1 && sonda[1]-1 > -1)
    {
        // comprueba si se puede pasar o no
        if(mapaArr[sonda[1]-1][sonda[0]-1] != pared && mapaArr[sonda[1]][sonda[0]-1] != pared && mapaArr[sonda[1]-1][sonda[0]] != pared)    //IMPORTANTE--> != 0 si las mapaArr son 0; != 1 si las mapaArr son 1
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
                        ////std::cout << "SE ANYADE A LISTA ABIERTA 1: " << aux.getX() << " --- " << aux.getY() << std::endl;
                        listaAbierta->insert(listaAbierta->begin()+comprobarLista.indice, aux);

                    }
                }
                else
                {
                    Posicion aux = Posicion(sonda[0]-1, sonda[1]-1, padre);
                    aux.setG(player, puntosG[1]);
                    aux.setH(heuristica(Posicion(sonda[0]-1, sonda[1]-1, padre)));

                    ////std::cout << "indice lista 1: " << comprobarLista.indice << std::endl;
                    ////std::cout << "listaAb size 1: " << listaAbierta->size() << std::endl;
                    salida.insert(salida.begin()+comprobarLista.indice, aux);

                }

            }
        }
    }

    ////std::cout << "=== arriba centro ===" << std::endl;
    ////std::cout << sonda[0] << " - " << sonda[1]-1 << std::endl;
    // arriba centro
    if(sonda[1]-1 > -1)
    {
        // comprueba si se puede pasar o no
        if(mapaArr[sonda[1]-1][sonda[0]]!= pared)    //IMPORTANTE--> != 0 si las mapaArr son 0; != 1 si las mapaArr son 1
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
                        ////std::cout << "SE ANYADE A LISTA ABIERTA 2: " << aux.getX() << " --- " << aux.getY() << std::endl;
                        listaAbierta->insert(listaAbierta->begin()+comprobarLista.indice, aux);

                    }
                }
                else
                {
                    Posicion aux = Posicion(sonda[0], sonda[1]-1, padre);
                    aux.setG(player, puntosG[0]);
                    aux.setH(heuristica(Posicion(sonda[0], sonda[1]-1, padre)));

                    ////std::cout << "indice lista 2: " << comprobarLista.indice << std::endl;
                    ////std::cout << "listaAb size 2: " << listaAbierta->size() << std::endl;
                    salida.insert(salida.begin()+comprobarLista.indice, aux);

                }

            }
        }
    }

    ////std::cout << "=== arriba derecha ===" << std::endl;
    ////std::cout << sonda[0]+1 << " - " << sonda[1]-1 << std::endl;
    // arriba derecha
    if(sonda[0]+1 < m_anc && sonda[1]-1 >-1)
    {
        // comprueba si se puede pasar o no
        if(mapaArr[sonda[1]-1][sonda[0]+1] != pared && mapaArr[sonda[1]][sonda[0]+1] != pared && mapaArr[sonda[1]-1][sonda[0]] != pared)    //IMPORTANTE--> != 0 si las mapaArr son 0; != 1 si las mapaArr son 1
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

                if(comprobarLista.status)       // si esta en la lista o no
                {
                    if(G(player, puntosG[1]) < listaAbierta->at(comprobarLista.indice).getG())
                    {
                        //para sustituir la posicion primero se borra y luego se inserta la nueva mas eficiente

                        listaAbierta->erase(listaAbierta->begin()+comprobarLista.indice);

                        Posicion aux = Posicion(sonda[0]+1, sonda[1]-1, padre);
                        aux.setG(player, puntosG[1]);
                        aux.setH(heuristica(Posicion(sonda[0]+1, sonda[1]-1, padre)));
                        ////std::cout << "SE ANYADE A LISTA ABIERTA 3: " << aux.getX() << " --- " << aux.getY() << std::endl;
                        listaAbierta->insert(listaAbierta->begin()+comprobarLista.indice, aux);

                    }
                }
                else
                {
                    Posicion aux = Posicion(sonda[0]+1, sonda[1]-1, padre);
                    aux.setG(player, puntosG[1]);
                    aux.setH(heuristica(Posicion(sonda[0]+1, sonda[1]-1, padre)));

                    ////std::cout << "indice lista 3: " << comprobarLista.indice << std::endl;
                    ////std::cout << "listaAb size 3: " << listaAbierta->size() << std::endl;
                    salida.insert(salida.begin()+comprobarLista.indice, aux);

                }

            }
        }
    }

    ////std::cout << "=== centro izquierda ===" << std::endl;
    ////std::cout << sonda[0]-1 << " - " << sonda[1] << std::endl;
    // centro izquierda
    if(sonda[0]-1 > -1)
    {
        // comprueba si se puede pasar o no

        ////std::cout << "mapaArr: " << mapaArr[sonda[1]][sonda[0]-1] << std::endl;

        if(mapaArr[sonda[1]][sonda[0]-1] != pared)    //IMPORTANTE--> != 0 si las mapaArr son 0; != 1 si las mapaArr son 1
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
                        ////std::cout << "SE ANYADE A LISTA ABIERTA 4: " << aux.getX() << " --- " << aux.getY() << std::endl;
                        listaAbierta->insert(listaAbierta->begin()+comprobarLista.indice, aux);

                    }
                }
                else
                {
                    Posicion aux = Posicion(sonda[0]-1, sonda[1], padre);
                    aux.setG(player, puntosG[0]);
                    aux.setH(heuristica(Posicion(sonda[0]-1, sonda[1], padre)));

                    ////std::cout << "indice lista 4: " << comprobarLista.indice << std::endl;
                    ////std::cout << "listaAb size 4: " << listaAbierta->size() << std::endl;
                    salida.insert(salida.begin()+comprobarLista.indice, aux);

                }

            }
        }
    }

    //////std::cout << "salida size despues de 3: " << salida.size() << std::endl;

    ////std::cout << "=== centro derecha ===" << std::endl;
    ////std::cout << sonda[0]+1 << " - " << sonda[1] << std::endl;
    // centro derecha
    if(sonda[0]+1 < m_anc)
    {
        //////std::cout << "sonda X: " << sonda[0]+1 << std::endl << m_anc << std::endl;
        // comprueba si se puede pasar o no
        //////std::cout << "mapaArr: " << mapaArr[sonda[0]+1][sonda[1]] << std::endl;
        //////std::cout << sonda[0]+1 << " - " << sonda[1] << std::endl;
        if(mapaArr[sonda[1]][sonda[0]+1] != pared)    //IMPORTANTE--> != 0 si las mapaArr son 0; != 1 si las mapaArr son 1
        {
            // comprueba que no se encuentre en la lista cerrada
            if(comprobarListaCerrada(Posicion(sonda[0]+1, sonda[1], padre), *listaCerrada))
            {
                /*
                Si ya esta en la lista abierta: comprobar si el camino es mas eficiente
                Si el camino es mas eficiente: cambiar el padre por el padre actual, de lo contrario no hacer nada
                Si no esta en la lista: calcular todo normalmente
                */
                comprobarLista = comprobarListaAbierta(Posicion(sonda[0]+1, sonda[1], padre), *listaAbierta);
                //////std::cout << "=== comprobando lista === " << comprobarLista.status << " || " << comprobarLista.indice << std::endl;

                if(comprobarLista.status)
                {
                    if(G(player, puntosG[0]) < listaAbierta->at(comprobarLista.indice).getG())
                    {
                        //para sustituir la posicion primero se borra y luego se inserta la nueva mas eficiente

                        listaAbierta->erase(listaAbierta->begin()+comprobarLista.indice);

                        Posicion aux = Posicion(sonda[0]+1, sonda[1], padre);
                        aux.setG(player, puntosG[0]);
                        aux.setH(heuristica(Posicion(sonda[0]+1, sonda[1], padre)));
                        ////std::cout << "SE ANYADE A LISTA ABIERTA 5: " << aux.getX() << " --- " << aux.getY() << std::endl;
                        listaAbierta->insert(listaAbierta->begin()+comprobarLista.indice, aux);

                    }
                }
                else
                {
                    Posicion aux = Posicion(sonda[0]+1, sonda[1], padre);
                    aux.setG(player, puntosG[0]);
                    aux.setH(heuristica(Posicion(sonda[0]+1, sonda[1], padre)));

                    ////std::cout << "indice lista 5: " << comprobarLista.indice << std::endl;
                    ////std::cout << "listaAb size 5: " << listaAbierta->size() << std::endl;
                    salida.insert(salida.begin()+comprobarLista.indice, aux);
                }

            }
        }
    }

    ////std::cout << "=== abajo izquierda ===" << std::endl;
    ////std::cout << sonda[0]-1 << " - " << sonda[1]+1 << std::endl;
    // abajo izquierda
    if(sonda[0]-1 > -1 && sonda[1]+1 < m_alt)
    {
        // comprueba si se puede pasar o no
        if(mapaArr[sonda[1]+1][sonda[0]-1] != pared && mapaArr[sonda[1]][sonda[0]-1] != pared && mapaArr[sonda[1]+1][sonda[0]] != pared)    //IMPORTANTE--> != 0 si las mapaArr son 0; != 1 si las mapaArr son 1
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
                        ////std::cout << "SE ANYADE A LISTA ABIERTA 6: " << aux.getX() << " --- " << aux.getY() << std::endl;
                        listaAbierta->insert(listaAbierta->begin()+comprobarLista.indice, aux);

                    }
                }
                else
                {
                    Posicion aux = Posicion(sonda[0]-1, sonda[1]+1, padre);
                    aux.setG(player, puntosG[1]);
                    aux.setH(heuristica(Posicion(sonda[0]-1, sonda[1]+1, padre)));
                    ////std::cout << aux.getH() << std::endl;
                    ////std::cout << "indice lista 6: " << comprobarLista.indice << std::endl;
                    ////std::cout << "listaAb size 6: " << listaAbierta->size() << std::endl;
                    salida.insert(salida.begin()+comprobarLista.indice, aux);

                }

            }
        }
    }

    ////std::cout << "=== abajo centro ===" << std::endl;
    ////std::cout << sonda[0] << " - " << sonda[1]+1 << std::endl;
    // abajo centro
    if(sonda[1]+1 < m_alt)
    {
        // comprueba si se puede pasar o no
        if(mapaArr[sonda[1]+1][sonda[0]] != pared)    //IMPORTANTE--> != 0 si las mapaArr son 0; != 1 si las mapaArr son 1
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
                        ////std::cout << "SE ANYADE A LISTA ABIERTA 7: " << aux.getX() << " --- " << aux.getY() << std::endl;
                        listaAbierta->insert(listaAbierta->begin()+comprobarLista.indice, aux);

                    }
                }
                else
                {
                    Posicion aux = Posicion(sonda[0], sonda[1]+1, padre);
                    aux.setG(player, puntosG[0]);
                    aux.setH(heuristica(Posicion(sonda[0], sonda[1]+1, padre)));

                    ////std::cout << "indice lista 7: " << comprobarLista.indice << std::endl;
                    ////std::cout << "listaAb size 7: " << listaAbierta->size() << std::endl;
                    salida.insert(salida.begin()+comprobarLista.indice, aux);

                }

            }
        }
    }

    ////std::cout << "=== abajo derecha ===" << std::endl;
    ////std::cout << sonda[0]+1 << " - " << sonda[1]+1 << std::endl;
    // abajo derecha
    if(sonda[0]+1 < m_anc && sonda[1]+1 < m_alt)
    {
        // comprueba si se puede pasar o no
        if(mapaArr[sonda[1]+1][sonda[0]+1] != pared && mapaArr[sonda[1]][sonda[0]+1] != pared && mapaArr[sonda[1]+1][sonda[0]] != pared)    //IMPORTANTE--> != 0 si las mapaArr son 0; != 1 si las mapaArr son 1
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
                        ////std::cout << "SE ANYADE A LISTA ABIERTA 8: " << aux.getX() << " --- " << aux.getY() << std::endl;
                        listaAbierta->insert(listaAbierta->begin()+comprobarLista.indice, aux);

                    }
                }
                else
                {
                    Posicion aux = Posicion(sonda[0]+1, sonda[1]+1, padre);
                    aux.setG(player, puntosG[1]);
                    aux.setH(heuristica(Posicion(sonda[0]+1, sonda[1]+1, padre)));

                    ////std::cout << "indice lista 8: " << comprobarLista.indice << std::endl;
                    ////std::cout << "listaAb size 8: " << listaAbierta->size() << std::endl;
                    salida.insert(salida.begin()+comprobarLista.indice, aux);

                }

            }
        }
    }

    ////std::cout << "SALIDA SIZE FIN: " << salida.size() << std::endl;

    for(int c = 0; c < salida.size(); c++)
    {
        ////std::cout << salida.at(c).getX() << " --- " << salida.at(c).getY() << std::endl;
    }

    ////std::cout << "..........." << std::endl;

    return salida;
}
