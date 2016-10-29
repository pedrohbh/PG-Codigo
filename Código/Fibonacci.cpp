#include "Fibonacci.h"

bool FibonacciNode::adicionaFilho( Node *node )
{
	if ( filhoPtr != NULL )
		filhoPtr->adicionaIrmao( node );
	else
	{
		filhoPtr = node;
		node->paiPtr = this;
		rank = 1;
	}

	return true;
}

bool HeapFibonacci::insereVertice( FibonacciNode *node )
{
	if ( node == NULL )
		return false;
	
	if ( minRoot == NULL )
		minRoot = node;
	
	else
	{
		mintRoot->adicionaIrmao( node );
		if ( minRoot->distancia > node->distancia )
			minRoot = node;
	}
	return true;
}
