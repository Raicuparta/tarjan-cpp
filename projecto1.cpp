#include <stdio.h>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Pessoa {

public:
	vector<Pessoa*> partilhas;
	int d;
	int low;
	int scc;
	bool used;
	bool inStack;

	Pessoa() {
		used = false;
		inStack = false;
		d = -1;
		low = -1;
		scc = -1;
	}
};

int visitados = 0;
stack<Pessoa*> pilha;
vector<vector<Pessoa*> > sccs;
vector<Pessoa*> pessoas;
int numeroSCCs = 0;
int maiorSCC = 0;
int sccsArcosFora = 0;



int tarjanVisit(Pessoa* pessoa) {
	pessoa->d = pessoa->low = visitados;
	pessoa->used = true;
	visitados++;
	pilha.push(pessoa);
	pessoa->inStack = true;
	for (int i = 0; i < (int)pessoa->partilhas.size(); i++) {
		if (!(pessoa->partilhas[i]->used)) {
			tarjanVisit(pessoa->partilhas[i]);
			pessoa->low = min(pessoa->low, pessoa->partilhas[i]->low);
		}
		else if (pessoa->partilhas[i]->inStack) {
			pessoa->low = min(pessoa->low, pessoa->partilhas[i]->d);
		}
	}

	if (pessoa->low == pessoa->d) {

		int i = 0;
		vector<Pessoa*> currentScc;
		for(i = 0; pilha.top() != pessoa; i++) {
			Pessoa* p1 = pilha.top();
			pilha.pop();
			p1->inStack = false;
			currentScc.push_back(p1);
			p1->scc = numeroSCCs;
			maiorSCC = max(maiorSCC, i+1);
		}
		if (pilha.top() == pessoa) {
			pilha.pop();
			pessoa->inStack = false;
			currentScc.push_back(pessoa);
			pessoa->scc = numeroSCCs;
			maiorSCC = max(maiorSCC, i+1);
		}
		sccs.push_back(currentScc);
		
		bool temArcosParaFora = false;
		for(int j = 0; j <= i && !temArcosParaFora; j++) {
			for(int k = 0; k < (int)sccs[numeroSCCs][j]->partilhas.size() && !temArcosParaFora; k++) {
				if( (sccs[numeroSCCs][j]->scc) != (sccs[numeroSCCs][j]->partilhas[k]->scc)) {
					sccsArcosFora++;
					temArcosParaFora = true;
				}
			}
		}
		
		numeroSCCs++;
	}


	return 0;
};

int tarjanSCC(int n) {
	for (int i = 0; i < n; i++) {
		if (!pessoas[i]->used) {
			tarjanVisit(pessoas[i]);
		}
	}
	return 0;
};

int main(){

	int n, p;

	scanf("%d %d", &n, &p);

	for (int i = 0; i < n; i++) {
		pessoas.push_back(new Pessoa);
	}

	int pess1, pess2;
	for (int i = 0; i < p; i++) {
		scanf("%d %d", &pess1, &pess2);
		pess1--;
		pess2--;
		pessoas[pess1]->partilhas.push_back(pessoas[pess2]);
	}

	tarjanSCC(n);

	//TESTES FIXES
	/*for (int i = 0; i < n; i++) {
		printf("Pessoa %d:\n", i+1);
		for (int j = 0; j < (int)pessoas[i]->partilhas.size(); j++) {
			printf("-%d\n", pessoas[i]->partilhas[j]->getID());
		}
		
	}*/
	
	printf("%d\n%d\n%d\n", numeroSCCs, maiorSCC, numeroSCCs - sccsArcosFora); 
}
