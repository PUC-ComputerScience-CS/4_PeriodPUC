#include <stdio.h>
#include <stdlib.h>

#define ID 256
#define NUM 257

int linha = 1;
int numero = 0;

void erro_lexico(){
    printf("\nERRO LEXICO NA LINHA %d\n\n", linha);
    exit(0);
}

int analex(){
    int num;
    char c;

    do{
        c = getchar(); 
        if(c=='\n')
            linha++; 
    }while(c == '\n'|| c == ' ' || c == '\t');

    if(c == '+' || c == '-' ||c == '*' ||c == '/' ||c == '(' ||c == ')' || c == ';')
        return c;
    
    if(c >= '0' && c <= '9'){
       num = 0;
       while(c >= '0' && c <= '9'){
        num = num * 10 + (c - '0'); //substrai o numero em ascii do caracter c com o char 0 (48)_ pra q tenha o numero do caracter como expoente
        c = getchar();
       }
        ungetc(c, stdin); // devolve o caractere que não faz parte do número
        numero = num;
        return NUM;
    }      

    if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')){
        // char id[20];
        // int i = 0; 
        // while((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')){
        //     id[i++] = c;
        //     c = getchar();
        // }
        // id[i] = '\0'; //termina a string depois do while pra terminar o id
        ungetc(c, stdin);
        return ID; 
    }   
    erro_lexico();
    
    return 0;
}

// int main(){
//       int token, conta = 0;

//       printf("\nDigite o caracter a ser identificado: ");
//        while(token != ';'){
//           token = analex();
//           conta++;
//       }
//       printf("\nTokens totais: %d", conta);
//       printf("\nLinhas totais(main): %d", linha);

//      return 0;
// }