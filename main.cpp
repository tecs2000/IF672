#include <bits/stdc++.h>

using namespace std;

void FRE(unordered_map<string, list<string>> &map, string &element, bool dlk_fre) {        //Recebe uma lista e o valor de um elemento
    int processosLiberados = 0, filas = 0;
    vector<string> apagar;

    for (auto &x : map) {
        auto it = find(x.second.begin(), x.second.end(), element);                  //Procura o processo na lista do recurso
        if (x.first[0] == 'R' && it != x.second.end()) apagar.push_back(x.first);   //Checa se o map na pos corrente eh um recurso
    }
    for (int i = 0; i < apagar.size(); i++) {                                       //Varre o array de chaves salvas
        auto oh = find(map[apagar[i]].begin(), map[apagar[i]].end(), element);      //Acha a posicao do processo a ser apagado
        if (oh == map[apagar[i]].begin()) {                                         //O processo esta usando o recurso
            map[apagar[i]].erase(oh);
            processosLiberados++;
            if (map[apagar[i]].size() > 0) {                                        //Se ainda houverem processos na fila do recurso
                string opa = map[apagar[i]].front();                                //Copia o atual processo usando o recurso
                auto oha = find(map[opa].begin(), map[opa].end(), apagar[i]);       //Acha a posicao do recurso a ser apagado nela
                map[opa].erase(oha);                                                //Apaga o recurso dessa fila, pois agora ele ja esta sendo usado
            }
        } else {
            map[apagar[i]].erase(oh);
            filas++;
        }
    }
    map.erase(element);                                                             //Apaga o processo do map;
    if (dlk_fre) cout << "KILL " << processosLiberados << " " << filas << endl;
    else cout << "TERM " << processosLiberados << endl;
}
bool DLK_visiting(unordered_map<string, list<string>> &map, unordered_map<string, int> &colors, string &element) {
    colors[element] = 1;                                        //Marca o no atual como cinza
    if(element[0] == 'R'){
        list<string> adjacentes = map[element].front();
    }
    else list<string> adjacentes = map[element];                //Copia a sua lista de adjacencia
    for (auto &x : adjacentes)
        if (!colors.count(x)) colors[x] = 0;                    //Seta todos os n registrados como nao visitados

    for (auto &x : adjacentes) {
        if (colors[x] == 0)  {                                  //se ainda n foi visitado...
            if (DLK_visiting(map, colors, x)) return true;
        }
        else if (colors[x] == 1) return true;                //se possuir cor cinza
    }
    colors[element] = -1;
    return false;
}
int main() {
    string comando;
    unordered_map<string, list<string>> so;

    cin >> comando;
    while (comando != "END") {
        string processo;
        cin >> processo;
        if (comando == "REQ") {
            string recurso;
            cin >> recurso;

            so[recurso].push_back(processo);
            if(so[recurso].size() == 1) cout << "AVAIL" << endl;
            else cout << "WAIT " << so[recurso].size()-1 << endl;
        } else if (comando == "FRE")
            FRE(so, processo, false);
        else {
            unordered_map<string, int> colors;
            if (DLK_visiting(so, colors, processo))
                FRE(so, processo, true);
            else cout << "NONE" << endl;
        }
        cin >> comando;
    }
    return 0;
}