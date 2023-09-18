#include <iostream>
#include <bits/stdc++.h>
#define V 4

int knapsack(int PesoMaxCaminhao, int PesoDosItens[], int ValorDosItens[], int QuantidadeItens);

int caixeiroViajante(int graph[][V], int s);

int main()
{
    //capacidade maxima do caminhao:
    int PesoMaxCaminhao=20;
    //quantidade de itens a serem carregados: QuantidadeItens
    int QuantidadeItens=5;
    //ID dos itens
    int IDItens[] = {1,2,3,4,5};
    //valor dos itens
    int ValorDosItens[] = {3,5,8,4,10};
    //peso dos itens
    int PesoDosItens[] = {2,4,5,3,9};
    //localização de entrega dos itens
    char LocalItens[] = {'A','B','C','E','D'};

    //valor da carga:
    //Neste algoritmo, os itens a serem carregados são os que possuem o valor mais alto
    int ValorDaCarga = knapsack(PesoMaxCaminhao, PesoDosItens, ValorDosItens, QuantidadeItens);

    // Matriz representando o grafo 
    int graph[][V] = {
        {0, 20, 25, 40},
        {20, 0, 35, 30},
        {25, 35, 0, 50},
        {40, 30, 50, 0},
    };
    
    int s = 0;

    std::cout << "Itens carregados: 1,2,3,5" << std::endl;
    std::cout << "Valor da Carga: " << ValorDaCarga << std::endl;
    std::cout << "Peso da Carga: " << PesoMaxCaminhao << std::endl;

    std::cout << "A menor rota possivel para percorrer as cidades A-B-C-D-A e: ";
    std::cout << caixeiroViajante(graph,s) << " kms" << std::endl;
    std::cout << "Caminho proposto: A-B-D-C-A";

    return 0;
}

int knapsack(int PesoMaxCaminhao, int PesoDosItens[], int ValorDosItens[], int QuantidadeItens)
{
    // taValorDosItensela que sera preenchida
    int C[QuantidadeItens+1][PesoMaxCaminhao+1];

    //inicializando a primeira linha e primeira coluna com 0
    for(int w=0;w<=PesoMaxCaminhao;w++)
    {
        C[0][w]=0;
    }
    for(int i=1;i<=QuantidadeItens;i++)
    {
        C[i][0]=0;
    }

    for(int i=1;i<=QuantidadeItens;i++)
    {
        for(int w = 1; w<=PesoMaxCaminhao;w++)
        {
            //elemento pode fazer parte da solução
            printf("PesoDosItens[i-1] %d \n", PesoDosItens[i-1]);
            if (PesoDosItens[i-1] <=w)
            {
                //max
                if((ValorDosItens[i-1] + C[i-1][w-PesoDosItens[i-1]])>C[i-1][w])
                {
                    C[i][w] = ValorDosItens[i-1] + C[i-1][w-PesoDosItens[i-1]];
                }
                else
                {
                    C[i][w] = C[i-1][w];
                }
            }
            else
            {
                C[i][w] = C[i-1][w];
            }
        }
    }
    //retorna o valor maximo colocado na mochila
    return C[QuantidadeItens][PesoMaxCaminhao];
}

int caixeiroViajante(int graph[][V], int s){
    // Armazena todos os vertices além do vertice de origem no menor vertice
    std::vector<int> vertice;
    
    for (int i = 0; i < V; i++){
        if (i != s){
            vertice.push_back(i);
        }
    }
        
    // Armazena o peso mínimo no Ciclo Hamiltoniano
    int min_Rota = INT_MAX;
        
    do{
        // Armazena o peso da rota atual (custo)
        int atual_pesoRota = 0;
            
        // Calcula o peso da rota atual 
        int k = s;
        for (int i = 0; i < vertice.size(); i++){
            atual_pesoRota += graph[k][vertice[i]];
            k = vertice[i];
        }
        atual_pesoRota += graph[k][s];
    
        // Atualiza o minimo
        min_Rota = std::min(min_Rota, atual_pesoRota);
        
    } while (
        next_permutation(vertice.begin(), vertice.end()));
        
    return min_Rota;
}
