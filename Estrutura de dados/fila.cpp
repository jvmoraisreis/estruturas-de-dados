#include <iostream>
using namespace std;

class Noh {
	friend class Fila;
	public:
		Noh (int dado);
	private:
		int valor;
		Noh* proximo;
};

Noh::Noh (int dado) {
	valor = dado;
	proximo = NULL;
}

class Fila {
	private:
		int tamanho;
		Noh* primeiro;
		Noh* ultimo;
	public:
		Fila ();
		~Fila();
		bool Vazia ();
		void Insere (int dado);
		int Remove ();
};

Fila::Fila () {
	primeiro = NULL;
	ultimo = NULL;
	tamanho = 0;
}

Fila::~Fila () {
	while (!Vazia()) {
		Remove();
	}
}

bool Fila::Vazia () {
	if (tamanho == 0) {
		return true;
	}
	else {
		return false;
	}
}

void Fila::Insere (int dado) {
	Noh* NovoNoh = new Noh (dado);
	if (Vazia()) {
		primeiro = NovoNoh;
		ultimo = NovoNoh;
		tamanho++;
	}
	else {
		ultimo -> proximo = NovoNoh;
		ultimo = NovoNoh;
		tamanho++;
	}
}

int Fila::Remove () {
	int retorno;
	if (Vazia()) {
		cout << "Fila Vazia!" << endl;
		return -1;
	}
	else {
		retorno = primeiro -> valor;
		Noh* aux = primeiro;
		primeiro = primeiro -> proximo;
		delete aux;
		tamanho--;
		return retorno;
	}
}

int main() { //TESTE
	Fila fila;
	int dado;
	int n;
	cin >> n;
	for (int i=0; i<n; i++) {
		cin >> dado;
		fila.Insere (dado);
	}
	
	for (int i=0; i<n; i++) {
		cout << fila.Remove() << " ";
	}
}
 
	
	
	
	
