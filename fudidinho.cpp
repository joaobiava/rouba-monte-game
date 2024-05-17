#include <iostream>
#include <stack>
#include <ctime>
#include <vector>
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

void EscolherCarta(stack<Carta> cartas, vector<Carta> cartasMesa, vector<Carta> cartasJogador1, vector<Carta> cartasJogador2){
    int i=0, j=0;
    int vezJogador = 1;
    int escolha;

    if(vezJogador%2 != 0){
        while(i<cartasMesa.size()){
            if(true || false){
                print(cartas, cartasMesa, cartasJogador1, cartasJogador2);
                cout << "escolha a carta para ser adicionada ao seu monte" << endl;
                cin >> escolha;
                stack<Carta> monteJogador1;
                monteJogador1.push(cartasMesa[escolha]);
                monteJogador1.push(cartasJogador1[escolha]);
                cartasJogador1.erase(cartasJogador1.begin() + escolha);
                cartasMesa.erase(cartasMesa.begin() + escolha);
            }
            else if(i == cartasMesa.size() - 1){
                cout << "escolha qual das cartas colocar na mesa" << endl;
                //mostras as opcoes possiveis
                for(int i=0; i<cartasJogador1.size(); i++){
                    cout << cartasJogador1[i].naipe << " " << cartasJogador1[i].numero << endl;
                }
                cin >> escolha;
                cartasMesa.push_back(cartasJogador1[escolha]);
                cartasJogador1.erase(cartasJogador1.begin() + escolha);
            }
            i++;
            vezJogador++;
        }
    }
    else{
        while(j<cartasMesa.size()){
            int escolha;
            if(cartasJogador2[i].numero == cartasMesa[i].numero){
                print(cartas, cartasMesa, cartasJogador1, cartasJogador2);
                cout << "escolha a carta para ser adicionada ao seu monte" << endl;
                cin >> escolha;
                stack<Carta> monteJogador2;
                monteJogador2.push(cartasMesa[escolha]);
                monteJogador2.push(cartasJogador2[escolha]);
                cartasJogador2.erase(cartasJogador2.begin() + escolha);
                cartasMesa.erase(cartasMesa.begin() + escolha);
            }
            else if(i == cartasMesa.size() - 1){
                cout << "escolha qual das cartas colocar na mesa" << endl;
                //mostras as opcoes possiveis
                for(int i=0; i<cartasJogador2.size(); i++){
                    cout << cartasJogador2[i].naipe << " " << cartasJogador2[i].numero << endl;
                }
                cin >> escolha;
                cartasMesa.push_back(cartasJogador2[escolha]);
                cartasJogador1.erase(cartasJogador2.begin() + escolha);
            }
            j++;
            vezJogador++;
        }
    }
    print(cartas, cartasMesa, cartasJogador1, cartasJogador2);
}

void menu(stack<Carta> cartas, vector<Carta> cartasMesa, vector<Carta> cartasJogador1, vector<Carta> cartasJogador2){
    int selecionar;
    cout << "1- começar jogo" << endl;
    cout << "2- printar" << endl;
    cout << "sair" << endl;
    cin >> selecionar;

    switch (selecionar){
    case 1:
        cartasJogador1 = distribuirCartas(cartas);
        cartasJogador2 = distribuirCartas(cartas);
        break;
    case 2:
        print(cartas, cartasMesa, cartasJogador1, cartasJogador2);
        cout << endl;
        EscolherCarta(cartas, cartasMesa, cartasJogador1, cartasJogador2);
        break;
    default:
        break;
    }
}

int main(){
    srand(time(nullptr));

    stack<Carta> cartas;
    vector<Carta> cartasMesa;
    cartas = gerarBaralho();
    cartasMesa = gerarMesa(cartas);
    vector<Carta> cartasJogador1 = distribuirCartas(cartas);
    vector<Carta> cartasJogador2 = distribuirCartas(cartas);
    
    while(true){
        menu(cartas, cartasMesa, cartasJogador1, cartasJogador2);
    }
}