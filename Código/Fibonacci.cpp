/*
 * Fibonacci.cpp
 *
 *  Created on: 31 de out de 2016
 *      Author: administrador
 */
#include <cstdlib>
#include <iostream>
#include "Fibonacci.h"

using namespace std;

FibonacciNode::FibonacciNode( int vertice, int dist )
{
	rank = 0;
	mark = false;
	esquerdaPtr = NULL;
	direitaPtr = NULL;
	paiPtr = NULL;
	filhoPtr = NULL;
	idVertice = vertice;
	distancia = dist;
}


void FibonacciNode::adicionaFilho( FibonacciNode *nodo )
{
	if ( filhoPtr == NULL )
		filhoPtr = nodo;
	else
	{
		nodo->direitaPtr = filhoPtr;
		filhoPtr = nodo;
	}

	rank++;

}


/*const FibonacciNode*& FibonacciNode::getDireitaPtr() const {
	return direitaPtr;
}

void FibonacciNode::setDireitaPtr(const FibonacciNode*& direitaPtr) {
	this->direitaPtr = direitaPtr;
}

const FibonacciNode*& FibonacciNode::getEsquerdaPtr() const {
	return esquerdaPtr;
}

void FibonacciNode::setEsquerdaPtr(const FibonacciNode*& esquerdaPtr) {
	this->esquerdaPtr = esquerdaPtr;
}

const FibonacciNode*& FibonacciNode::getFilhoPtr() const {
	return filhoPtr;
}

void FibonacciNode::setFilhoPtr(const FibonacciNode*& filhoPtr) {
	this->filhoPtr = filhoPtr;
}*/

bool FibonacciNode::isMark() const {
	return mark;
}

void FibonacciNode::setMark(bool mark) {
	this->mark = mark;
}

/*const FibonacciNode*& FibonacciNode::getPaiPtr() const {
	return paiPtr;
}

void FibonacciNode::setPaiPtr(const FibonacciNode*& paiPtr) {
	this->paiPtr = paiPtr;
}*/

int FibonacciNode::getRank() const {
	return rank;
}

void FibonacciNode::setRank(int rank) {
	this->rank = rank;
}

// Definições HeapFibonacci

HeapFibonacci::HeapFibonacci()
{
	numeroNodos = 0;
	minRoot = NULL;
	ultimoListaCircular = NULL;
	primeiroListaCircular = NULL;
}

void HeapFibonacci::insertVertex( FibonacciNode *nodo )
{
	if ( ultimoListaCircular == NULL )
	{
		ultimoListaCircular = nodo;
		primeiroListaCircular = nodo;
		nodo->direitaPtr = nodo;
		nodo->esquerdaPtr = nodo;
	}
	else
	{
		nodo->direitaPtr = primeiroListaCircular;
		nodo->esquerdaPtr = ultimoListaCircular;

		ultimoListaCircular->direitaPtr = nodo;
		primeiroListaCircular->esquerdaPtr = nodo;
		ultimoListaCircular = nodo;
	}

	if ( minRoot == NULL || nodo->getDistancia() < minRoot->getDistancia() )
		minRoot = nodo;

	numeroNodos++;
}

FibonacciNode *HeapFibonacci::extractMin()
{
	FibonacciNode *nodo = minRoot;
	if ( nodo != NULL )
	{
		for ( FibonacciNode *it = nodo->filhoPtr; it != NULL; it = it->direitaPtr )
		{
			it->direitaPtr = primeiroListaCircular;
			it->esquerdaPtr = ultimoListaCircular;

			ultimoListaCircular->direitaPtr = it;
			primeiroListaCircular->esquerdaPtr = it;
			ultimoListaCircular = it;

			it->paiPtr = NULL;
		}

		nodo->direitaPtr->esquerdaPtr = nodo->esquerdaPtr;
		nodo->esquerdaPtr->direitaPtr = nodo->direitaPtr;
		if ( primeiroListaCircular == nodo )
			primeiroListaCircular = nodo->direitaPtr;
		if ( ultimoListaCircular == nodo )
			ultimoListaCircular = nodo->esquerdaPtr;


		if ( nodo->direitaPtr == nodo )
			minRoot = NULL;
		else
		{
			minRoot = nodo->direitaPtr;
			consolidate();
		}
		numeroNodos--;
	}



	return nodo;
}

void swapFibonacciNodes( FibonacciNode **n1, FibonacciNode **n2  )
{
	FibonacciNode *temp = (*n1);
	*n1 = *n2;
	*n2 = temp;
}

void HeapFibonacci::heapLink( FibonacciNode *y, FibonacciNode *x )
{
	y->direitaPtr->esquerdaPtr = y->esquerdaPtr;
	y->esquerdaPtr->direitaPtr = y->direitaPtr;
	if ( primeiroListaCircular == y )
		primeiroListaCircular = y->direitaPtr;
	if ( ultimoListaCircular == y )
		ultimoListaCircular = y->esquerdaPtr;


	x->adicionaFilho( y );
	y->mark = false;

}

void HeapFibonacci::consolidate()
{
	// Mudar aqui depois
	FibonacciNode **vetorAuxiliar = (FibonacciNode **)malloc(sizeof(FibonacciNode *) * 100 );
	if ( vetorAuxiliar == NULL )
	{
		cerr << "Não foi possível alocar o vetor auxiliar na Heap de Fibonnaci. Encerrando o programa" << endl;
		exit( 1 );
	}

	for ( int i = 0; i < 100; i++ )
		vetorAuxiliar[ i ] = NULL;

	FibonacciNode *it = primeiroListaCircular;
	do
	{
		FibonacciNode *x = it;
		int d = x->getRank();
		while ( vetorAuxiliar[ d ] != NULL )
		{
			FibonacciNode *y = vetorAuxiliar[ d ];
			if ( x->getDistancia() > y->getDistancia() )
				swapFibonacciNodes( &x, &y );
			heapLink( y, x );
			vetorAuxiliar[ d ] = NULL;
			d = d + 1;
		}
		vetorAuxiliar[ d ] = x;

		it = it->direitaPtr;

	} while ( it != primeiroListaCircular );

	minRoot = NULL;
	for ( int i = 0; i < 100; i++ )
	{
		if ( vetorAuxiliar[ i ] != NULL )
		{
			vetorAuxiliar[ i ]->esquerdaPtr = ultimoListaCircular;
			vetorAuxiliar[ i ]->direitaPtr = primeiroListaCircular;

			ultimoListaCircular->direitaPtr = vetorAuxiliar[ i ];
			primeiroListaCircular->esquerdaPtr = vetorAuxiliar[ i ];

			ultimoListaCircular = vetorAuxiliar[ i ];
			if ( minRoot == NULL || vetorAuxiliar[ i ]->getDistancia() < minRoot->getDistancia() )
				minRoot = vetorAuxiliar[ i ];


		}
	}

}

int FibonacciNode::getDistancia() const {
return distancia;
}

void FibonacciNode::setDistancia(int distancia) {
this->distancia = distancia;
}

int FibonacciNode::getIdVertice() const {
return idVertice;
}

void FibonacciNode::setIdVertice(int idVertice) {
this->idVertice = idVertice;
}
