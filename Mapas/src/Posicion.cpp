#include "../include/Posicion.h"
#include <iostream>
#include <stdlib.h>

Posicion::Posicion(int n, int m, Posicion p) // n
{
    //ctor
    x = n;
    y = m;
    //padre = new Posicion(p.getX(), p.getY());
    padre = new Posicion(p.getX(), p.getY());
    g = -1;
    h = -1;
    ////std::cout << "valor G: " << g << std::endl;
}
Posicion::Posicion(int n, int m) // n
{
    //ctor
    x = n;
    y = m;
}

Posicion::~Posicion()
{
    //dtor

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
    ////std::cout << "setG (pre): " << g << std::endl;
    g = salida;
    ////std::cout << "setG (post): " << g << std::endl;
}

void Posicion::copyGH(int gg, int hh)
{
    g = gg;
    h = hh;
}

int Posicion::getG()
{
    ////std::cout << "getG: " << g << std::endl;
    return g;
}

void Posicion::setH(Posicion i, Posicion f)  //p: posicion inicial; f: posicion final
{
    int ax, ay, fx, fy;
    ax = i.getX();
    ay = i.getY();
    fx = f.getX();
    fy = f.getY();
    h = (abs(ax - fx)) + (abs(ay - fy));
}

void Posicion::setH(int n)
{
    h = n;
}

int Posicion::getH()
{
    return h;
}

int Posicion::getF()
{
    return g + h;
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

