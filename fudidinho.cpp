#include <iostream>
#include <stack>
#include <ctime>
#include <vector>
#include <functional>
#define M 4

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
    for(int i=0; i<M; i++){
        cartasMesa.push_back(cartas.top());
        cartas.pop();
    }
    return cartasMesa;
}

vector<Carta> distribuirCartas(stack<Carta> &cartas){
    vector<Carta> player;
    for(int i=0; i<M; i++){
        player.push_back(cartas.top());
        cartas.pop();
    }
    return player;
}

void print(stack<Carta> cartas, vector<Carta> cartasMesa, vector<Carta> cartasJogador1, vector<Carta> cartasJogador2){
    cout << "baralho randomizado:" << endl;
    while(cartas.size() > 0){
        cout << cartas.top().numero << " " << cartas.top().naipe << endl;
        int ultimo = cartas.top().numero;
        cartas.pop();
    }
    
    cout << endl << "cartas na mesa: " << endl;
    for(int i=0; i<cartasMesa.size(); i++){
        cout << cartasMesa[i].naipe << " " << cartasMesa[i].numero << endl;
    }
    cout << endl;

    for(int i=0; i<cartasJogador1.size(); i++){
        cout << "jogador 1: " << cartasJogador1[i].naipe << " " << cartasJogador1[i].numero << endl;
        cout << "jogador 2: " << cartasJogador2[i].naipe << " " << cartasJogador2[i].numero << endl;
    }
}

void menu(stack<Carta> cartas, vector<Carta> cartasMesa){
    int selecionar;
    cin >> selecionar;
    
    cout << "1- começar jogo" << endl;
    cout << "sair" << endl;
    switch (selecionar){
    case 1:
        gerarBaralho();
        gerarMesa(cartas);
        distribuirCartas(cartas);
        break;
    default:
        break;
    }
}

int main(){
    srand(time(nullptr));

    stack<Carta> cartas = gerarBaralho();
    vector<Carta> cartasMesa = gerarMesa(cartas);
    vector<Carta> cartasJogador1 = distribuirCartas(cartas);
    vector<Carta> cartasJogador2 = distribuirCartas(cartas);

    print(cartas, cartasMesa, cartasJogador1, cartasJogador2);
}