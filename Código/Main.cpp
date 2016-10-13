/*
 * Main.cpp
 *
 *  Created on: 14 de jul de 2016
 *      Author: administrador
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Grafo.h"
using namespace std;

int main( int argc, char *argv[] )
{
	Grafo g;
	int verticeOrigem;
	int verticeDestino;
	clock_t begin;
	clock_t end;
	double tempoDecorrido;
	string nomeEntrada;
	if ( argc < 2 )
	{
		nomeEntrada = "../Testes/teste.txt";
		verticeOrigem = 0;
		verticeDestino = 1;
	}
	else
	{
		nomeEntrada = argv[ 1 ];
		verticeOrigem = 0;
		verticeDestino = 1;
		if ( argc > 3 )
		{
			verticeOrigem = atoi( argv[ 3 ] );
			verticeDestino = atoi( argv[ 4 ] );
		}
	}
			
	
	g.leArquivoDeEntrada( nomeEntrada.c_str() );
	g.imprimeGrafo();
	g.dijkstraCanonico( 0, 3 );
	/*begin = clock();
	//g.buscaEmLargura();
	g.dijkstra( 0, 3 );
	//g.buscaEmProfundidade();
	end = clock();
	tempoDecorrido = (double)(end - begin) / CLOCKS_PER_SEC;
	cout << tempoDecorrido << endl;
	//g.buscaEmLargura();*/

	//cout << "Sobrevivi Final" << endl;
}

