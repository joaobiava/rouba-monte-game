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

void print(vector<Carta> cartasMesa, vector<Carta> cartasJogador1, vector<Carta> cartasJogador2){    
    cout << endl << "cartas na mesa: " << endl;
    for(int i=0; i<cartasMesa.size(); i++){
        cout << cartasMesa[i].naipe << " " << cartasMesa[i].numero << endl;
    }
    cout << endl;

    for(int i=0; i<cartasJogador1.size() || i<cartasJogador2.size(); i++){
        cout << "jogador 1: " << cartasJogador1[i].naipe << " " << cartasJogador1[i].numero << endl;
        cout << "jogador 2: " << cartasJogador2[i].naipe << " " << cartasJogador2[i].numero << endl;
    }
}

void EscolherCarta(stack<Carta> cartas, vector<Carta> cartasMesa, vector<Carta> cartasJogador1, vector<Carta> cartasJogador2){
    int escolha, vezJogador = 0;
    bool jogadaFeita = false;

    while(!cartasJogador1.empty() || !cartasJogador2.empty()){
        if(vezJogador%2 == 0){
            for(int i=0; i<cartasJogador1.size(); i++){
                for(int i=0; i<cartasJogador1.size(); i++){
                    for(int j=0; j<cartasMesa.size(); j++){
                        if(!cartasMesa.empty() && cartasJogador1[i].numero == cartasMesa[j].numero){
                            cout << "escolha a carta da mesa que vai ser adicionada ao seu monte" << endl;
                            for(int i=0; i<cartasMesa.size(); i++){
                                cout << i << ". "<< cartasMesa[i].naipe << " " << cartasMesa[i].numero << endl;
                            }
                            cin >> escolha;

                            stack<Carta> monteJogador1;
                            monteJogador1.push(cartasMesa[escolha]);
                            cartasMesa.erase(cartasMesa.begin() + escolha);

                            cout << "escolha a carta de sua mão que vai ser adicionada no monte" << endl;
                            for(int i=0; i<cartasJogador1.size(); i++){
                                cout << i << ". "<< cartasJogador1[i].naipe << " " << cartasJogador1[i].numero << endl;
                            }
                            cin >> escolha;
                            monteJogador1.push(cartasJogador1[escolha]);
                            cartasJogador1.erase(cartasJogador1.begin() + escolha);
                            jogadaFeita = true;
                            vezJogador++;
                        }
                    }
                }
            }
            if(!jogadaFeita) {
                cout << "escolha qual das cartas colocar na mesa" << endl;
                for(int i=0; i<cartasJogador1.size(); i++){
                    cout << i << ". "<< cartasJogador1[i].naipe << " " << cartasJogador1[i].numero << endl;
                }
                cin >> escolha;
                cartasMesa.push_back(cartasJogador1[escolha]);
                cartasJogador1.erase(cartasJogador1.begin() + escolha);
                vezJogador++;
            }
        }
        else{
            jogadaFeita=false;
            for(int i=0; i<cartasJogador2.size(); i++){
                for(int j=0; i<cartasMesa.size(); j++){
                    if(!cartasMesa.empty() && cartasJogador2[i].numero == cartasMesa[j].numero){
                        print(cartasMesa, cartasJogador1, cartasJogador2);
                        cout << "escolha a carta para ser adicionada ao seu monte" << endl;
                        for(int i=0; i<cartasMesa.size(); i++){
                            cout << i << ". " << cartasMesa[i].naipe << " " << cartasMesa[i].numero << endl;
                        }
                        cin >> escolha;

                        stack<Carta> monteJogador2;
                        monteJogador2.push(cartasMesa[escolha]);
                        cartasMesa.erase(cartasMesa.begin() + escolha);

                        cout << "escolha a carta que sera adicionada do seu monte" << endl;
                        for(int i=0; i<cartasJogador2.size(); i++){
                            cout << i << ". " << cartasJogador2[i].naipe << " " << cartasJogador2[i].numero << endl;
                        }
                        cin >> escolha;
                        monteJogador2.push(cartasJogador2[escolha]);
                        cartasJogador2.erase(cartasJogador2.begin() + escolha);
                        jogadaFeita=true;
                        vezJogador++;
                    }
                }
            }
            if(!jogadaFeita){
                cout << "escolha qual das cartas colocar na mesa" << endl;
                for(int i=0; i<cartasJogador2.size(); i++){
                    cout << i << ". " << cartasJogador2[i].naipe << " " << cartasJogador2[i].numero << endl;
                }
                cin >> escolha;
                cartasMesa.push_back(cartasJogador2[escolha]);
                cartasJogador1.erase(cartasJogador2.begin() + escolha);
                vezJogador++;
            }
        }
    }
}

void menu(stack<Carta> cartas, vector<Carta> cartasMesa, vector<Carta> cartasJogador1, vector<Carta> cartasJogador2){
    int selecionar;
    cout << "1- comecar jogo" << endl;
    cout << "3- sair" << endl;
    cin >> selecionar;

    switch (selecionar){
    case 1:
        print(cartasMesa, cartasJogador1, cartasJogador2);
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