#include <iostream>
#include <vector>
#include <stack>
#include <ctime>
using namespace std;

stack<string> gerarBaralho(){

    vector<int> pos = {};
    for(int i=0; i<52; i++){
        pos.push_back(i);
    }

    stack<string> cartas;
    string naipes[4] = {"ouros","espadas","paus","copas"};
    for(int i=1; i<=13; i++){
        for(string naipe: naipes){
            cartas.push(naipe + to_string(i));
        }
    }

    vector<string> cartasEmbaralhadas(52);
    for(int i=0; i<52; i++){
        int num = rand() % (pos.size());
        cartasEmbaralhadas[pos[num]] = cartas.top();
        cartas.pop();
        pos.erase(pos.begin() + num);
    }

    for(string carta: cartasEmbaralhadas){
        cartas.push(carta);
    }

    return cartas;
}

int main(){
    srand(time(NULL));

    stack<string> cartas = gerarBaralho();
    while(cartas.size() > 0){
        cout << cartas.top() << endl;
        cartas.pop();
    }

    return 0;
}