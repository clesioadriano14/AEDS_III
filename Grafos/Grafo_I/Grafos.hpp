#ifndef Grafos_hpp
#define Grafos_hpp

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Grafos
{
private: // atributos da implementação da classe Grafos
    int **MatrizAdj;
    int NumVertices;
    int NumArestas;
    string *nomeVertices;
    int *coordX;
    int *coordY;
    bool direcionado;

public: // construtor que inicializa o grafo com branco(0)
    Grafos() ;
    ~Grafos(); 

    // metodo para importar de um arquivo o grafo
    void importar();

    void criarVazio(int NumDeVertices, bool Direcionado)
    ;
        
    void exibirTodasAsAdjacencias()
    ;     
    
    bool consultarSeAdjacente(int origem, int destino)
    ;
    
    void inserAresta(int origem, int destino, int peso)
    ;
    
    void removerAresta(int origem, int destino)
    ;
    
    void editarCoordenadaDoVertice(int origem, int coordenadaX, int coordenadaY)
    ;

    void editarNomeDoVertice(int u, string nome)
    ;

    int primeiroAdjacenteDoVertice(int origem)
    ;
    
    int proximoAdjacenteDoVertice(int origem, int atual)
    ;
    
    void listaCompletaDeAdjacentesDoVertice(int origem)
    ;
    void buscaProfundidade()
    ;
    void visitaProfundidade (int origem, vector<char> &cor, vector<int> &descoberta, vector<int> &termino, vector<int>&antecessor, int &tempo)
    ;
    void exportar()
    ;
    
    void mostrarGraficamente()
    ;
    
};

#endif 