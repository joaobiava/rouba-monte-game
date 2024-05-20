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

stack<Carta> gerarBaralho()
{
    // vetor que posteriormente serão alocadas as cartas
    vector<int> pos = {};
    for (int i = 0; i < 52; i++)
    {
        pos.push_back(i);
    }

    string naipes[4] = {"ouros", "espadas", "copas", "paus"};
    stack<Carta> cartas;
    // gera todas as cartas
    for (int i = 1; i <= 13; i++)
    {
        for (string naipe : naipes)
        {
            Carta carta;
            carta.naipe = naipe;
            carta.numero = i;
            cartas.push(carta);
        }
    }

    vector<Carta> embaralhar(52);
    for (int i = 0; i < 52; i++)
    {
        int num = rand() % pos.size();
        embaralhar[pos[num]] = cartas.top();
        cartas.pop();
        pos.erase(pos.begin() + num);
    }

    for (Carta carta : embaralhar)
    {
        cartas.push(carta);
    }

    return cartas;
}

vector<Carta> gerarMesa(stack<Carta> &cartas)
{
    vector<Carta> cartasMesa;
    for (int i = 0; i < M; i++)
    {
        cartasMesa.push_back(cartas.top());
        cartas.pop();
    }
    return cartasMesa;
}

vector<Carta> distribuirCartas(stack<Carta> &cartas)
{
    vector<Carta> player;
    for (int i = 0; i < M; i++)
    {
        player.push_back(cartas.top());
        cartas.pop();
    }
    return player;
}

void print(stack<Carta> &cartas, vector<Carta> &cartasMesa, vector<Carta> &cartasJogador1, vector<Carta> &cartasJogador2)
{
    cout << "Cartas na Mesa: " << endl;
    for (const auto &carta : cartasMesa)
    {
        cout << carta.naipe << " " << carta.numero << endl;
    }
    cout << "Cartas do Jogador 1: " << endl;
    for (const auto &carta : cartasJogador1)
    {
        cout << carta.naipe << " " << carta.numero << endl;
    }
    cout << "Cartas do Jogador 2: " << endl;
    for (const auto &carta : cartasJogador2)
    {
        cout << carta.naipe << " " << carta.numero << endl;
    }
    cout << endl;
}

void jogada(vector<Carta> &cartasJogador, vector<Carta> &cartasMesa, stack<Carta> &cartas, stack<Carta> &monteJogador)
{
    int escolha;
    bool jogadaFeita = false;

    for (int i = 0; i < cartasJogador.size(); ++i)
    {
        for (int j = 0; j < cartasMesa.size(); ++j)
        {
            if (cartasJogador[i].numero == cartasMesa[j].numero)
            {
                cout << "Escolha a carta da mesa que vai ser adicionada ao seu monte" << endl;
                for (int k = 0; k < cartasMesa.size(); ++k)
                {
                    cout << k << ". " << cartasMesa[k].naipe << " " << cartasMesa[k].numero << endl;
                }
                cin >> escolha;

                monteJogador.push(cartasMesa[escolha]);
                cartasMesa.erase(cartasMesa.begin() + escolha);

                cout << "Escolha a carta de sua mão que vai ser adicionada no monte" << endl;
                for (int k = 0; k < cartasJogador.size(); ++k)
                {
                    cout << k << ". " << cartasJogador[k].naipe << " " << cartasJogador[k].numero << endl;
                }
                cin >> escolha;

                monteJogador.push(cartasJogador[escolha]);
                cartasJogador.erase(cartasJogador.begin() + escolha);

                jogadaFeita = true;
                break;
            }
        }
        if (jogadaFeita)
            break;
    }

    if (!jogadaFeita)
    {
        cout << "Escolha qual das cartas colocar na mesa" << endl;
        for (int i = 0; i < cartasJogador.size(); ++i)
        {
            cout << i << ". " << cartasJogador[i].naipe << " " << cartasJogador[i].numero << endl;
        }
        cin >> escolha;

        cartasMesa.push_back(cartasJogador[escolha]);
        cartasJogador.erase(cartasJogador.begin() + escolha);
    }
}

void vezJogadores(vector<Carta> &cartasJogador1, vector<Carta> &cartasMesa, stack<Carta> &cartas, vector<Carta> &cartasJogador2)
{
    stack<Carta> monteJogador1;
    stack<Carta> monteJogador2;
    int n = 0;

    while (!cartasJogador1.empty() || !cartasJogador2.empty() || cartas.empty())
    {
        if (n % 2 == 0)
        {
            jogada(cartasJogador1, cartasMesa, cartas, monteJogador1);
        }
        else
        {
            jogada(cartasJogador2, cartasMesa, cartas, monteJogador2);
        }
        n++;
        print(cartas, cartasMesa, cartasJogador1, cartasJogador2); // Para ver o estado após cada jogada
    }
    cartasJogador1 = distribuirCartas(cartas);
    cartasJogador2 = distribuirCartas(cartas);
    vezJogadores(cartasJogador1, cartasMesa, cartas, cartasJogador2);
}

void menu(stack<Carta> cartas, vector<Carta> cartasMesa, vector<Carta> cartasJogador1, vector<Carta> cartasJogador2)
{
    int selecionar;
    cout << "1- comecar jogo" << endl;
    cout << "3- sair" << endl;
    cin >> selecionar;

    switch (selecionar)
    {
    case 1:
        print(cartas, cartasMesa, cartasJogador1, cartasJogador2);
        cout << endl;
        vezJogadores(cartasJogador1, cartasMesa, cartas, cartasJogador2);
        break;
    default:
        break;
    }
}

int main()
{
    srand(time(nullptr));

    stack<Carta> cartas;
    vector<Carta> cartasMesa;
    cartas = gerarBaralho();
    cartasMesa = gerarMesa(cartas);
    vector<Carta> cartasJogador1 = distribuirCartas(cartas);
    vector<Carta> cartasJogador2 = distribuirCartas(cartas);

    while (true)
    {
        menu(cartas, cartasMesa, cartasJogador1, cartasJogador2);
    }
}