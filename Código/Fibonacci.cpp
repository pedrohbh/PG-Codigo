/*
 * Fibonacci.cpp
 *
 *  Created on: 31 de out de 2016
 *      Author: administrador
 */
#include <cstdlib>
#include "Fibonacci.h"


FibonacciNode::FibonacciNode( int vertice, int dist )
{
	rank = 0;
	mark = false;
	esquerdaPtr = this;
	direitaPtr = this;
	paiPtr = NULL;
	filhoPtr = NULL;
	idVertice = vertice;
	distancia = dist;
}




const FibonacciNode*& FibonacciNode::getDireitaPtr() const {
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
}

bool FibonacciNode::isMark() const {
	return mark;
}

void FibonacciNode::setMark(bool mark) {
	this->mark = mark;
}

const FibonacciNode*& FibonacciNode::getPaiPtr() const {
	return paiPtr;
}

void FibonacciNode::setPaiPtr(const FibonacciNode*& paiPtr) {
	this->paiPtr = paiPtr;
}

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

		if ( nodo->direitaPtr == nodo )
			minRoot = NULL;
		else
		{
			minRoot = nodo->direitaPtr;
		}
	}



	return nodo;
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
