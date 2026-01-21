#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>

using namespace std;

// Função para contruir n fitas
void CriarFitas(string base, int qtd){
    for (int i = 1; i <= qtd; i++)
    {
        ofstream arq;
        arq.open(base + to_string(i) + ".txt");
        if (!arq.is_open())
        {
            cout << "Error ao abrir o arquivo!" << endl;
        }
        arq.close();
    }
}

// Função para alocar valores
void addInFita(string valor, string base, int i) {
    ofstream arq;
        arq.open(base + to_string(i) + ".txt", ios::app);
        if (!arq.is_open())
        {
            cout << "Error ao abrir o arquivo!" << endl;
        }
        arq << valor << endl;
        arq.close();
}

int main()
{
    int tmemoria, fitas, i, j=1;
    char c;
    string base = "fita";
    vector<char> mem;

    // Leitura do arquivo inicial
    fstream arq("dados.in", ios::in);
    arq >> tmemoria >> fitas;
    arq.ignore();

    // Criando as n fitas
    CriarFitas(base, fitas);

    cout << "Fitas: " << fitas << endl;
    cout << "T. Memoria: " << tmemoria << endl;


    // Motangem dos blocos iniciais ordenados
    while (!arq.eof())
    {
        i = 0;
        while (i < tmemoria&& !arq.eof())
        {
            arq.get(c);
            mem.push_back(c);
            i++;
            arq >> ws;
        }
        sort(mem.begin(), mem.end());
        cout << string(mem.begin(), mem.end()) << endl;
        
        // Alocando valores nas fitas inicias

        addInFita(string(mem.begin(), mem.end()),base,j);
        j++;
        if (j > fitas/2)
        {
            j=1;
        }
        
        mem.clear();
    }
    arq.close();

    return 0;
}   