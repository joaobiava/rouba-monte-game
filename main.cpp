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

int particao(vector<Carta> &cartasMesa, int min, int max) {
    int pivo = cartasMesa[max].numero;
    int i = (min - 1);

    for (int j = min; j < max; j++){
        if (cartasMesa[j].numero < pivo){
            i++;
            swap(cartasMesa[i], cartasMesa[j]);
        }
    }
    swap(cartasMesa[i + 1], cartasMesa[max]);
    return (i + 1);
}

void quicksort(vector<Carta> &cartasMesa, int min, int max) {
    if (min < max) {
        int pivo = particao(cartasMesa, min, max);
        quicksort(cartasMesa, min, pivo - 1);
        quicksort(cartasMesa, pivo + 1, max);
    }
}

void print(vector<Carta> &cartasMesa, vector<Carta> &cartasDoJogador, stack<Carta> monteDoJogador){
    system("cls");
    cout << endl << "--------------------------------------" << endl;

    cout << "Cartas na Mesa: " << endl;
    quicksort(cartasMesa, 0, cartasMesa.size() - 1);
    for (Carta &carta : cartasMesa){
        cout << carta.naipe << " " << carta.numero << endl;
    }

    quicksort(cartasDoJogador, 0, cartasDoJogador.size() - 1);
    cout << endl << "Cartas do Jogador: " << endl;
    for (Carta &carta : cartasDoJogador){
        cout << carta.naipe << " " << carta.numero << endl;
    }

    if(!monteDoJogador.empty()){
        cout << endl << "o topo do jogador oponente possui a carta: " << monteDoJogador.top().naipe << " " << monteDoJogador.top().numero << endl;
    }
    else{
        cout << endl <<"o monte do oponente esta vazio, nao tem nada para roubar T-T" << endl;
    }

    cout << "--------------------------------------" << endl;
}

void jogada(vector<Carta> &cartasJogador, vector<Carta> &cartasMesa, stack<Carta> &monteJogador){
    int escolha;
    bool jogadaFeita = false;
    vector<int> opcoesValidas;

    for (int i = 0; i < cartasJogador.size(); ++i){
        for (int j = 0; j < cartasMesa.size(); ++j){
            if ((cartasJogador[i].numero == cartasMesa[j].numero) && !jogadaFeita){
                opcoesValidas.push_back(i);
            }
        }
    }

    if(!opcoesValidas.empty()){
        cout << "Escolha a carta de sua mao para pegar uma carta da mesa:" << endl;
        for (int i = 0; i < opcoesValidas.size(); ++i) {
            cout << i << ". " << cartasJogador[opcoesValidas[i]].naipe << " " << cartasJogador[opcoesValidas[i]].numero << endl;
        }
        cin >> escolha;

        while(escolha > opcoesValidas.size()){
            cin >> escolha;
        }
        
        int indiceEscolhido = opcoesValidas[escolha];
        int numeroEscolhido = cartasJogador[indiceEscolhido].numero;

        for (int j = 0; j < cartasMesa.size(); ++j) {
            if (cartasMesa[j].numero == numeroEscolhido) {
                monteJogador.push(cartasMesa[j]);
                cartasMesa.erase(cartasMesa.begin() + j);
                break;
            }
        }

        monteJogador.push(cartasJogador[indiceEscolhido]);
        cartasJogador.erase(cartasJogador.begin() + indiceEscolhido);
    } else{
        cout << "Nao ha jogadas validas. Escolha uma carta para colocar na mesa:" << endl;
        for (int i = 0; i < cartasJogador.size(); ++i) {
            cout << i << ". " << cartasJogador[i].naipe << " " << cartasJogador[i].numero << endl;
        }
        cin >> escolha;

        cartasMesa.push_back(cartasJogador[escolha]);
        cartasJogador.erase(cartasJogador.begin() + escolha);
    }
}

bool roubarMonte(vector<Carta> &cartasJogador, stack<Carta> &monteJogadorOponente, stack<Carta> &monteJogadorAtual){
    int escolha;

    if(monteJogadorOponente.empty()){
        return false;
    }

    for(int i=0; i<cartasJogador.size(); i++){
        if(cartasJogador[i].numero == monteJogadorOponente.top().numero){
            cout << "quer sacanear seu amigo?" << endl;
            cout << "1- sim, estou atras da vitoria, nao de uma amizade" << endl;
            cout << "2- tadinho dele" << endl;
            cin >> escolha;
            if(escolha == 1){
                stack<Carta> aux;
                while(!monteJogadorOponente.empty()){
                    aux.push(monteJogadorOponente.top());
                    monteJogadorOponente.pop();
                    monteJogadorAtual.push(aux.top());
                    aux.pop();
                }
                return true;
            }
            else{
                return false;
            }
        }
    }
    return false;
}

void vencedor(stack<Carta> monteJogador1, stack<Carta> monteJogador2);

void vezJogadores(vector<Carta> &cartasJogador1, vector<Carta> &cartasMesa, stack<Carta> &baralho, vector<Carta> &cartasJogador2){
    stack<Carta> monteJogador1;
    stack<Carta> monteJogador2;
    int n = 0;
    bool jogadaFeita = false;

    while (!cartasJogador1.empty() || !cartasJogador2.empty() || !baralho.empty()){

        if (n % 2 == 0){
            if(cartasJogador1.empty() && !baralho.empty()){
                cartasJogador1 = distribuirCartas(baralho);
            }
            print(cartasMesa, cartasJogador1, monteJogador2);
            if(!cartasJogador1.empty()){
                cout << "vez do jogador 1:" << endl;
                jogadaFeita = roubarMonte(cartasJogador1, monteJogador2, monteJogador1);
                if(!jogadaFeita){
                    jogada(cartasJogador1, cartasMesa, monteJogador1);
                }
            }
        } else{
            if(cartasJogador2.empty() && !baralho.empty()){
                cartasJogador2 = distribuirCartas(baralho);
            }
            print(cartasMesa, cartasJogador2, monteJogador1);
            if(!cartasJogador2.empty()){
                cout << "vez do jogador 2" << endl;
                jogadaFeita = roubarMonte(cartasJogador2, monteJogador1, monteJogador2);

                if(!jogadaFeita){
                    jogada(cartasJogador2, cartasMesa, monteJogador2);
                }
            }
        }
        n++;
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