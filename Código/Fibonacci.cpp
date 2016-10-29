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

bool FibonacciNode::adicionaIrmao( Node *node )
{
	Node *temp = rightMostSibling();
	if ( temp == NULL )
		return false;
	
	temp->direitaPtr = node;
	node->esquerdaPtr = temp;
	node->paiPtr = this->paiPtr;
	node->direitaPtr = NULL;

	if ( paiPtr )
		paiPtr->rank++;
	
	return true;
}

bool FibonacciNode::remove()
{
	if ( paiPtr )
	{
		paiPtr->rank--;
		if ( esquerdaPtr )
			paiPtr->filhoPtr = esquerdaPtr;
		else if ( direitaPtr )
			paiPtr->filhoPtr = direitaPtr;
		else
			paiPtr->filhoPtr = NULL;
	}

	if ( esquerdaPtr )
		esquerdaPtr->direitaPtr = direitaPtr;
	if ( direitaPtr )
		direitaPtr->esquerdaPtr = esquerdaPtr;

	esquerdaPtr = NULL;
	direitaPtr = NULL;
	paiPtr = NULL;

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

void HeapFibonacci::decreaseKey( int delta, Node *vertice )
{
	vertice->distancia = delta;

	if ( vertice->paiPtr != NULL )
	{
		verticePtr->remove();
		minRoot->adicionaIrmao( vertice );
	}
	
	if ( vertice->distancia < minRoot->distancia )
		minRoot = vertice;
}

Node *HeapFibonacci::findMin()
{
	return minRoot;
}
