#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;
// Função para heapificar uma subárvore enraizada no índice i
void heapificar(vector<char>& arr, int n, int i) {
    int largest = i; // Inicializar largest como raiz
    int left = 2 * i + 1; // filho esquerdo
    int right = 2 * i + 2; // filho direito
    
    // Se o filho esquerdo é maior que a raiz
    if (left < n && arr[left] > arr[largest])
    largest = left;
    
    // Se o filho direito é maior que o maior até agora
    if (right < n && arr[right] > arr[largest])
    largest = right;
    
    // Se largest não é raiz
    if (largest != i) {
    swap(arr[i], arr[largest]);
    // Heapificar recursivamente a subárvore afetada
    heapificar(arr, n, largest);
    }
    }
    
    // Função para construir um heap máximo
    void construirHeap(vector<char>& arr, int n) {
    // Índice do último nó não-folha
    int startIdx = (n / 2) - 1;
    
    // Executar travessia em ordem reversa de nível a partir do último nó não-folha
    for (int i = startIdx; i >= 0; i--) {
    heapificar(arr, n, i);
    }
    }
    
    // Função para realizar a ordenação por heap
    void ordenarPorHeap(vector<char>& arr) {
    int n = arr.size();
    
    // Construir heap (rearranjar array)
    construirHeap(arr, n);
    
    // Extrair um elemento do heap um por um
    for (int i = n - 1; i > 0; i--) {
    // Mover raiz atual para o final
    swap(arr[0], arr[i]);
    
    // chamar heapificar máximo no heap reduzido
    heapificar(arr, i, 0);
    }
    }
    
    int main() {
    vector<char>arr = {'b', 'a', 'd', 'c', 'e'};
    
    cout << "Vetor antes da ordenação: ";
    for (char ch : arr) {
    cout << ch << " ";
    }
    cout << endl;
    
    ordenarPorHeap(arr);
    
    cout << "Vetor após a ordenação: ";
    for (char ch : arr) {
    cout << ch << " ";
    }
    cout << endl;
    
    return 0;
    }
