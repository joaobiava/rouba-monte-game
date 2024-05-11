#include <iostream>
#include <stack>
#include <ctime>
#include <vector>

using namespace std;

struct Carta{
    string naipe;
    int numero;
};

stack<Carta> gerarBaralho(){
    //vetor que posteriormente serão alocadas as cartas
    vector<int> pos = {};
    for(int i=0; i<52; i++){
        pos.push_back(i);
    }

    string naipes[4] = {"ouros", "espadas", "copas", "paus"};
    stack<Carta> cartas;
    //gera todas as cartas
    for(int i=1; i<=13; i++){
        for(string naipe: naipes){
            Carta carta;
            carta.naipe = naipe;
            carta.numero = i;
            cartas.push(carta);
        }
    }

    vector<Carta> embaralhar(52);
    for(int i = 0; i < 52; i++){
        int num = rand() % pos.size();
        embaralhar[pos[num]] = cartas.top();
        cartas.pop();
        pos.erase(pos.begin() + num);
    }

    for(Carta carta: embaralhar){
        cartas.push(carta);
    }



    return cartas;
}

vector<Carta> gerarMesa(stack<Carta> &cartas){
    vector<Carta> cartasMesa;
    for(int i=0; i<4; i++){
        cartasMesa.push_back(cartas.top());
        cartas.pop();
    }
    return cartasMesa;
}

int main(){
    srand(time(nullptr));

    stack<Carta> cartas = gerarBaralho();
    vector<Carta> cartasMesa = gerarMesa(cartas);//colocado aqui para não dar o pop antes do print

    while(cartas.size() > 0){
        cout << cartas.top().numero << " " << cartas.top().naipe << endl;
        int ultimo = cartas.top().numero;
        cartas.pop();
    }

    cout << endl;
    for(int i=0; i<cartasMesa.size(); i++){
        cout << cartasMesa[i].naipe << " " << cartasMesa[i].numero << endl;
    }
}