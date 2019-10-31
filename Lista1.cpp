#include <bits/stdc++.h>
using namespace std;

struct Node
{
    string valor;
    Node *next;
};
//cria o sentinela;
Node *head = NULL;

void push(string v)
{
    Node *ptr = new Node();
    ptr->valor = v;
    ptr->next = head;
    head = ptr;
}

string pop()
{
    //Nao precisamos do isempty() neste caso pois a stack nunca estara vazia
    Node *ptr = head;
    string aux;
    aux = ptr->valor;

    head = head->next;
    delete ptr;
    return aux;
}

void INF(char operador)
{
    string novaExpressao, a, b;

    if (operador == '^' || operador == 'v' || operador == '>')
    {
        a = pop();
        b = pop();
        novaExpressao = "(" + b + operador + a + ")";
        push(novaExpressao);
    }
    else // -> NEGACAO
    {
        a = pop();
        novaExpressao = "(~" + a + ")";
        push(novaExpressao);
    }
}

void VAL(char operador)
{
    bool resposta, a, b;
    if (operador == '^' || operador == 'v' || operador == '>')
    {
        a = pop()[0] == '1';
        b = pop()[0] == '1';
        //AND
        if (operador == '^')
        {
            resposta = (b && a);
            if (resposta == false)
                push("0");
            else
                push("1");
        }
            //OR
        else if (operador == 'v')
        {
            resposta = (a || b);
            if (!resposta)
                push("0");
            else
                push("1");
        }
            //IMPLICACAO
        else
        {
            if (b && !a)
                push("0");
            else
                push("1");
        }
    }
    else // -> NEGACAO
    {
        a = pop()[0] == '1';
        if (a)
            push("0");
        else
            push("1");
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int qtd;
    cin >> qtd;

    for (int i = 0; i < qtd; i++)
    {
        string comando, exp;//cmd == val ou inf //exp == exp algebrica
        cin >> comando >> exp;

        for (int j = 0; j < exp.length(); j++)
        {
            if (exp[j] == '1' || exp[j] == '0')
            {
                //Se for caractere
                string aux;
                aux = exp[j];
                push(aux);
            }
            else
            {
                if (comando.compare("INF") == 0)
                    INF(exp[j]);
                else
                    VAL(exp[j]);
            }
        }
        cout << pop() << endl;
    }
    return 0;
}