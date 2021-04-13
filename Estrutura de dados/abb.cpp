#include <iostream>
using namespace std;

class Noh {
	friend class ABB;
	private:
		Noh* esquerdo;
		Noh* direito;
		Noh* pai;
		int valor;
		int nivel;
	public:
		Noh(int _d) {
			pai = NULL;
			esquerdo = NULL;
			direito = NULL;
			valor = _d;
			nivel = -1;
		}
};

class ABB {
	private:
		Noh* raiz;
		Noh* InserirRecursivo(Noh* umNoh, int _d);
		Noh* Buscar(int _d);
		//auxiliares na remoção
		void Transplantar(Noh* antigo, Noh* novo); 
		Noh* Minimo(Noh* umNoh);
	public:
		ABB();
		void Remover(int _d);
		void BuscarAux(int _d);
		void Depurar();
		bool Inserir (int _d); //inserção interativa
		void InserirAux(int _d); // para chamar a função privada de inserção recursiva
};

ABB::ABB() {
	raiz = NULL;
}

void ABB::BuscarAux(int _d) {
	Buscar(_d);
}

Noh* ABB::Buscar(int _d) {
	Noh* percorre = raiz;
	while (percorre != NULL) {
		if (percorre -> valor == _d) {
			return percorre;   // retorna o ponteiro para o nó encontrado
		}
		else if (percorre->valor < _d) {
			percorre = percorre -> direito;
		}
		else if (percorre -> valor > _d) {
			percorre = percorre -> esquerdo;
		}
	}
	return NULL;
}

void ABB::InserirAux(int _d) {
	raiz = InserirRecursivo(raiz,_d);
}

Noh* ABB::InserirRecursivo(Noh* umNoh, int _d) {
	if (umNoh == NULL) {
		Noh* novoNoh = new Noh(_d);
		return novoNoh;
	}
	else {
		// se não for uma folha nula, checa a inserção a esquerda e a direita.
		if (_d > umNoh -> valor ) {
			umNoh -> direito = InserirRecursivo(umNoh->direito, _d);
			//acerta o nó pai
			umNoh -> direito -> pai = umNoh;
		}
		else {
			umNoh -> esquerdo = InserirRecursivo(umNoh->esquerdo, _d);
			//acerta o nó pai
			umNoh -> esquerdo -> pai = umNoh;
		}
	}
	return umNoh;
}

bool ABB::Inserir (int _d){
	Noh* novoNoh = new Noh (_d);
	if (raiz == NULL) {
		raiz = novoNoh;
		return true;
	}
	else {
		Noh* percorre = raiz;
		while(percorre != NULL) {
		if (_d > percorre-> valor){
			if (percorre ->direito != NULL) {
				percorre = percorre -> direito;
			}
			else {
				novoNoh -> pai = percorre;
				percorre -> direito = novoNoh;
				return true;
			}
		}
		if (_d < percorre-> valor){
			if (percorre -> esquerdo != NULL) {
				percorre = percorre -> esquerdo;
			}
			else {
				novoNoh -> pai = percorre;
				percorre -> esquerdo = novoNoh;
				return true;
			}
		}
	}
	}
	return false;
}

//funções auxiliares para remoção
void ABB::Transplantar(Noh* antigo, Noh* novo) {
	//pega o pai do antigo e faz ser pai do novo  
	
	if (antigo == raiz) {
		raiz = novo;
	}
	else if (antigo == antigo -> pai -> esquerdo) {
		antigo -> pai -> esquerdo = novo;
	}
	else {
		antigo -> pai -> direito = novo;
	}
	if (novo != NULL) {
		novo -> pai = antigo -> pai;
	}
}

Noh* ABB:: Minimo(Noh* umNoh) {
	while (umNoh -> esquerdo != NULL) {
		umNoh = umNoh -> esquerdo;
	}
	return umNoh;
}
 
void ABB::Remover(int _d) {
	Noh* aRemover = Buscar(_d);
	if (aRemover == NULL) {
		cerr << "Item não encontrado :^(" << endl;
	}
	else if(aRemover -> esquerdo == NULL) {
		Transplantar(aRemover,aRemover -> direito);
	}
	else if(aRemover -> direito == NULL) {
		Transplantar(aRemover,aRemover -> esquerdo);
	}
	else { //tem dois filhos!
		//podemos trocar pelo antecessor ou pelo sucessor 
		Noh* sucessor = Minimo(aRemover -> direito);
		if(sucessor -> pai != aRemover) { //tratamento para caso o sucessor possua filho direito
			Transplantar(sucessor,sucessor->direito);
			sucessor->direito = aRemover -> direito;
			sucessor -> direito -> pai= sucessor;
		}
		Transplantar(aRemover,sucessor);
		//tratamento com o filho do nó removido
		sucessor -> esquerdo = aRemover-> esquerdo;
		sucessor -> esquerdo -> pai = sucessor;
	}
	// ponnteiros ajustados, o nó pode ser deletado.
	delete aRemover;
}

void ABB::Depurar() {
	Noh* aux = raiz;
	while(aux != NULL) {
		cout << aux-> valor << " ";
		aux= aux->esquerdo;
	}
	cout << endl;
}

int main() { //TESTE
	ABB teste;
	teste.InserirAux(5);
	teste.InserirAux(4);
	teste.InserirAux(3);
	teste.InserirAux(2);
	teste.InserirAux(1);
	teste.Remover(5);
	teste.Remover(2);
	teste.Remover(1);
	teste.Depurar();
}
