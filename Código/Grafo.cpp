/*
 * Grafo.cpp
 *
 *  Created on: 14 de jul de 2016
 *      Author: administrador
 */

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cctype>
#include <queue>
#include <string>
#include <climits>
#include <list>
#include "Grafo.h"
#include "Fibonacci.h"
using namespace std;

struct Heap
{
	unsigned int idVertice;
	//unsigned int posicaoAtual;
	long int distancia;
	bool aSerChecado;
};

Grafo::Grafo()
{
	numeroArestas = 0;
	numeroVertices = 0;
	verticesGrafos = NULL;

	// TODO Auto-generated constructor stub

}

void Grafo::leArquivoDeEntrada( const char *nome )
{
	char inicio;
	bool modoLeituraOficial = true; // Usado para determinar se o modo de leitura segue o padrão oficial de leitura de grafos ou o costumizado ( true = Oficial; false = Costumizado )
	ifstream arqEntrada( nome, ios::in );

	unsigned int vert1;
	unsigned int vert2;
	long int peso;


	if ( !arqEntrada )
	{
		cerr << "Erro ao abrir o arquivo de entrada. Encerrando o programa. Verifique se o mesmo existe ou está escrito de forma correta" << endl;
		exit( 0 );
	}

	arqEntrada >> inicio;

	if ( isalpha( inicio ) )
		modoLeituraOficial = true;
	else
		modoLeituraOficial = false;


	if ( modoLeituraOficial )
	{
		arqEntrada.seekg( 0, ios::beg );
		string letraInicial;

		while ( !arqEntrada.eof() )
		{
			arqEntrada >> letraInicial;
			if ( letraInicial == "c" )
			{
				getline( arqEntrada, letraInicial );
				//cout << letraInicial << endl;
				continue;
			}
			else if ( letraInicial == "a" )
			{
				arqEntrada >> vert1 >> vert2 >> peso;
				vert1--;
				vert2--;
				criaVertice( vert1, vert2, peso );
			}
			else if ( letraInicial == "p" )
			{
				arqEntrada >> letraInicial >> numeroVertices >> numeroArestas;
				verticesGrafos = new Aresta[ numeroVertices ];
				for ( unsigned int i = 0; i < numeroVertices; i++ )
				{
					verticesGrafos[ i ].idVertice1 = i;
					verticesGrafos[ i ].idVertice2 = i;
					verticesGrafos[ i ].pesoAresta = -1;
				}
			}
		}
	}
	else
	{
		arqEntrada.seekg( 0, ios::beg ); // Retorna o cabeçote de leitura ao inicio do arquivo.

		arqEntrada >> numeroVertices >> numeroArestas;
		verticesGrafos = new Aresta[ numeroVertices ]; // Aloca o número de vertices correspondentes ao grafo representado pelo arquivo de entrada

		for ( unsigned int i = 0; i < numeroVertices; i++ )
		{
			verticesGrafos[ i ].idVertice1 = i;
			verticesGrafos[ i ].idVertice2 = i;
			verticesGrafos[ i ].pesoAresta = -1;
		}


		while ( !arqEntrada.eof() )
		{
			arqEntrada >> vert1 >> vert2 >> peso;
			criaVertice( vert1, vert2, peso );
		}

	}
}

void swapAuxiliar( Heap *elemento1, Heap *elemento2, unsigned int *vetorPosicoes )
{
	//cout << vetorPosicoes[ elemento1->idVertice ] << "-->" << elemento2->idVertice << endl;
	//cout << vetorPosicoes[ elemento2->idVertice ] << "-->" << elemento1->idVertice << endl;
	vetorPosicoes[ elemento1->idVertice ] = elemento2->idVertice;
	vetorPosicoes[ elemento2->idVertice ] = elemento1->idVertice;
	//cout << vetorPosicoes[ elemento1->idVertice ] << endl;
	//cout << vetorPosicoes[ elemento2->idVertice ] << endl;
	Heap temp = *elemento1;
	*elemento1 = *elemento2;
	*elemento2 = temp;
}

void moveDown( Heap *vetor, unsigned int primeiro, unsigned int ultimo, unsigned int *vetorPosicoes )
{
	unsigned int menor = 2*primeiro + 1;
	while ( menor <= ultimo )
	{
		if ( menor < ultimo && vetor[ menor ].distancia > vetor[ menor + 1 ].distancia )
			menor++;

		if ( vetor[ primeiro ].distancia > vetor[ menor ].distancia )
		{
			swapAuxiliar( &vetor[ primeiro ], &vetor[ menor ], vetorPosicoes );
			primeiro = menor;
			menor = 2*primeiro + 1;
		}
		else
			menor = ultimo + 1;
	}

}

// Função auxiliar para a construção da Heap
void criaHeap( Heap *vetor, unsigned int tamanho, unsigned int *posicoes )
{
	for ( int i = tamanho / 2 - 1; i >= 0; --i )
		moveDown( vetor, i, tamanho-1, posicoes);
}

void imprimeHeap( Heap *h, unsigned int tamanho )
{
	cout << "Id\tDistância" << endl;
	for ( unsigned int i = 0; i < tamanho; i++ )
	{
		cout << h[ i ].idVertice << "\t" << h[ i ].distancia << endl;
	}
}

void imprimeVetorPosicoes( unsigned int *vetor, unsigned int tamanho )
{
	cout << "Vetor Posições" << endl;
	for ( unsigned int i = 0; i < tamanho; i++ )
		cout << vetor[ i ] << endl;
}

void impimeRotaMaisCurta( unsigned int const *origemPtr, unsigned int const *detinoPtr, unsigned int const *anterior, unsigned int const *predecessor )
{
	if ( predecessor[ (*anterior) ] != *origemPtr )
	{
		impimeRotaMaisCurta( origemPtr, detinoPtr, &predecessor[ (*anterior) ], predecessor );
		cout << predecessor[ (*anterior) ] << " - ";
	}
	else
		cout << cout << predecessor[ (*anterior) ] << " - ";
}

/*void Grafo::dijkstraHeapFibonacci( unsigned int origem, unsigned int destino )
{
	HeapFibonacci *heap = new FibonacciHeap();

	heap->insereVertice( 
}*/
// No caso do Dijkstra Canônico, a posição dos vetores predecessor, distancias, aSerChecado correspondem ao ID dos vértices
void Grafo::dijkstraCanonico( unsigned int origem, unsigned int destino )
{
	if ( origem >= numeroVertices || destino >= numeroVertices )
	{
		cerr << "Erro: O vértice origem ou destino não existe no grafo (nVertice > numeroVertices)" << endl;
		return;
	}

	// Inicializações de Variáveis
	unsigned int tamanhoVetor = numeroVertices;
	unsigned int predecessor[ numeroVertices ];
	unsigned int distancias[ numeroVertices ];
	unsigned int verticeAtual = origem;
	bool aSerChecado[ numeroVertices ];
	
	for ( int i = 0; i < numeroVertices; i++ )
	{
		aSerChecado[ i ] = true;
		distancias[ i ] = UINT_MAX;
		predecessor[ i ] = 0;
	}

	// Inicialização de origem
	distancias[ origem ] = 0;
	aSerChecado[ origem ] = false;
	predecessor[ origem ] = origem;
	
	while ( tamanhoVetor > 0 )
	{
		for ( list<Aresta>::const_iterator it = verticesGrafos[ verticeAtual ].verticesAdjacentes.begin(); it != verticesGrafos[ verticeAtual ].verticesAdjacentes.end(); ++it )
		{
			unsigned int posicaoVerticeAdjacente = it->idVertice2;
			
			if ( !aSerChecado[ posicaoVerticeAdjacente ] )
				continue;
			
			if ( distancias[ posicaoVerticeAdjacente ] > distancias[ verticeAtual ] + it->pesoAresta )
			{
				distancias[ posicaoVerticeAdjacente ] = distancias[ verticeAtual ] + it->pesoAresta;
				predecessor[ posicaoVerticeAdjacente ] = verticeAtual;
			}
		}
		
		unsigned int menorElemento = UINT_MAX;
		// Busca menor elemento
		for ( int i = 0; i < numeroVertices; i++ )
		{
			if ( !aSerChecado[ i ] )
				continue;
			if ( distancias[ i ] < menorElemento )
			{
				menorElemento = distancias[ i ];
				verticeAtual = i;
			}
		}

		aSerChecado[ verticeAtual ] = false;
		tamanhoVetor--;
	}

	// Imprime rota - Comente o trecho a seguir para os testes de tempos
	//impimeRotaMaisCurta( &origem, &destino, &predecessor[ destino ] , predecessor );
	for ( int i = 0; i < numeroVertices; i++ )
	{
		cout << i << ": " << predecessor[ i ] << endl;
	}
	
}

void Grafo::dijkstraHeapBinario( unsigned int origem, unsigned int destino )
{
	if ( origem >= numeroVertices || destino >= numeroVertices )
	{
		cerr << "Erro: O vértice origem ou destino não existe no grafo (nVertice > numeroVertices)" << endl;
		return;
	}

	unsigned int tamanhoVetor = numeroVertices;
	unsigned int predecessor[ numeroVertices ];
	unsigned int listaPosicoes[ numeroVertices ]; // Mostra a posição atual dos vértices na Heap
	Heap *minHeap = new Heap[ numeroVertices ];
	for ( unsigned int i = 0; i < numeroVertices; i++ )
	{
		minHeap[ i ].aSerChecado = true;
		minHeap[ i ].distancia = LONG_MAX;
		minHeap[ i ].idVertice = i;
		predecessor[ i ] = 0;
		listaPosicoes[ i ] = i;
	}

	minHeap[ origem ].distancia = 0;
	criaHeap( minHeap, numeroVertices, listaPosicoes );
	/*imprimeHeap( minHeap, numeroVertices );
	imprimeVetorPosicoes( listaPosicoes, numeroVertices );*/

	// VERIFICAR DEPOIS AQUI SE DEVO MUDAR DE GT PARA GE
	while ( tamanhoVetor > 0 )
	{

		Heap *atual = &minHeap[ 0 ];
		atual->aSerChecado = false;
		for ( list<Aresta>::iterator it = verticesGrafos[ atual->idVertice ].verticesAdjacentes.begin(); it != verticesGrafos[ atual->idVertice ].verticesAdjacentes.end(); ++it )
		{
			unsigned int posicaoCorreta = listaPosicoes[ it->idVertice2 ];
			Heap *adjacente = &minHeap[ posicaoCorreta ];

			if ( !adjacente->aSerChecado )
				continue;

			if ( adjacente->distancia > atual->distancia + it->pesoAresta )
			{
				adjacente->distancia = atual->distancia + it->pesoAresta;
				predecessor[ adjacente->idVertice ] = atual->idVertice;
			}

		}
		//imprimeHeap( minHeap, numeroVertices );
		swapAuxiliar( &minHeap[ 0 ], &minHeap[ tamanhoVetor - 1], listaPosicoes );
		tamanhoVetor--;
		for ( int i = tamanhoVetor / 2 - 1; i >= 0; --i )
			moveDown( minHeap, i, tamanhoVetor-1, listaPosicoes);
		//imprimeHeap( minHeap, numeroVertices );
		//imprimeVetorPosicoes( listaPosicoes, numeroVertices );


	}

	/*for ( unsigned int i = 0; i < numeroVertices; i++ )
		cout << predecessor[ i ] << " ";
	cout << endl;*/


}

void Grafo::buscaEmLargura()
{
	unsigned int listaVertices[ numeroVertices ];
	unsigned int i = 1;
	queue<unsigned int> fila;
	list<Aresta> arestas;

	for ( unsigned int k = 0; k < numeroVertices; k++ )
		listaVertices[ k ] = 0;

	for ( unsigned int k = 0; k < numeroVertices; k++ )
	{
		if ( listaVertices[ k ] != 0 )
			continue;
		listaVertices[ k ] = i++;
		fila.push( k );
		while ( !fila.empty() )
		{
			k = fila.front();
			fila.pop();
			for ( list<Aresta>::const_iterator it = verticesGrafos[ k ].verticesAdjacentes.begin(); it != verticesGrafos[ k ].verticesAdjacentes.end(); ++it )
			{
				if ( listaVertices[ it->idVertice2 ] == 0 )
				{
					listaVertices[ it->idVertice2 ] = i++;
					fila.push( it->idVertice2 );
					arestas.push_back( (*it) );
				}
			}

		}

	}

	// PARA IMPRIMIR, DESCOMENTE ABAIXO
	/*cout << "Busca em Largura" << endl;

	for ( list<Aresta>::const_iterator it = arestas.begin(); it != arestas.end(); ++it )
		cout << it->idVertice1 << " ---> " << it->idVertice2 << endl;*/





}

void Grafo::DSF( unsigned int v, unsigned int *lista, list<Aresta> &a, unsigned int *i )
{
	lista[ v ] = ++(*i);
	for ( list<Aresta>::const_iterator it = verticesGrafos[ v ].verticesAdjacentes.begin(); it != verticesGrafos[ v ].verticesAdjacentes.end(); ++it )
	{
		if ( lista[ it->idVertice2 ] == 0 )
		{
			a.push_back( (*it) );
			DSF( it->idVertice2, lista, a, i );
		}
	}

}

void Grafo::buscaEmProfundidade()
{
	unsigned int i;
	unsigned int listaVertices[ numeroVertices ];
	list<Aresta> arestas;

	for ( unsigned int k = 0; k < numeroVertices; k++ )
		listaVertices[ k ] = 0;

	for ( unsigned int k = 0; k < numeroVertices; k++ )
	{
		DSF( k, listaVertices, arestas, &i );
	}

	// PARA IMPRIMIR, DESCOMENTE ABAIXO
	/*
	cout << "Busca em Profundidade" << endl;
	for ( list<Aresta>::const_iterator it = arestas.begin(); it != arestas.end(); it++ )
	{
		cout << it->idVertice1 << " ---> " << it->idVertice2 << endl;
	}*/
	arestas.clear();
}

void Grafo::imprimeGrafo() const
{
	for ( unsigned int i = 0; i < numeroVertices; i++ )
	{
		for ( list<Aresta>::const_iterator it = verticesGrafos[ i ].verticesAdjacentes.begin(); it != verticesGrafos[ i ].verticesAdjacentes.end(); ++it )
		{
			cout << it->idVertice1 << " ---> " << it->idVertice2 << " w: " << it->pesoAresta << endl;
		}
	}
}

void Grafo::criaVertice(unsigned int idVert1, unsigned int idVert2, long int peso )
{
	Aresta novaAresta;
	novaAresta.idVertice1 = idVert1;
	novaAresta.idVertice2 = idVert2;
	novaAresta.pesoAresta = peso;

	verticesGrafos[ idVert1 ].verticesAdjacentes.push_back(novaAresta);
}

unsigned int Grafo::getNumeroArestas() const {
	return numeroArestas;
}

void Grafo::setNumeroArestas(unsigned int numeroArestas) {
	this->numeroArestas = numeroArestas;
}

unsigned int Grafo::getNumeroVertices() const {
	return numeroVertices;
}

void Grafo::setNumeroVertices(unsigned int numeroVertices) {
	this->numeroVertices = numeroVertices;
}
