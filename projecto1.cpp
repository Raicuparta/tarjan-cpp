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

int tarjanVisit(Pessoa* pessoa) {
	//cerr << "TarjanVisit - dentro\n";
	pessoa->d = pessoa->low = visitados;
	pessoa->used = true;
	visitados++;
	pilha.push(pessoa);
	//cerr << "Push\n";
	pessoa->inStack = true;
	for (int i = 0; i < pessoa->getNumeroPartilhas(); i++) {
		//cerr << "For line 66\n";
		if (!(pessoa->getPartilhas(i)->used)) {
			//cerr << "TarjanVisit FOR line 64\n";
			tarjanVisit(pessoa->getPartilhas(i));
			//cerr << "Depois   TarjanVisit\n";
			pessoa->low = min(pessoa->low, pessoa->getPartilhas(i)->low);
		}
		else if (pessoa->getPartilhas(i)->inStack) {
			//cerr << "Se ja ta na pilha\nAntes min\n";
			pessoa->low = min(pessoa->low, pessoa->getPartilhas(i)->d);
			//cerr << "Dps min\n";
		}
	}
	
	cerr << "Saiu do FOR\n";
	if (pessoa->low == pessoa->d) {
		cerr << "Sitio dos pops\n";
		
		sccs[numeroSCCs] = new Pessoa*;
		int i;
		for(i = 0; pilha.top() != pessoa; i++) {
			cerr << "ID: " << pilha.top()->getID() << "\n";
			Pessoa* p1 = pilha.top();
			pilha.pop();
			p1->inStack = false;
			cerr << "4\n";
			sccs[numeroSCCs][i] = p1;
			cerr << "5\n";
			maiorSCC = max(maiorSCC, i+1);
			cerr << "6\n";
		}
		if (pilha.top() == pessoa) {
			cerr << "ID: " << pilha.top()->getID() << "\n";
			pilha.pop();
			pessoa->inStack = false;
			cerr << "4.\n";
			sccs[numeroSCCs][i] = pessoa;
			cerr << "5.\n";
			maiorSCC = max(maiorSCC, i+1);
			cerr << "6.\n";
		}
		numeroSCCs++;
	}
	
	
	return 0;
};

int tarjanSCC(Pessoa** pessoas, int n) {
	//cerr << "TarjanSCC - dentro\n";
	for (int i = 0; i < n; i++) {
		if (!pessoas[i]->used) {
			//cerr << "Antes de tarjanVisit" << i << "\n";;
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
	
	cerr << "TarjanSCC\n";
	tarjanSCC(pessoas, n);
	
	//TESTES FIXES
	/*for (int i = 0; i < n; i++) {
		printf("Pessoa %d:\n", i+1);
		for (int j = 0; j < pessoas[i]->getNumeroPartilhas(); j++) {
			printf("-%d\n", pessoas[i]->getPartilhas(j)->getID());
		}
		
	}
	*/
	printf("\n%d SCCs\nMaior tem %d elementos\n", numeroSCCs, maiorSCC); 
}
