#include <iostream>
using namespace std;

class noh {
friend class pilha;
public:
	noh(int valor);
private:
    int dado; // poderia ser outro tipo de variavel
    noh* prox;
};

noh::noh(int valor) {
	dado = valor;
	prox = NULL;
}

// pilha dinamicamente encadeada
class pilha {
private:
    noh* topo;
    int tamanho;

public:
    pilha();
    ~pilha();
    void empilha(int d);
    int desempilha(); // retorna o topo da pilha
    int espia() { return topo -> dado;} // espia o topo da pilha
    bool vazia();
    void limpaPilha(); //limpa a pilha
    void imprime(); //função para teste
};


pilha::pilha() {
	topo = NULL;
	tamanho = 0;
}

pilha::~pilha() {
	limpaPilha();
}

void pilha::limpaPilha() {
	while (!vazia()) {
		desempilha();
	}
}

void pilha::empilha (int d) {
	noh* novoNoh = new noh(d);
	if (topo == NULL) {
		topo = novoNoh;
	}
	else {
		novoNoh->prox = topo;
		topo = novoNoh;
	}
	tamanho++;
}

int pilha::desempilha() {
	if (topo == NULL) {
		return -1;
	}
	else {
		int retorno = topo -> dado;
		noh* aux = topo;
		topo = aux -> prox;
		delete aux;
		tamanho --;
		return retorno;
	}
}

bool pilha:: vazia() {
	if (tamanho == 0) {
		return true;
	}
	else {
		return false;
	}
}

void pilha::imprime() {
    noh* aux = topo;
    while(aux != NULL) {
        cout << aux->dado << " ";
        aux = aux->prox;
    }
    cout << endl;
}

int main() { //TESTE
    pilha p1;
    p1.empilha(1);
    p1.empilha(2);
    p1.empilha(3);
    p1.imprime();
    p1.desempilha();
    p1.desempilha();
    p1.imprime();
}