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


	Pessoa() {
		_partilhas = new Pessoa*;
		_id = 0;
		_numeroPartilhas = 0;
		used = false;
	}

	Pessoa** getPartilhas() {
		return _partilhas;
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
stack<Pessoa> pilha;

int tarjanVisit(Pessoa pessoa) {
	pessoa.d = pessoa.low = visitados;
	visitados++;
	pilha.push(pessoa);
	
	
	return 0;
};

int tarjanSCC(Pessoa* pessoas, int n) {
	for (int i = 0; i < n; i++) {
		if (!pessoas[i].used) {
			tarjanVisit(pessoas[i]);
		}
	}
	return 0;
};

int main(){
		
	int n, p;
	
	scanf("%d %d", &n, &p);
	
	Pessoa* pessoas = new Pessoa[n];
	for (int i = 0; i < n; i++) {
		pessoas[i].setID(i);
	}
	
	int pess1, pess2;
	for (int i = 0; i < p; i++) {
		scanf("%d %d", &pess1, &pess2);
		pess1--;
		pess2--;
		pessoas[pess1].addPartilha(&pessoas[pess2]);		
	}
	
	
	//TESTES FIXES
	for (int i = 0; i < n; i++) {
		printf("Pessoa %d:\n", i+1);
		for (int j = 0; j < pessoas[i].getNumeroPartilhas(); j++) {
			printf("-%d\n", pessoas[i].getPartilhas()[j]->getID());
		}
	}
	
}
