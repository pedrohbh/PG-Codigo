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
	nodo->direitaPtr = NULL;
	nodo->esquerdaPtr = NULL;
	nodo->paiPtr = this;

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
		while ( nodo->filhoPtr != NULL )
		{
			FibonacciNode *it = nodo->filhoPtr;
			nodo->filhoPtr = nodo->filhoPtr->direitaPtr;
			it->paiPtr = NULL;
			insereVerticineListaPricipal( it );
		}

		remoreVerticeNaListaPrincipal( nodo );

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
	remoreVerticeNaListaPrincipal( y );
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

		if ( it->paiPtr != NULL )
			it = it->paiPtr;

		it = it->direitaPtr;

	} while ( it != primeiroListaCircular );

	minRoot = NULL;
	for ( int i = 0; i < 100; i++ )
	{
		if ( vetorAuxiliar[ i ] != NULL )
		{
			//insereVerticineListaPricipal( vetorAuxiliar[ i ] );

			if ( minRoot == NULL || vetorAuxiliar[ i ]->getDistancia() < minRoot->getDistancia() )
				minRoot = vetorAuxiliar[ i ];
		}
	}

	free( vetorAuxiliar );

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


void HeapFibonacci::imprimeHeapFibonacci()
{
	FibonacciNode *it = primeiroListaCircular;
	do
	{
		cout << "Nodo: " << it->distancia << " Filhos: ";
		for ( FibonacciNode *itFilhos = it->filhoPtr; itFilhos != NULL; itFilhos = itFilhos->direitaPtr )
		{
			if ( itFilhos == NULL )
				cout << "Null" << endl;
			cout << itFilhos->distancia << " -> ";
		}

		cout << endl;

		it = it->direitaPtr;



	} while ( it != primeiroListaCircular );
}

void HeapFibonacci::insereVerticineListaPricipal( FibonacciNode *novoNodo )
{
	if ( ultimoListaCircular == NULL )
	{
		ultimoListaCircular = novoNodo;
		primeiroListaCircular = novoNodo;
		novoNodo->direitaPtr = novoNodo;
		novoNodo->esquerdaPtr = novoNodo;
	}
	else
	{
		novoNodo->direitaPtr = primeiroListaCircular;
		novoNodo->esquerdaPtr = ultimoListaCircular;

		ultimoListaCircular->direitaPtr = novoNodo;
		primeiroListaCircular->esquerdaPtr = novoNodo;
		ultimoListaCircular = novoNodo;
	}
}


void HeapFibonacci::remoreVerticeNaListaPrincipal( FibonacciNode *nodo )
{
	if ( primeiroListaCircular == nodo && ultimoListaCircular == nodo )
	{
		primeiroListaCircular = NULL;
		ultimoListaCircular = NULL;
	}
	else
	{
		nodo->esquerdaPtr->direitaPtr = nodo->direitaPtr;
		nodo->direitaPtr->esquerdaPtr = nodo->esquerdaPtr;

		if ( nodo == ultimoListaCircular )
			ultimoListaCircular = nodo->esquerdaPtr;
		if ( nodo == primeiroListaCircular )
			primeiroListaCircular = nodo->direitaPtr;
	}

}
