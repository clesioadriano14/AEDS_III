#include <iostream>
#include "Grafos.hpp"
#include <limits>

using namespace std;

int main()
{
    Grafos NovoGrafo;
    int opcao, x, y;
    int origem, destino, peso;
    string nome;
    do
    {
        cout << "\n\n--------Menu---------\n";
        cout << "\nDigite a opcao desejada:\n";
        cout << "0  - Sair\n";
        cout << "1  - Importar grafo de arquivo .txt\n";
        cout << "2  - Criar grafo vazio\n";
        cout << "3  - Exibir as adjacencias\n";
        cout << "4  - Consultar adjacencia entre vertices\n";
        cout << "5  - Inserir nova aresta\n";
        cout << "6  - Inserir novo conjunto de arestas\n";
        cout << "7  - Remover arestas\n";
        cout << "8  - Editar coordenadas vertice\n";
        cout << "9  - Editar nomes dos vertices\n";
        cout << "10 - Buscar primeiro adjacente\n";
        cout << "11 - Buscar proximo adjacente\n";
        cout << "12 - Imprimir lista completa adjacentes\n";
        cout << "13 - Realizar busca em profundidade\n";
        cout << "14 - Exportar grafo para arquivo .txt\n";
        cout << "15 - Visualizar Grafo\n";

        cin >> opcao;
        if (cin.fail()) 
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nErro: Digite apenas numeros!" << endl;
            opcao = -1;
            cout << "Pressione Enter para voltar ao menu...";
            cin.get(); 
            system("cls"); 
            continue; 
        }
        switch (opcao)
        {
        case 0:
            cout << "PROGRAMA ENCERRADO";
            break;
        case 1:
            NovoGrafo.importar();
            cout << "Grafo importado de arquivo de texto!" << endl;
            cout << "\n--- Exibicao Concluida. Pressione Enter para voltar ao menu ---" << endl;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.get();
            system("cls");
            break;
        case 2:
            int numVert;
            bool direcionado;
            cout << "Informe o numero de Vertices: " << endl;
            cin >> numVert;
            cout << "Escreva 1 para direcionado e 0 para nao direcionado: " << endl;
            cin >> direcionado;
            NovoGrafo.criarVazio(numVert, direcionado);
            break;
        case 3:
            NovoGrafo.exibirTodasAsAdjacencias();
            cout << "\n--- Exibicao Concluida. Pressione Enter para voltar ao menu ---" << endl;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.get();
            system("cls");
            break;
        case 4:
            cout << "Informe o primeiro vertice: ";
            cin >> origem;
            cout << "Informe o segundo vertice: ";
            cin >> destino;
            if (NovoGrafo.consultarSeAdjacente(origem, destino))
                cout << "Vertices " << origem << " e " << destino << " sao adjacentes!";
            else
                cout << "Vertices " << origem << " e " << destino << " nao sao adjacentes!";
            cout << "\n--- Exibicao Concluida. Pressione Enter para voltar ao menu ---" << endl;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.get();
            system("cls");
            break;
        case 5:
            cout << "Informe o vertice origem: ";
            cin >> origem;
            cout << "Informe o vertice destino: ";
            cin >> destino;
            cout << "Informe o peso: ";
            cin >> peso;
            NovoGrafo.inserAresta(origem, destino, peso);
            cout << "\n--- Exibicao Concluida. Pressione Enter para voltar ao menu ---" << endl;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.get();
            system("cls");
            break;
        case 6:
            int qtd;
            cout << "Quantas arestas voce deseja inserir? ";
            cin >> qtd;
            for (int i = 0; i < qtd; i++)
            {
                cout << "Preenchendo aresta " << i + 1 << endl;
                cout << "Informe o vertice origem: ";
                cin >> origem;
                cout << "Informe o vertice destino: ";
                cin >> destino;
                cout << "Informe o peso: ";
                cin >> peso;
                NovoGrafo.inserAresta(origem, destino, peso);
            }
            cout << "\n--- Exibicao Concluida. Pressione Enter para voltar ao menu ---" << endl;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.get();
            system("cls");
            break;
        case 7:
            cout << "Informe o vertice origem: ";
            cin >> origem;
            cout << "Informe o vertice destino: ";
            cin >> destino;
            NovoGrafo.removerAresta(origem, destino);
            cout << "\n--- Exibicao Concluida. Pressione Enter para voltar ao menu ---" << endl;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.get();
            system("cls");
            break;
        case 8:
            cout << "Informe o vertice origem: ";
            cin >> origem;
            cout << "Informe a coordenada X: ";
            cin >> x;
            cout << "Informe a coordenada Y: ";
            cin >> y;
            NovoGrafo.editarCoordenadaDoVertice(origem, x, y);
            cout << "\n--- Exibicao Concluida. Pressione Enter para voltar ao menu ---" << endl;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.get();
            system("cls");
            break;
        case 9:
            cout << "Informe o vertice origem: ";
            cin >> origem;
            cout << "Informe o novo nome: ";
            cin >> nome;
            NovoGrafo.editarNomeDoVertice(origem, nome);
            cout << "\n--- Exibicao Concluida. Pressione Enter para voltar ao menu ---" << endl;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.get();
            system("cls");
        case 10:
            int result;
            cout << "Informe o vertice de busca: ";
            cin >> origem;
            result = NovoGrafo.primeiroAdjacenteDoVertice(origem);
            if (result != -1)
            {
                cout << "O primeiro adjacente do vertice " << origem << " e: " << result;
            }
            else
            {
                cout << "O vertice " << origem << " nao possui adjacente ";
            }
            cout << "\n--- Exibicao Concluida. Pressione Enter para voltar ao menu ---" << endl;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.get();
            system("cls");
            break;
        case 11:
            int atual, resultado;
            cout << "Informe o vertice origem: ";
            cin >> origem;
            cout << "Informe o adjacente atual: ";
            cin >> atual;
            resultado = NovoGrafo.proximoAdjacenteDoVertice(origem, atual);
            if (resultado != -1)
            {
                cout << "O proximo adjacente do vertice de indice" << origem << " cujo adjacente atual indice: " << atual << " sera o indice: " << resultado;
            }
            else
            {
                cout << "O vertice de indice " << origem << " nao possui adjacente apos o indice: " << atual;
            }
            cout << "\n--- Exibicao Concluida. Pressione Enter para voltar ao menu ---" << endl;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.get();
            system("cls");
            break;
        case 12:
            cout << "Informe o vertice origem: ";
            cin >> origem;
            NovoGrafo.listaCompletaDeAdjacentesDoVertice(origem);
            cout << "\n--- Exibicao Concluida. Pressione Enter para voltar ao menu ---" << endl;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.get();
            system("cls");
            break;
        case 13:
            cout << "Realizando Busca em Profundidade!";
            NovoGrafo.buscaProfundidade();
            cout << "\n--- Exibicao Concluida. Pressione Enter para voltar ao menu ---" << endl;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.get();
            system("cls");
            break;
        case 14:
            NovoGrafo.exportar();
            break;
        case 15: // (Opcional) Visualizar Grafo
            NovoGrafo.mostrarGraficamente();
            cout << "\n--- Pressione Enter para voltar ---";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            break;
        default:
            cout << "\nOpcao invalida\n";
        }
    } while (opcao != 0);

    return 0;
}