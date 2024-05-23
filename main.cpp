#include <iostream>
#include <stack>
#include <ctime>
#include <vector>
#define M 4

using namespace std;

struct Carta
{
    string naipe;
    int numero;
};

stack<Carta> gerarBaralho(){
    // vetor que posteriormente serão alocadas as cartas
    vector<int> pos = {};
    for (int i = 0; i < 52; i++){
        pos.push_back(i);
    }

    string naipes[4] = {"ouros", "espadas", "copas", "paus"};
    stack<Carta> baralho;
    // gera todas as cartas
    for (int i = 1; i <= 13; i++){
        for (string naipe : naipes){
            Carta carta;
            carta.naipe = naipe;
            carta.numero = i;
            baralho.push(carta);
        }
    }

    vector<Carta> embaralhar(52);
    for (int i = 0; i < 52; i++){
        int num = rand() % pos.size();
        embaralhar[pos[num]] = baralho.top();
        baralho.pop();
        pos.erase(pos.begin() + num);
    }

    for (Carta carta : embaralhar){
        baralho.push(carta);
    }

    return baralho;
}

vector<Carta> gerarMesa(stack<Carta> &baralho){
    vector<Carta> cartasMesa;
    for (int i = 0; i < M; i++){
        cartasMesa.push_back(baralho.top());
        baralho.pop();
    }
    return cartasMesa;
}

vector<Carta> distribuirCartas(stack<Carta> &baralho){
    vector<Carta> player;
    for (int i = 0; i < M; i++){
        if(baralho.empty()){
            cout << "baralho acabou" << endl;
            break;
        }
        else{
            player.push_back(baralho.top());
            baralho.pop();
        }
    }
    return player;
}

void print(vector<Carta> &cartasMesa, vector<Carta> &cartasJogador1, vector<Carta> &cartasJogador2){
    cout << endl << "--------------------------------------" << endl;

    cout << "Cartas na Mesa: " << endl;
    for (Carta &carta : cartasMesa){
        cout << carta.naipe << " " << carta.numero << endl;
    }

    cout << "Cartas do Jogador 1: " << endl;
    for (Carta &carta : cartasJogador1){
        cout << carta.naipe << " " << carta.numero << endl;
    }

    cout << "Cartas do Jogador 2: " << endl;
    for (Carta &carta : cartasJogador2){
        cout << carta.naipe << " " << carta.numero << endl;
    }

    cout << "--------------------------------------" << endl;
}

void jogada(vector<Carta> &cartasJogador, vector<Carta> &cartasMesa, stack<Carta> &monteJogador){
    int escolha;
    bool jogadaFeita = false;

    for (int i = 0; i < cartasJogador.size(); ++i){
        for (int j = 0; j < cartasMesa.size(); ++j){
            if (cartasJogador[i].numero == cartasMesa[j].numero){
                cout << "Escolha a carta da mesa que vai ser adicionada ao seu monte" << endl;
                for (int k = 0; k < cartasMesa.size(); ++k){
                    cout << k << ". " << cartasMesa[k].naipe << " " << cartasMesa[k].numero << endl;
                }
                cin >> escolha;

                monteJogador.push(cartasMesa[escolha]);
                cartasMesa.erase(cartasMesa.begin() + escolha);

                cout << "Escolha a carta de sua mao que vai ser adicionada no monte" << endl;
                for (int k = 0; k < cartasJogador.size(); ++k){
                    cout << k << ". " << cartasJogador[k].naipe << " " << cartasJogador[k].numero << endl;
                }
                cin >> escolha;

                monteJogador.push(cartasJogador[escolha]);
                cartasJogador.erase(cartasJogador.begin() + escolha);

                jogadaFeita = true;
                break;
            }
        }
    }

    if (!jogadaFeita){
        cout << "Escolha qual das cartas colocar na mesa" << endl;
        for (int i = 0; i < cartasJogador.size(); ++i){
            cout << i << ". " << cartasJogador[i].naipe << " " << cartasJogador[i].numero << endl;
        }
        cin >> escolha;

        cartasMesa.push_back(cartasJogador[escolha]);
        cartasJogador.erase(cartasJogador.begin() + escolha);
    }
}

void vencedor(stack<Carta> monteJogador1, stack<Carta> monteJogador2);

void vezJogadores(vector<Carta> &cartasJogador1, vector<Carta> &cartasMesa, stack<Carta> &baralho, vector<Carta> &cartasJogador2){
    stack<Carta> monteJogador1;
    stack<Carta> monteJogador2;
    int n = 0;

    while (!cartasJogador1.empty() || !cartasJogador2.empty() || !baralho.empty()){

        if (n % 2 == 0){
            if(cartasJogador1.empty() && !baralho.empty()){
                cartasJogador1 = distribuirCartas(baralho);
            }
            if(!cartasJogador1.empty()){
                jogada(cartasJogador1, cartasMesa, monteJogador1);
            }
        } else{
            if(cartasJogador2.empty() && !baralho.empty()){
                cartasJogador2 = distribuirCartas(baralho);
            }
            if(!cartasJogador2.empty()){
                jogada(cartasJogador2, cartasMesa, monteJogador2);
            }
        }
        
        n++;
        print(cartasMesa, cartasJogador1, cartasJogador2); // Para ver o estado após cada jogada

    }
    vencedor(monteJogador1, monteJogador2);
}

void vencedor(stack<Carta> monteJogador1, stack<Carta> monteJogador2){
    int cont1 = 0, cont2 = 0;

    while(!monteJogador1.empty()){
        monteJogador1.pop();
        cont1++;
    }
    while(!monteJogador2.empty()){
        monteJogador2.pop();
        cont2++;
    }

    cout << "o monte do jogador 1 possui: " << cont1 << endl;
    cout << "o monte do jogador 2 possui: " << cont2 << endl;

    if(cont1 == cont2){
        cout << "Empate" << endl;
    } else if (cont1 > cont2) {
        cout << "jogador 1 venceu o jogo com: " << cont1 << " cartas" << endl;
    } else {
        cout << "jogador 2 venceu o jogo com: " << cont2 << " cartas" << endl;
    }
}

bool menu(stack<Carta> baralho, vector<Carta> cartasMesa, vector<Carta> cartasJogador1, vector<Carta> cartasJogador2){
    int selecionar;
    cout << "1- comecar jogo" << endl;
    cout << "2- sair" << endl;
    cin >> selecionar;

    switch (selecionar){
    case 1:
        print(cartasMesa, cartasJogador1, cartasJogador2);
        cout << endl;
        vezJogadores(cartasJogador1, cartasMesa, baralho, cartasJogador2);
        break;
    case 2:
        return false;
    default:
        break;
    }
    return true;
}

int main(){
    srand(time(nullptr));

    stack<Carta> baralho;
    vector<Carta> cartasMesa;
    baralho = gerarBaralho();
    cartasMesa = gerarMesa(baralho);
    vector<Carta> cartasJogador1 = distribuirCartas(baralho);
    vector<Carta> cartasJogador2 = distribuirCartas(baralho);

    while (menu(baralho, cartasMesa, cartasJogador1, cartasJogador2)) {}
}