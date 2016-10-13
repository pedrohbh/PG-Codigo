/*
 * Grafo.h
 *
 *  Created on: 14 de jul de 2016
 *      Author: administrador
 */

#ifndef GRAFO_H
#define GRAFO_H

#include <list>
using namespace std;

struct Aresta
{
	unsigned int idVertice1;
	unsigned int idVertice2;
	long int pesoAresta;
	list<Aresta> verticesAdjacentes;
};

class Grafo
{
public:
	// Funções de Criação do grafo
	Grafo();
	void leArquivoDeEntrada( const char *nome );

	void buscaEmProfundidade();
	void buscaEmLargura();
	void dijkstraCanonico( unsigned int origem, unsigned int destino );
	void dijkstraHeapBinario(unsigned int origem, unsigned int destino );

	// Getters and Setters
	unsigned int getNumeroArestas() const;
	void setNumeroArestas(unsigned int numeroArestas);
	unsigned int getNumeroVertices() const;
	void setNumeroVertices(unsigned int numeroVertices);

	// Funções de depuração
	void imprimeGrafo() const;


private:
	unsigned int numeroVertices;
	unsigned int numeroArestas;
	Aresta *verticesGrafos;

	void criaVertice( unsigned int idVert1, unsigned int idVert2, long int peso );
	void DSF( unsigned int v, unsigned int *lista, list<Aresta> &a, unsigned int *i );

};

#endif /* GRAFO_H_ */
