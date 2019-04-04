#include "Posicion.h"
#include <iostream>

Posicion::Posicion(int n, int m, Posicion p) // n
{
    //ctor
    x = n;
    y = m;
    *padre = p;
    *g = -1;
    *h = -1;
}

Posicion::~Posicion()
{
    //dtor
    delete g;
    delete h;
    delete padre;
}

void Posicion::setG(Posicion p, int valor)  // p: posicion padre; valor: coste de desplazamiento
{
    Posicion player = p;
    int salida = 0;
    if(player.getG() != -1)
    {
        salida = player.getG() + valor;
    }
    else
    {
        salida = valor;
    }
    *g = salida;
}

int Posicion::getG()
{
    return *g;
}

void Posicion::setH(Posicion i, Posicion f)  //p: posicion inicial; f: posicion final
{
    int ax, ay, fx, fy;
    ax = i.getX();
    ay = i.getY();
    fx = f.getX();
    fy = f.getY();
    *h = (abs(ax - fx)) + (abs(ay - fy));
}

int Posicion::getH()
{
    return *h;
}

int Posicion::getF()
{
    return *g + *h;
}

int Posicion::getX()
{
    return x;
}

int Posicion::getY()
{
    return y;
}

Posicion Posicion::getPadre()
{
    return *padre;
}
