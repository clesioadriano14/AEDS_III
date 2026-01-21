#include <cmath>
#include "Grafos.hpp"
#include <vector>

// construtor e destrutor da classe Grafos
// construtor que inicializa o grafo com branco(0)
Grafos::Grafos() : MatrizAdj(nullptr), NumVertices(0), NumArestas(0), coordX(nullptr), coordY(nullptr), direcionado(false), nomeVertices(nullptr) {}

Grafos::~Grafos()
{

    if (MatrizAdj != nullptr)
    {
        for (int i = 0; i < NumVertices; i++)
            delete[] MatrizAdj[i];

        delete[] MatrizAdj;
    }

    delete[] coordX;
    delete[] coordY;
}
void Grafos::criarVazio(int NumDeVertices, bool Direcionado)
{
    this->NumVertices = NumDeVertices;
    this->direcionado = Direcionado;
    // Alocar coordenadas
    coordX = new int[NumVertices];
    coordY = new int[NumVertices];
    // alocar nomes
    this->nomeVertices = new string [NumVertices];

    for (int i = 0; i < NumVertices; i++)
    {
        coordX[i] = 0;
        coordY[i] = 0;
        nomeVertices[i] = "";
    }

    // Alocar matriz de adjacências
    MatrizAdj = new int *[NumVertices];
    
    for (int i = 0; i < NumVertices; i++)
    {
        MatrizAdj[i] = new int[NumVertices];
        for (int j = 0; j < NumVertices; j++)
        {
            MatrizAdj[i][j] = 0;
        }
    }
}
// metodo para importar de um arquivo o grafo

void Grafos::importar()
{

    ifstream arq;
    arq.open("Grafo_Exemplo.txt");
    if (!arq.is_open())
    {
        cout << "Erro ao abrir o arquivo!" << endl;
        return;
    }
    string linha;
    getline(arq, linha);
    // pega só o que vem depois do '='
    string valor = linha.substr(linha.find('=') + 1);

    // transforma em booleano
    if (valor == "sim")
        direcionado = true;
    else
        direcionado = false;

    arq >> NumVertices;

    criarVazio(NumVertices, direcionado);

    // passando coordenadas e nome dos vértices
    int id, x, y;
    char n[100];
    for (int i = 0; i < NumVertices; i++)
    {
        arq >> id >> x >> y >> ws;
        arq.getline(n,100);
        arq >> ws;
        editarNomeDoVertice(id,n);
        editarCoordenadaDoVertice(id,x,y);
    }
    // passando arestas
    arq >> NumArestas;
    int destino, origem, peso;
    for (int i = 0; i < NumArestas; i++)
    {
        arq >> origem >> destino >> peso;
        MatrizAdj[origem][destino] = peso;

        // se o grafo é não direcionado, colocamos o mesmo peso na direção oposta
        if (!direcionado)
            MatrizAdj[destino][origem] = peso;
    }
    arq.close();
}

void Grafos::exibirTodasAsAdjacencias()
{
    if (NumVertices == 0 || MatrizAdj == nullptr)
    {
        cout << "Grafo Vazio!" << endl;
        return;
    }
    for (int i = 0; i < NumVertices; i++)
    {
        cout << "Vertice: " << i << ": " ;
        for (int j = 0; j < NumVertices; j++)
        {
            cout << MatrizAdj[i][j] << "\t";
        }
        cout << endl;
    }
}
bool Grafos::consultarSeAdjacente(int origem, int destino)
{
    if (origem < 0 || origem >= NumVertices || destino < 0 || destino >= NumVertices)
    {
        cout << "Erro: Vertices invalidos!" << endl;
        return false;
    }
    if (MatrizAdj[origem][destino] != 0)

        return true;
    else
        return false;
}
void Grafos::inserAresta(int origem, int destino, int peso)
{
    if (origem < 0 || origem >= NumVertices || destino < 0 || destino >= NumVertices)
    {
        cout << "Erro: Vertices invalidos." << endl;
        return;
    }
    if (MatrizAdj[origem][destino] == 0)
    {
        NumArestas++;
    }
    if (this->direcionado == false)
    {
        MatrizAdj[destino][origem] = peso;
        MatrizAdj[origem][destino] = peso;
        cout << "Aresta inserida" << endl;
    }
    else
    {
        MatrizAdj[origem][destino] = peso;
        cout << "Aresta inserida" << endl;
    }
    
}

void Grafos::removerAresta(int origem, int destino)
{
    if (origem < 0 || origem >= NumVertices || destino < 0 || destino >= NumVertices)
    {
        cout << "Erro: Vertices invalidos!" << endl;
        return;
    }

    if (MatrizAdj[origem][destino] == 0)
    {
        cout << "Erro: Aresta inexistente";
        return;
    }
    NumArestas--;

    if (this->direcionado == false)
    {
        MatrizAdj[destino][origem] = 0;
        MatrizAdj[origem][destino] = 0;
        cout << "Aresta removida" << endl;
    }
    else
    {
        MatrizAdj[origem][destino] = 0;
        cout << "Aresta removida" << endl;
    }
}
void Grafos::editarCoordenadaDoVertice(int origem, int coordenadaX, int coordenadaY)
{
    if (origem < 0 || origem >= NumVertices)
    {
        cout << "Erro: Vertices invalidos!" << endl;
        return;
    }
    coordX[origem] = coordenadaX;
    coordY[origem] = coordenadaY;
    cout << "Coordenadas atualizadas!" << endl;
}

void Grafos::editarNomeDoVertice(int origem, string nome){
    if (origem < 0 || origem >= NumVertices)
    {
        cout << "Erro: Vertices invalidos!" << endl;
        return;
    }
    nomeVertices[origem] = nome;
    cout << "Nome do vértice atualizado!" << endl;
}

int Grafos::primeiroAdjacenteDoVertice(int origem)
{
    if (origem < 0 || origem >= NumVertices)
    {
        cout << "Erro: Vertices invalidos!" << endl;
        return -1;
    }
    for (int i = 0; i < NumVertices; i++)
    {
        if (MatrizAdj[origem][i] != 0)
        {
            return i;
        }
    }
    return -1;
}
int Grafos::proximoAdjacenteDoVertice(int origem, int atual)
{
    if (origem < 0 || origem >= NumVertices)
    {
        cout << "Erro: Vertices invalidos!" << endl;
        return -1;
    }
    for (int i = atual + 1; i < NumVertices; i++)
    {
        if (MatrizAdj[origem][i] != 0)
        {
            return i;
        }
    }
    return -1;
}
void Grafos::listaCompletaDeAdjacentesDoVertice(int origem)
{
    if (origem < 0 || origem >= NumVertices)
    {
        cout << "Erro: Vertices invalidos!" << endl;
        return;
    }
    int aux;
    aux = primeiroAdjacenteDoVertice(origem);
    while (aux != -1)
    {
        cout << "Indice:" << aux << " ";
        aux = proximoAdjacenteDoVertice(origem, aux);
    }
    cout << endl;
}

void Grafos::buscaProfundidade(){
    vector<int> descoberta(NumVertices);
    vector<int> termino(NumVertices);
    vector<int> antecessor(NumVertices);
    vector<char> cor(NumVertices);

    int tempo = 0;
    for (int origem = 0; origem < NumVertices; origem++)
    {
        antecessor[origem] = -1;
        cor[origem] = 'B';
    }
    
    for (int origem = 0; origem < NumVertices; origem++)
    {
        if (cor[origem] == 'B')
        {
            visitaProfundidade(origem, cor, descoberta, termino, antecessor, tempo);
        }
    }
}

void Grafos::visitaProfundidade(int origem, vector<char> &cor, vector<int> &descoberta, vector<int> &termino, vector<int>&antecessor, int &tempo){
    cor[origem] = 'C';
    tempo++;
    descoberta[origem] = tempo;
    cout << "\n Descoberta " <<  origem << "\n Tempo: " << descoberta[origem];
    for (int v = 0; v < NumVertices; v++) {
        // Checa se existe aresta entre u e v E se v é branco ('B')
        if (MatrizAdj[origem][v] != 0 && cor[v] == 'B') { 
            // a. Registrar antecessor de v sendo u
            antecessor[v] = origem;
            // b. Executar visitaEmProfundidade recursivamente para v
            visitaProfundidade(v, cor, descoberta, termino, antecessor, tempo);
        }
    }

    // 5. Colorir vértice u de preto
    cor[origem] = 'P';

    // 6. Incrementar o tempo e registrar tempo de término para u
    tempo++;
    termino[origem] = tempo;

    // 7. Exibir informações de finalização do vértice
    cout << "\n Vertice: " << origem << " finalizado no tempo: " << termino[origem] << " (Antecessor: " << antecessor[origem] << ")" << endl;
    


}
void Grafos::exportar()
{
    ofstream arq;
    arq.open("exportacao_Grafo.txt");
    if (!arq.is_open())
    {
        cout << "Erro ao abrir o arquivo!" << endl;
        return;
    }
    arq << "direcionado=";
    if (direcionado)
        arq << "sim" << endl;
    else
        arq << "nao" << endl;

    arq << NumVertices << endl;

    // passando coordenadas e nomes dos vértices
    for (int i = 0; i < NumVertices; i++)
    {
        arq << i << " " << coordX[i] << " " << coordY[i] << " " << nomeVertices[i] << endl;
    }
    // passando arestas
    arq << NumArestas << endl;

    for (int i = 0; i < NumVertices; i++)
    {
        for (int j = 0; j < NumVertices; j++)
        {
            // Validacao pra ver se existe aresta
            if (MatrizAdj[i][j] != 0)
            {
                if (direcionado)
                {
                    // Se for direcionado, todas as conexoes
                    arq << i << " " << j << " " << MatrizAdj[i][j] << endl;
                }
                else
                {
                    // Se for nao direcionado, salvam apenas a metade da matriz (triângulo superior)
                    if (i < j)
                    {
                        arq << i << " " << j << " " << MatrizAdj[i][j] << endl;
                    }
                }
            }
        }
    }
    arq.close();
}

void Grafos::mostrarGraficamente()
{
    ofstream arq;
    arq.open("grafo_visual.html");

    if (!arq.is_open())
    {
        cout << "Erro ao criar arquivo de visualizacao!" << endl;
        return;
    }

    // 1. Cabeçalho HTML e SVG
    arq << "<!DOCTYPE html>" << endl;
    arq << "<html><head><title>Visualizacao do Grafo</title></head>" << endl;
    arq << "<body>" << endl;
    arq << "<h1 style='text-align:center;'>Visualizacao do Grafo</h1>" << endl;
    arq << "<div style='border: 1px solid #ccc; width: 800px; height: 600px; margin: 0 auto;'>" << endl;
    arq << "<svg width='800' height='600' xmlns='http://www.w3.org/2000/svg'>" << endl;

    // Definição de seta para grafos direcionados
    arq << "<defs><marker id='arrowhead' markerWidth='10' markerHeight='7' refX='28' refY='3.5' orient='auto'>" << endl;
    arq << "<polygon points='0 0, 10 3.5, 0 7' fill='#555'/></marker></defs>" << endl;

    // 2. Definir posições (Se tudo for 0,0, geramos um círculo automático)
    int *posX = new int[NumVertices];
    int *posY = new int[NumVertices];
    bool usarCoordDoArquivo = false;

    // Verifica se existe alguma coordenada preenchida
    for(int i=0; i<NumVertices; i++) {
        if(coordX[i] != 0 || coordY[i] != 0) usarCoordDoArquivo = true;
    }

    if (usarCoordDoArquivo) {
        int escala = 5;
        int margem = 50; 

        for(int i=0; i<NumVertices; i++) {
            // Aplica a escala e a margem
            posX[i] = (coordX[i] * escala) + margem;
            posY[i] = (coordY[i] * escala) + margem;
        }
    } else {
        int centroX = 400, centroY = 300, raio = 200;
        double anguloPasso = 2 * 3.14159 / NumVertices;
        
        for (int i = 0; i < NumVertices; i++) {
            posX[i] = centroX + raio * cos(i * anguloPasso);
            posY[i] = centroY + raio * sin(i * anguloPasso);
        }
    }

    //Arestas
    for (int i = 0; i < NumVertices; i++)
    {
        for (int j = 0; j < NumVertices; j++)
        {
            if (MatrizAdj[i][j] != 0)
            {
                // trata a questao de desenhar aresta duplicada em grafo não direcionado
                if (!direcionado && i > j) continue; 

                arq << "<line x1='" << posX[i] << "' y1='" << posY[i] 
                    << "' x2='" << posX[j] << "' y2='" << posY[j] 
                    << "' stroke='#555' stroke-width='2'";
                
                if (direcionado) arq << " marker-end='url(#arrowhead)'";
                
                arq << " />" << endl;
                
                //Mostrar o peso
                int meioX = (posX[i] + posX[j]) / 2;
                int meioY = (posY[i] + posY[j]) / 2;
                arq << "<text x='" << meioX << "' y='" << meioY 
                    << "' fill='red' font-size='12'>" << MatrizAdj[i][j] << "</text>" << endl;
            }
        }
    }

    // Vertices
    for (int i = 0; i < NumVertices; i++)
    {
        arq << "<circle cx='" << posX[i] << "' cy='" << posY[i] 
            << "' r='20' fill='#3498db' stroke='#2980b9' stroke-width='2' />" << endl;
        
       
        arq << "<text x='" << posX[i] << "' y='" << posY[i] + 5 
            << "' font-family='Arial' font-size='15' fill='white' text-anchor='middle'>" 
            << i << "</text>" << endl;
    }

    arq << "</svg></div></body></html>" << endl;
    arq.close();

    delete[] posX;
    delete[] posY;

    cout << "Arquivo 'grafo_visual.html' gerado com sucesso!" << endl;
    system("start grafo_visual.html");
}
