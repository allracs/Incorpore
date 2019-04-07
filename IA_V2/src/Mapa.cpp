#include <iostream>
#include <stdlib.h>
#include "Mapa.h"
//PROVISIONAL

Mapa::Mapa(int n, int mm)
{
    //ctor
    n = 9;
    mm = 10;

    m = new bool *[n];
	for(int a = 0; a < n; a++){
        m[a] = new bool[mm];
	}

    bool j[n][mm] =
	{
		{ 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
		{ 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
		{ 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
		{ 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
		{ 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
		{ 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
		{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
		{ 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
		{ 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 }
	};

	for(int a = 0; a < n; a++)
    {
        for(int b = 0; b < mm; b++)
        {
            m[a][b] = j[a][b];
            std::cout << m[a][b];
        }
        std::cout << std::endl;
    }

    altura = n;
    anchura = mm;
}

Mapa::~Mapa()
{
    //dtor
}

int Mapa::getAltura()
{
    return altura;
}

int Mapa::getAnchura()
{
    return anchura;
}

bool **Mapa::getMapa()
{
    return m;
}
