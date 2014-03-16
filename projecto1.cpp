#include <stdio.h>
#include <iostream>
#include <stack>

using namespace std;

class Pessoa {
private:
	Pessoa** _partilhas;
	int _numeroPartilhas;
	int _id;

public:
	int d;
	int low;
	int scc;
	bool used;
	bool inStack;

	Pessoa() {
		_partilhas = new Pessoa*;
		_id = 0;
		_numeroPartilhas = 0;
		used = false;
		inStack = false;
		d = -1;
		low = -1;
		scc = -1;
	}

	Pessoa* getPartilhas(int i) {
		return _partilhas[i];
	}

	int getNumeroPartilhas() {
		return _numeroPartilhas;
	}

	void addPartilha(Pessoa* p){
		_partilhas[_numeroPartilhas++] = p;
	}

	int getID() {
		return _id + 1;
	}

	void setID(int id) {
		_id = id;
	}

};

int visitados = 0;
stack<Pessoa*> pilha;
Pessoa*** sccs = new Pessoa**;
int numeroSCCs = 0;
int maiorSCC = 0;
int sccsArcosFora = 0;

int tarjanVisit(Pessoa* pessoa) {
	pessoa->d = pessoa->low = visitados;
	pessoa->used = true;
	visitados++;
	pilha.push(pessoa);
	pessoa->inStack = true;
	for (int i = 0; i < pessoa->getNumeroPartilhas(); i++) {
		if (!(pessoa->getPartilhas(i)->used)) {
			tarjanVisit(pessoa->getPartilhas(i));
			pessoa->low = min(pessoa->low, pessoa->getPartilhas(i)->low);
		}
		else if (pessoa->getPartilhas(i)->inStack) {
			pessoa->low = min(pessoa->low, pessoa->getPartilhas(i)->d);
		}
	}

	if (pessoa->low == pessoa->d) {

		sccs[numeroSCCs] = new Pessoa*;
		int i = 0;
		for(i = 0; pilha.top() != pessoa; i++) {
			Pessoa* p1 = pilha.top();
			pilha.pop();
			p1->inStack = false;
			sccs[numeroSCCs][i] = p1;
			p1->scc = numeroSCCs;
			maiorSCC = max(maiorSCC, i+1);
		}
		if (pilha.top() == pessoa) {
			pilha.pop();
			pessoa->inStack = false;
			sccs[numeroSCCs][i] = pessoa;
			pessoa->scc = numeroSCCs;
			maiorSCC = max(maiorSCC, i+1);
		}
		
		bool temArcosParaFora = false;
		for(int j = 0; j <= i && !temArcosParaFora; j++) {
			for(int k = 0; k < sccs[numeroSCCs][j]->getNumeroPartilhas() && !temArcosParaFora; k++) {
				if( (sccs[numeroSCCs][j]->scc) != (sccs[numeroSCCs][j]->getPartilhas(k)->scc)) {
					sccsArcosFora++;
					temArcosParaFora = true;
				}
			}
		}
		
		numeroSCCs++;
	}


	return 0;
};

int tarjanSCC(Pessoa** pessoas, int n) {
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

	Pessoa** pessoas = new Pessoa*[n];
	for (int i = 0; i < n; i++) {
		pessoas[i] = new Pessoa;
		pessoas[i]->setID(i);
	}

	int pess1, pess2;
	for (int i = 0; i < p; i++) {
		scanf("%d %d", &pess1, &pess2);
		pess1--;
		pess2--;
		pessoas[pess1]->addPartilha(pessoas[pess2]);		
	}

	tarjanSCC(pessoas, n);

	//TESTES FIXES
	/*for (int i = 0; i < n; i++) {
		printf("Pessoa %d:\n", i+1);
		for (int j = 0; j < pessoas[i]->getNumeroPartilhas(); j++) {
			printf("-%d\n", pessoas[i]->getPartilhas(j)->getID());
		}
		
	}
	*/
	printf("%d\n%d\n%d\n", numeroSCCs, maiorSCC, numeroSCCs - sccsArcosFora); 
}
