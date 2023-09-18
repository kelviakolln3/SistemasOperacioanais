#include <bits/stdc++.h>
using namespace std;
#define V 4
#define QtdeItens 5
struct Trajeto{
	int weight;
	char inicio, final;
};
struct Trajetos{
	struct Trajeto* trajeto;
};
struct Trajetos* createTrajeto()
{
	struct Trajetos* trajetos = new Trajetos;
	trajetos->trajeto = new Trajeto[3];
	return trajetos;
}
struct ItemMochila{
	int idItem;
	int pesoItem;
	int valorItem;
	char entrega;
};

struct ItensMochila{
	struct ItemMochila* itemMochila;
};

struct ItensMochila* createMochila()
{
	struct ItensMochila* itensMochila = new ItensMochila;
	itensMochila->itemMochila = new ItemMochila[QtdeItens];
	return itensMochila;
}

struct Trajetos* traj = createTrajeto();
struct ItensMochila* itemMoc = createMochila();
int bestWay[V] = {0,0,0,0};
int cont = 0;
int aux = 0;
int CaixeiroViajante(int graph[][V], int s)
{
	vector<int> vertex;
	for (int i = 0; i < V; i++)
		if (i != s)
			vertex.push_back(i);
	int min_path = INT_MAX;
	do {
		int somaWeight = 0;
		int current_pathweight = 0;
		int k = s;
		int weight[V] = {0,0,0,0};
		for (int i = 0; i < vertex.size(); i++) {
			current_pathweight += graph[k][vertex[i]];
			weight[i] = graph[k][vertex[i]];
			cont = i;	
			k = vertex[i];		
		}
		current_pathweight += graph[k][s];
		weight[cont+1] = graph[k][s];
		min_path = min(min_path, current_pathweight);
		
		for(int i = 0; i < V; i++){
			somaWeight = somaWeight + weight[i];
		}
		if(somaWeight == min_path){
			for(int i = 0; i < V; i++){
				bestWay[i] = weight[i];
			}
		}
	} while (next_permutation(vertex.begin(), vertex.end()));
	return min_path;
}
int knapsack(int PesoMaxCaminhao, ItensMochila* itensMochila)
{
    int C[QtdeItens+1][PesoMaxCaminhao+1];

    for(int w = 0; w <= PesoMaxCaminhao; w++)
    {
        C[0][w] = 0;
    }
    for(int i = 1; i <= QtdeItens; i++)
    {
        C[i][0]=0;
    }

    for(int i = 1; i <= QtdeItens; i++)
    {
        for(int w = 1; w <= PesoMaxCaminhao; w++)
        {
            if (itensMochila->itemMochila[i-1].pesoItem <= w)
            {
                if((itensMochila->itemMochila[i-1].valorItem + C[i-1][w - itensMochila->itemMochila[i-1].pesoItem]) > C[i-1][w])
                {
                    C[i][w] = itensMochila->itemMochila[i-1].valorItem + C[i-1][w - itensMochila->itemMochila[i-1].pesoItem];
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
    return C[QtdeItens][PesoMaxCaminhao];
}
int main()
{
	int graph[][V] = { 
		{ 0, 10, 15, 20 },
		{ 10, 0, 35, 25 },
		{ 15, 35, 0, 30 },
		{ 20, 25, 30, 0 } 
	};
	int s = 0;
	
	int melhorCaminho = CaixeiroViajante(graph, s);
	printf("Melhor caminho entre as cidades A, B, C e D e: \n%d \n", melhorCaminho);
	int PesoMaxCaminhao = 20;
	
	//Guardando os trajetos e seus equivalentes pesos
	traj->trajeto[0].inicio = 'A';//1
	traj->trajeto[0].final = 'B';//2
	traj->trajeto[0].weight = bestWay[3];
	
	traj->trajeto[1].inicio = 'B';//2
	traj->trajeto[1].final = 'D';//4
	traj->trajeto[1].weight = bestWay[2];
	
	traj->trajeto[2].inicio = 'D';//4
	traj->trajeto[2].final = 'C';//3
	traj->trajeto[2].weight = bestWay[1];
	
	traj->trajeto[3].inicio = 'C';//3
	traj->trajeto[3].final = 'A';//1
	traj->trajeto[3].weight = bestWay[0];
		
		
	//Criando a mochila/entrega
	itemMoc->itemMochila[0].idItem = 1;
	itemMoc->itemMochila[0].valorItem = 3;
	itemMoc->itemMochila[0].pesoItem = 2;
	itemMoc->itemMochila[0].entrega = traj->trajeto[1].final;
	
	itemMoc->itemMochila[1].idItem = 2;
	itemMoc->itemMochila[1].valorItem = 5;
	itemMoc->itemMochila[1].pesoItem = 4;
	itemMoc->itemMochila[1].entrega = traj->trajeto[3].final;
	
	itemMoc->itemMochila[2].idItem = 3;
	itemMoc->itemMochila[2].valorItem = 8;
	itemMoc->itemMochila[2].pesoItem = 5;
	itemMoc->itemMochila[2].entrega = traj->trajeto[1].final;
	
	itemMoc->itemMochila[3].idItem = 4;
	itemMoc->itemMochila[3].valorItem = 4;
	itemMoc->itemMochila[3].pesoItem = 3;
	itemMoc->itemMochila[3].entrega = traj->trajeto[2].final;
	
	itemMoc->itemMochila[4].idItem = 5;
	itemMoc->itemMochila[4].valorItem = 10;
	itemMoc->itemMochila[4].pesoItem = 9;
	itemMoc->itemMochila[4].entrega = traj->trajeto[3].final;
	
	int valorCarga = knapsack(PesoMaxCaminhao, itemMoc);
	
	printf("Valor carga: %d \n", valorCarga);
	printf("Peso carga: %d \n", PesoMaxCaminhao);
	return 0;
}
