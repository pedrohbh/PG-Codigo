/*
 * Main.cpp
 *
 *  Created on: 14 de jul de 2016
 *      Author: administrador
 */

#include <iostream>
#include <ctime>
#include <string>
#include "Grafo.h"
using namespace std;

int main()
{
	Grafo g;
	clock_t begin;
	clock_t end;
	double tempoDecorrido;
	string nomeEntrada = "USA-road-d.NY.gr"; //"USA-road-d.NY.gr"; // = "USA-road-d.FLA.gr";
	g.leArquivoDeEntrada( nomeEntrada.c_str() );
	//g.imprimeGrafo();
	begin = clock();
	//g.buscaEmLargura();
	g.dijkstra( 0, 3 );
	//g.buscaEmProfundidade();
	end = clock();
	tempoDecorrido = (double)(end - begin) / CLOCKS_PER_SEC;
	cout << tempoDecorrido << endl;
	//g.buscaEmLargura();

	//cout << "Sobrevivi Final" << endl;
}

