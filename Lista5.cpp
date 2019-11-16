#include <bits/stdc++.h>
#define INF 999999999
#define x first
#define y second
using namespace std;

int main(){
    int qtd_fases;
    cin >> qtd_fases;

    for(int u = 0; u < qtd_fases; u++){
        int qtd_pontos;
        cin >> qtd_pontos;

        int distancia[qtd_pontos][qtd_pontos], precursores[qtd_pontos];
        pair<int, int> pontos[qtd_pontos];                              //Guarda o ponto
        bool moedas[qtd_pontos];                                        //Guarda se tem moeda
        unordered_map <int, list<pair<int, int>>> adjacencias;          //Guarda o adjacente + peso aresta

        for(int j = 0 ; j < qtd_pontos; j++) {
            precursores[j] = -1;
            moedas[j] = false;
        }

        for(int j = 0; j < qtd_pontos; j++){
            for(int k = 0; k < qtd_pontos; k++){
                distancia[j][k] = INF;
            }
        }

        for(int j = 0; j < qtd_pontos; j++){                            //Coleta as coordenadas dos pontos
            int x, y;
            cin >> x >> y;
            pontos[j] = make_pair(x, y);
        }

        int qtd_moedas;
        cin >> qtd_moedas;
        for(int j = 0; j < qtd_moedas; j++){
            int posicao;
            cin >> posicao;
            moedas[posicao] = true;
        }

        for(int j = 0; j < qtd_pontos; j++){
            int qtd_alcancaveis;
            cin >> qtd_alcancaveis;

            for(int i = 0; i < qtd_alcancaveis; i++){
                int aux;
                cin >> aux;
                int distancia = pow((pontos[j].x - pontos[aux].x),2) + pow((pontos[j].y - pontos[aux].y),2);
                if(moedas[aux] == true)
                    adjacencias[j].push_back(make_pair(aux, -distancia));
                else
                    adjacencias[j].push_back(make_pair(aux, distancia));
            }
        }
        //INICIO DO BELLMAN-FORD
        distancia[0][0] = 0;
        for(int i = 1; i < qtd_pontos; i++){                          //Varre os vertices
            for(int p = 0; p < qtd_pontos; p++){
                distancia[i][p] = distancia[i-1][p];
            }
            for(int j = 0; j < qtd_pontos; j++){
                for(auto r: adjacencias[j]){                            //Varre a lista de adj. de cada vertice
                    if(distancia[i-1][j] + r.y < distancia[i][r.x]){
                        distancia[i][r.x] = distancia[i-1][j] + r.y;
                        precursores[r.x] = j;
                    }
                }
            }
        }
        bool stop = false;
        for(int i = 0; i < qtd_pontos && !stop; i++){               //Checa se ha loops
            for(auto r: adjacencias[i]){
                if(distancia[qtd_pontos-1][r.x] > distancia[qtd_pontos-1][i] + r.y)
                    stop = true;
            }
        }
        if(stop == false){
            vector<int> print;
            bool breka = false;

            int i = qtd_pontos-1;
            print.push_back(qtd_pontos-1);

            while(!breka){
                int toprint = precursores[i];
                print.push_back(toprint);
                i = precursores[i];

                if(i == 0)
                    breka = true;
            }
            cout << distancia[qtd_pontos-1][qtd_pontos-1] << " ";
            for(int i = print.size()-1; i >= 0; i--){
                if(i == 0) cout << print[i] << endl;
                else cout << print[i] << " ";
            }
        }
        else cout << "LOOP" << endl;
    }
    return 0;
}