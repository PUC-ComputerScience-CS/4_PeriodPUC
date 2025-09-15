#include "analex.h"
#include "pilha.h"
#include <string.h>

int token;
char pos_fixa[50]; //armazena todos os caracteres(dig e operadores) da not. pos-fixa

void S();
void E();
void T();
void F();
void E_linha();
void T_linha();

void erro_sintatico(){
    printf("\nERRO SINTATICO NA LINHA %d\n\n", linha);
    exit(2);
}

void consome(int t){
    if(t == token)
        token = analex();
    else
        erro_sintatico();
}

void analise_posFixa(char *caracter){
    strcat(pos_fixa, caracter); //strcat -> concatena as strings anexando uma ao final da outra (ex; s=jor t = ge com o strcat ficaria jorge :D)
    strcat(pos_fixa, " ");
}

void analisa_digito(int n){
    char buf[40];
    sprintf(buf, "%d", n); // de acordo com a documentação da IBM (https://www.ibm.com/docs/pt-br/i/7.6.0?topic=functions-sprintf-print-formatted-data-buffer) o sprintf  formata e armazwna uma serie de caracteres e valores na matriz buffer
    analise_posFixa(buf);
}

void S(){
    E();
    if(token != ';'){
        erro_sintatico();
    }
    //printf("\nTopo da pilha: %d", topo());
    int c = pop();
    printf("\nEXPRESSAO CORRETA!\n");
    printf("NOTACAO POS-FIXA: %s\n", pos_fixa);
    printf("RESULTADO DA EXPRESSAO: %d.\n\n", c);
}

void E(){
    T();
    E_linha();
}

void E_linha(){
    if(token == '+'){
        consome('+');
        T();
        //faz o calculo usando a pilha | SOMA
        int a = pop();
        int b = pop();
        int c = b + a;
        push(c);
        analise_posFixa("+");
        E_linha();
    }else if(token == '-'){
        consome('-');
        T();
        //SUB
        int a = pop();
        int b = pop();
        int c = b - a;
        push(c);
        analise_posFixa("-");
        E_linha();
    }
}

void T(){
    F();
    T_linha();
}

void T_linha(){
    if(token == '*'){
        consome('*');
        F();
        //MULT
        int a = pop();
        int b = pop();
        int c = b * a;
        push(c);
        analise_posFixa("*");
        T_linha();
    }else if(token == '/'){
        consome('/');
        F();
        //DIV
        int a = pop();
        int b = pop();
        if(a == 0){
            printf("ERRO: DIVISAO POR ZERO NA LINHA %d", linha);
            exit(0);
        }
        int c = b / a;
        push(c);
        analise_posFixa("/");
        T_linha();
    }
}

void F(){
    if(token == NUM){
        push(numero);
        analisa_digito(numero);
        consome(NUM);
    }
    else if(token == ID){
        analise_posFixa("id");
        consome(ID);
    }
       
    else if(token == '('){
        consome('(');
        E();
        consome(')');
    }else
        erro_sintatico();
}

int main(){
    token = analex();
    S();
    // if(token != ';'){ || movi o if do main para a função S() para que identificasse tokens extras e não resolvesse as expressões antes de verificar se token!= ';'. Como no caso do exemplo "(2+3)) + 1;".
    //     erro_sintatico();
    // }
}