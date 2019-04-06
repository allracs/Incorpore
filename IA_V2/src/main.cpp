#include <iostream>
#include <stdlib.h>
#include <vector>
#include "Posicion.h"
#include "Mapa.h"
#include "Astar.h"

int main()
{
    std::cout << "creando mapa" << std::endl;
    Mapa *m = new Mapa(9,10);
    std::cout << "mapa creado" << std::endl;

    std::cout << "creando ia" << std::endl;
    Astar *ia = new Astar(Posicion(0,0), Posicion(0,2), *m);
    std::cout << "ia creada" << std::endl;

    std::cout << "mapeando" << std::endl;
    std::vector<Posicion> path = ia->mapear();
    std::cout << "mapedao hecho" << std::endl;


    delete m;
    exit(0);
}
