#include <bits/stdc++.h>

using namespace std;

int Dmax1 = 0, Dmax2 = 0;
int vagasIndisponiveis = 0, vagasOcupadas = 0;

int posicaoInicial(string placa, int tamanhoEsAtual) {
    int somador = 0;
    for (int i = 0; i < placa.length(); i++) {
        somador += (placa[i] - (int) 'A') * pow(26, i);
    }
    return somador % tamanhoEsAtual;
}

typedef struct carro {
    string placa = "vazio";
    int deslocamento = -1;

}carro;

struct Estacionamento1 {
    carro *realocacao(carro *parkOld, int novoTamanho, int antigoTamanho) {

        carro *newPark = new carro[novoTamanho];
        vagasOcupadas = 0;

        for(int i = 0; i < novoTamanho; i++) newPark[i] = carro();

        for (int i = 0; i < antigoTamanho; i++) {
            if (parkOld[i].placa != "vazio" && parkOld[i].placa != "off") {         //Se for uma posicao vazia ou indisponivel, n realoca
                int aux = posicaoInicial(parkOld[i].placa, novoTamanho);
                vagasOcupadas++;

                if (newPark[aux].placa == "vazio") {
                    parkOld[i].deslocamento = 0;
                    newPark[aux] = parkOld[i];

                } else {
                    parkOld[i].deslocamento = 0;
                    aux = (aux + 1) % novoTamanho;
                    while (newPark[aux].placa != "vazio") {
                        parkOld[i].deslocamento++;
                        aux = (aux + 1) % novoTamanho;
                    }
                    newPark[aux] = parkOld[i];
                }
            }
        }
        delete[] parkOld;
        return newPark;
    }

    void IN(carro *park, int tamanhoAtual, carro dirigivel) {
        int aux = posicaoInicial(dirigivel.placa, tamanhoAtual);

        if (park[aux].placa == "vazio") {
            park[aux] = dirigivel;
            cout << aux << " " << park[aux].deslocamento << " ";

        } else {
            while (park[aux].placa != "vazio") {
                dirigivel.deslocamento++;
                aux = (aux + 1) % tamanhoAtual;
            }
            park[aux] = dirigivel;
            cout << aux << " " << park[aux].deslocamento << " ";
        }
    }

    bool OUTSRC(carro *park, int tamanhoAtual, string placa, bool remocao) {
        int aux = posicaoInicial(placa, tamanhoAtual);

        int tempoBusca = 0;

        if (park[aux].placa == placa) {
            if (remocao){
                vagasIndisponiveis++;
                park[aux].placa = "off";
                cout << aux << " " << tempoBusca << " ";
                return true;
            }
            else if (tempoBusca > Dmax1) Dmax1 = tempoBusca;           //SE FOR UMA BUSCA
            cout << aux << " " << tempoBusca << " ";

        } else {
            bool stop = false;
            while (!stop) {      //JA COMECA NA PROXIMA POSICAO
                aux = (aux + 1) % tamanhoAtual;
                tempoBusca++;

                if (park[aux].placa == "vazio") {
                    cout << "-1 -1 ";
                    stop = true;

                } else if (park[aux].placa == placa) {
                    if (remocao){
                        park[aux].placa = "off";
                        vagasIndisponiveis++;
                        cout << aux << " " << tempoBusca << " ";
                        return true;
                    }
                    else if (tempoBusca > Dmax1) Dmax1 = tempoBusca;
                    cout << aux << " " << tempoBusca << " ";
                    stop = true;
                }
            }
        }
        return false;
    }
};

struct Estacionamento2 {
    carro *realocacao(carro *parkOld, int novoTamanho, int antigoTamanho) {
        carro *newPark = new carro[novoTamanho];

        for (int i = 0; i < antigoTamanho; i++) {
            if (parkOld[i].placa != "vazio" && parkOld[i].placa != "off") {
                int aux = posicaoInicial(parkOld[i].placa, novoTamanho);

                if (newPark[aux].placa == "vazio") {
                    parkOld[i].deslocamento = 0;
                    newPark[aux] = parkOld[i];

                } else {
                    parkOld[i].deslocamento = 0;

                    while (newPark[aux].placa != "vazio") {
                        if (newPark[aux].deslocamento < parkOld[i].deslocamento) {
                            carro temp = newPark[aux];
                            newPark[aux] = parkOld[i];

                            parkOld[i] = temp;
                        }
                        aux = (aux + 1) % novoTamanho;
                        parkOld[i].deslocamento++;
                    }
                    newPark[aux] = parkOld[i];
                }
            }
        }
        delete[] parkOld;
        return newPark;
    }

    void IN(carro *park, int tamanhoAtual, carro dirigivel) {
        int aux = posicaoInicial(dirigivel.placa, tamanhoAtual);

        if (park[aux].placa == "vazio") {
            park[aux] = dirigivel;
            cout << aux << " " << dirigivel.deslocamento << endl;

        } else {
            int trocas = 0;
            while (park[aux].placa != "vazio") {
                if (park[aux].placa != "off" && park[aux].deslocamento < dirigivel.deslocamento) {
                    carro temp = park[aux];
                    park[aux] = dirigivel;

                    if(trocas == 0) cout << aux << " " << dirigivel.deslocamento << endl;
                    trocas++;

                    dirigivel = temp;
                }
                aux = (aux + 1) % tamanhoAtual;
                dirigivel.deslocamento++;
            }
            park[aux] = dirigivel;
            if(trocas == 0) cout << aux << " " << dirigivel.deslocamento << endl;
        }
    }
    void OUTSRC(carro *park, int tamanhoAtual, string placa, bool remocao) {
        int aux = posicaoInicial(placa, tamanhoAtual);

        int tempoBusca = 0;

        if (park[aux].placa == placa) {
            if (remocao) park[aux].placa = "off";                         //SE FOR UMA REMOCAO
            else if (tempoBusca > Dmax1) Dmax1 = tempoBusca;
            cout << aux << " " << tempoBusca << endl;

        } else {
            bool stop = false;
            while(!stop) {      //JA COMECA NA PROXIMA POSICAO
                aux = (aux+1)%tamanhoAtual;
                tempoBusca++;

                if (park[aux].placa == "vazio") {
                    cout << "-1 -1" << endl;
                    stop = true;

                } else if (park[aux].placa == placa) {
                    if (remocao) {                                //SE FOR UMA REMOCAO
                        park[aux].placa = "off";
                    }else if (tempoBusca > Dmax2) Dmax2 = tempoBusca;
                    cout << aux << " " << tempoBusca << endl;
                    stop = true;
                }
            }
        }
    }
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int Mmin, Fmin, Fmax;
    cin >> Mmin >> Fmin >> Fmax;

    carro *park1 = new carro[Mmin];
    carro *park2 = new carro[Mmin];

    Estacionamento1 estacionamento1;
    Estacionamento2 estacionamento2;
    int m = Mmin;
    bool check = false;

    string comando, placa;
    cin >> comando;

    while (comando != "END") {
        cin >> placa;

        if (comando == "IN") {

            if (100 * vagasOcupadas  > m * Fmax)              //TAXA DE OCUPACAO
            {
                park1 = estacionamento1.realocacao(park1, m * 2, m);        //RECEBE UM NOVO ARRAY
                park2 = estacionamento2.realocacao(park2, m * 2, m);
                m *= 2;

                vagasIndisponiveis = 0;
            }
            carro novo;                                                         //CRIA UM OBJ DO TIPO CARROS
            novo.placa = placa;
            novo.deslocamento = 0;

            estacionamento1.IN(park1, m, novo);
            estacionamento2.IN(park2, m, novo);
            vagasOcupadas++;

        } else if (comando == "OUT") {
            check = estacionamento1.OUTSRC(park1, m, placa, true);
            estacionamento2.OUTSRC(park2, m , placa, true);

            if (check && m > Mmin && 100 * (vagasOcupadas-vagasIndisponiveis) < m * Fmin) {
                park1 = estacionamento1.realocacao(park1, m / 2, m);           //RECEBE UM NOVO ARRAY
                park2 = estacionamento2.realocacao(park2, m / 2, m);           //RECEBE UM NOVO ARRAY
                m /= 2;

                vagasIndisponiveis = 0;
            }
        } else {
            estacionamento1.OUTSRC(park1, m, placa, false);
            estacionamento2.OUTSRC(park2, m, placa, false);
        }
        cin >> comando;
    }
    cout << Dmax1 << " " << Dmax2 << endl;
    return 0;
}
