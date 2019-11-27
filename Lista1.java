import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);

        int qtd = in.nextInt();

        for (int i = 0; i < qtd; i++) {
            String comando = in.next(); //Se VAL ou INF
            String exp = in.next();  //Expressao algebrica

            int tamanho = exp.length(); //Tamanho da expressao algebrica

            Pilha pilha = new Pilha(tamanho); //Inicializando a pilha

            for (int j = 0; j < exp.length(); j++) {
                if (exp.charAt(j) == '1' || exp.charAt(j) == '0') { //Se for caractere
                    String aux = "" + exp.charAt(j);
                    pilha.push(aux);

                } else {
                    if (comando.equals("INF")) pilha.INF(exp.charAt(j));
                    else pilha.VAL(exp.charAt(j));
                }
            }
            System.out.print(pilha.resultado() + "\n");
            pilha.limpar();
        }
    }
}

class Pilha {
    String[] expressao;
    int topo;
    int tamanhoP;

    public Pilha(int tamanho) {
        expressao = new String[tamanho];
        topo = -1;
        tamanhoP = tamanho;
    }

    boolean push(String a) {
        if (topo < this.tamanhoP - 1) {
            topo++;
            expressao[topo] = a;
            return true;
        }
        return false;
    }

    String pop() {
        String x = expressao[topo];
        topo--;
        return x;
    }

    String resultado() {
        return expressao[topo];
    }

    void limpar() {
        for (int i = 0; i < topo; i++) {
            pop();
        }
        topo = -1;
    }

    void INF(char operador) {
        String novaExpressao;

        if (operador == '^' || operador == 'v' || operador == '>') {
            String a = pop();
            String b = pop();
            novaExpressao = "(" + b + operador + a + ")";
            push(novaExpressao);

        } else  //NEGACAO
        {
            String a = pop();
            novaExpressao = "(" + operador + a + ")";
            push(novaExpressao);
        }
    }

    void VAL(char operador) {
        if (operador == '^' || operador == 'v' || operador == '>') {
            boolean a = pop().charAt(0) == '1';
            boolean b = pop().charAt(0) == '1';
            //AND
            if (operador == '^') {
                boolean resposta = (b && a);
                if (resposta == false) {
                    push("0");
                } else {
                    push("1");
                }
            //OR
            } else if (operador == 'v') {
                boolean resposta = (a || b);
                if (resposta == false) {
                    push("0");
                } else {
                    push("1");
                }
            }
            //IMPLICACAO
            else {
                if (b == true && a == false) {
                    push("0");
                } else if (b == true && a == true) {
                    push("1");
                } else {
                    push("1");
                }
            }
        } else  //NEGACAO
        {
            boolean a = pop().charAt(0) == '1';
            if (a) push("0");
            else {
                push("1");
            }
        }
    }
}
