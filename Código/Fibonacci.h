/*
 * Fibonacci.h
 *
 *  Created on: 31 de out de 2016
 *      Author: administrador
 */

#ifndef FIBONACCI_H
#define FIBONACCI_H

class FibonacciNode
{
public:
	FibonacciNode( int, int );




	// Getters and Setters
	const FibonacciNode*& getDireitaPtr() const;
	void setDireitaPtr(const FibonacciNode*& direitaPtr);
	const FibonacciNode*& getEsquerdaPtr() const;
	void setEsquerdaPtr(const FibonacciNode*& esquerdaPtr);
	const FibonacciNode*& getFilhoPtr() const;
	void setFilhoPtr(const FibonacciNode*& filhoPtr);
	bool isMark() const;
	void setMark(bool mark);
	const FibonacciNode*& getPaiPtr() const;
	void setPaiPtr(const FibonacciNode*& paiPtr);
	int getRank() const;
	void setRank(int rank);
	int getDistancia() const;
	void setDistancia(int distancia);
	int getIdVertice() const;
	void setIdVertice(int idVertice);

private:
	FibonacciNode *paiPtr;
	FibonacciNode *filhoPtr;
	FibonacciNode *esquerdaPtr;
	FibonacciNode *direitaPtr;
	int rank;
	bool mark;
	int idVertice;
	int distancia;



};


class HeapFibonacci
{
public:
	HeapFibonacci();

	void insertVertex( FibonacciNode *nodo );
	FibonacciNode *extractMin();

private:
	int numeroNodos;
	FibonacciNode *minRoot;
	FibonacciNode *ultimoListaCircular;
	FibonacciNode *primeiroListaCircular;



};

#endif /* FIBONACCI_H_ */
