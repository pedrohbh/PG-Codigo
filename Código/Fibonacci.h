#ifndef FIBONACCI_H
#define FIBONACCI_H

#include "Grafo.h"

class FibonacciNode
{
public:
	FibonacciNode();
	
	bool adicionaFilho( FibonacciNode *node );
	bool adicionaIrmao( FibonacciNode *node );
	bool remove();

	// Variáveis
	FibonacciNode *esquerdaPtr;
	FibonacciNode *direiraPtr;
	FibonacciNode *paiPtr;
	FibonacciNode *filhoPtr;
	int idVertice;
	int distancia;
	int rank;
};


class HeapFibonacci
{
public:
	bool insereVertice( FibonacciNode *node );

private:
	FibonacciNode *minRoot;

};



#endif
