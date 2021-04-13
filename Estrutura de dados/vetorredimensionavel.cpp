#include <iostream>
using namespace std;

class vetor {
    friend class conjunto;
    public:
        vetor (); //capacidade inicial = 5
        ~vetor();
        void Inserir(int _n);
        void Remover(int _n);
        void Intercessao(vetor& _b, vetor& _c); //recebe 1 conjunto e retorna um novo, contendo a intercessao dos 2.
        int Tamanho() {return tam;}
        void Imprimir();
    private:
        int* vet;
        int capacidade;
        int tam;
        void Redimensionar(); //redimensiona o vetor caso fique cheio
        bool Existe(int _n); //verifica se o elemento existe no vetor
};

vetor::vetor () {
    this->capacidade = 5;
    this->tam = 0;
    this->vet = new int[capacidade];
}

vetor::~vetor() {
    delete[] vet;
}

void vetor::Redimensionar() {
    int* novoVetor = new int[capacidade+4];
    for(int i=0; i<tam;i++) {
        novoVetor[i]=vet[i];
    }
    delete[] vet;

    vet = new int[capacidade+4];
    for(int i=0; i<tam;i++) {
        vet[i]=novoVetor[i];
    }
    delete[] novoVetor;
    this -> capacidade += 4;
}

void vetor::Inserir(int _n) {
    if(!Existe(_n)) {
        if(tam == capacidade) {
            Redimensionar();
        }
        if(tam == 0) {
            vet[0] = _n;
        }
        else {
            vet[tam] = _n;
        }
        tam++;
    }
}

void vetor::Remover(int _n) {
    if(Existe(_n)){
        int pos;
        for (int i=0; i<tam; i++){ //acha a posição do elemento a ser removido
            if(vet[i]==_n) {
                pos = i;
            }
        }
        for (int i=pos; i<tam;i++){
            vet[i] = vet[i+1];
            vet[tam]=0;
        }
        tam--;
    }
}

void vetor::Intercessao (vetor& C1,vetor& C2) {
    for (int i=0; i<C1.Tamanho(); i++){
        for (int j=0; j<C2.Tamanho();j++) {
            if(C1.vet[i] == C2.vet[j]) {
                Inserir(C1.vet[i]);
            }
        }
    }
} 

void vetor::Imprimir() {
    for (int i=0; i<tam; i++) {
        cout << vet[i] << ' ';
    }
    cout << endl;
}

bool vetor::Existe(int _n) {
    bool retorno = false;
    for (int i=0; i<tam;i++) {
        if (vet[i]==_n) {
            retorno = true;
        }
    }
    return retorno;
}


int main() { //TESTE
    vetor vet;
    vet.Inserir(1);
    vet.Inserir(2);
    vet.Inserir(3);
    vet.Inserir(4);
    vet.Imprimir();
    vet.Remover(2);
    vet.Remover(4);
    vet.Remover(3);
    vet.Imprimir();
    vet.Inserir(6);
    vet.Inserir(7);
    vet.Inserir(8);
    vet.Imprimir();
}

