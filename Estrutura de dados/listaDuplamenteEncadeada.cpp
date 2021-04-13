#include <iostream>
using namespace std;

class Noh {
	friend class Lista;
	public:
	Noh (int _dado) {
		valor = _dado;
		proximo = NULL;
		anterior = NULL;
	}
	private:
	Noh* proximo;
	Noh* anterior;
	int valor;
};

class Lista {
	private:
		Noh* primeiro;
		Noh* ultimo;
		int tamanho;
	public:
		Lista();
		~Lista();
		void Insere(int _dado);
		void Remove();
		void Inverte();
		void Imprime();
		void ImprimeInverso();
		bool Vazia();
};

Lista::Lista() {
	primeiro = NULL;
	ultimo = NULL;
	tamanho = 0;
}

Lista::~Lista() {
	while(!Vazia()) {
		Remove();
	}
}

bool Lista::Vazia() {
	if (tamanho == 0) {
		return true;
	}
	else {
		return false;
	}
}

void Lista::Insere(int _dado) {
	Noh* novoNoh = new Noh(_dado);
	if (Vazia()) {
		primeiro = novoNoh;
		ultimo = novoNoh;
	}
	else {
		novoNoh->anterior = ultimo;
		ultimo->proximo = novoNoh;
		ultimo = novoNoh;
	}
	tamanho++;
}

void Lista::Remove() {
	Noh* aux = ultimo;
	ultimo = ultimo -> anterior;
	delete aux;
	ultimo -> proximo = NULL;
	tamanho--;
}

void Lista::Imprime() {
	Noh* aux = primeiro;
	while (aux != NULL) {
		cout << aux->valor << " ";
		aux = aux-> proximo;
	}
	cout << endl;
}


void Lista::Inverte() {
	Noh* aux = primeiro;
	while (aux != NULL) {
		Noh* auxProx = aux -> proximo;
		aux -> proximo = aux -> anterior;
		aux -> anterior = auxProx;
		aux = auxProx;
	}
	Noh* exUltimo = ultimo;
	ultimo = primeiro;
	primeiro = exUltimo;
} 

int main() { //TESTE
	Lista lista;
	int val;
	while (val != -1) {
		cin >> val;
		if (val != -1) {
			lista.Insere(val);
		}
	}
	lista.Inverte();
	lista.Imprime();
}
	



