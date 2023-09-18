#include <algorithm>

using namespace std;
// defino os maiores valores de n e s como 1010
#define MAXN 1010
#define MAXS 1010

// declaro as vari�veis que a fun��o utiliza
int n, valor[MAXN], peso[MAXN], tab[MAXN][MAXS]

int knapsack(int obj, int aguenta){
	
	// se j� calculamos esse estado da dp, retornamos o resultado salvo
	if(tab[obj][aguenta] >= 0) return tab[obj][aguenta];
	
	// se n�o houver mais objetos ou espa�o na mochila, retorno 0, pois n�o posso mais botar nada
	if(obj == n or !aguenta) return tab[obj][aguenta] = 0;
	
	// n�o colocar avan�a para o estado em que tentmos o pr�ximo, com o mesmo espa�o dispon�vel
	int nao_coloca = knapsack(obj + 1, aguenta);
	
	// se for poss�vel colocar o objeto
	if(peso[obj] <= aguenta){
		
		// o melhor ating�vel � o valor dele mais o melhor entre colocar ou n�o os pr�ximos
		// que � o resultado do estado da dp em que olhamos o pr�ximo objeto
		// mas agora a mochila aguenta o que aguentava antes menos o peso que coloquei nela
		int coloca = valor[obj] + knapsack(obj + 1, aguenta - peso[obj]);
		
		// e a fun��o deve retornar o melhor entre colocar ou n�o colocar
		return tab[obj][aguenta] = max(coloca, nao_coloca);
	}
	
	// se a fun��o n�o retornou ainda, ent�o ela n�o entrou no if
	// logo n�o era poss�vel colocar o objeto 
	return tab[obj][aguenta] = nao_coloca; // ent�o retorno o valor de n�o coloc�-lo
}
