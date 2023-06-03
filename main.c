#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "lista.h"

void lerNumero(BigInt *l);
void menu();
int multiplicacaoSimples(BigInt *l1, int m, BigInt *l3);
int multiplicacao(BigInt *l1, BigInt *l2, BigInt *l3);

int main() {
    BigInt *l1 = criar();
    BigInt *l2 = criar();
    BigInt *l3;

    printf(" ________________________\n");
    printf("|                        |\n");
    printf("|       CALCULADORA      |\n");
    printf("|________________________|\n\n");

    lerNumero(l1);
    lerNumero(l2);
    sleep(1);

    char op;


    do{
        if(listaVazia(l1) == 0 || listaVazia(l2) == 0){
            printf("Erro!");
            break;
        }

        l3 = criar();
        system("cls");
        setbuf(stdin, NULL);

        menu();
        scanf("%c", &op);

        sleep(1);
        system("cls");

        switch (op)
        {
        case '1':
            lerNumero(l1);
            lerNumero(l2);
            sleep(1);
            break;
        case '2':
            printf("Primeiro operando: ");
            mostrar(l1);
            printf("\nSegundo operando: ");
            mostrar(l2);
            break;
        case '3':
            l3 = maior(l1,l2);
            printf("Maior operando: ");
            mostrar(l3);
            l3 = NULL;
            break;
        case  '4':
            l3 = maior(l1,l2);
            printf("Menor operando: ");
            if(l3 == l1) mostrar(l2);
            else mostrar(l1);
            l3 = NULL;
            break;
        case '5':
            printf("Ate mais!...");
            sleep(1);
            break;
        case '+':
            soma(l1, l2, l3);
            mostrar(l1);
            printf(" + ");
            mostrar(l2);
            printf(" = ");
            mostrar(l3);
            limpar(l3);
            break;
        case '-':
            subtracao(l1, l2, l3);
            mostrar(l1);
            printf(" - ");
            mostrar(l2);
            printf(" = ");
            mostrar(l3);
            limpar(l3);
            break;
        case '*':
            multiplicacao(l1, l2, l3);
            mostrar(l1);
            printf(" * ");
            mostrar(l2);
            printf(" = ");
            mostrar(l3);
            limpar(l3);
            break;
        default:
            break;
        }

        printf("\n");
        system("pause");
    }while(op != '5');

    limpar(l1);
    limpar(l2);
    limpar(l3);

    return 0;
}

void menu(){
    printf(" ________________________\n");
    printf("|                        |\n");
    printf("|          MENU          |\n");
    printf("|________________________|\n\n");
    printf("\n1 - Inserir novos operandos\n");
    printf("2 - Checar operandos atuais\n");
    printf("3 - Imprimir maior operando\n");
    printf("4 - Imprimir menor operando\n");
    printf("5 - Sair\n");
    printf("Digite simbolos aritmeticos para efetuar operacao(+,-,*,/)\n");
    printf("Opcao: ");
}

void lerNumero(BigInt *l) {
    char input[100]; // tamanho máximo da entrada

    printf("\nDigite um numero:\n");
    scanf("%s", input);

    int length = strlen(input);
    for (int i = 0; i < length; i++)
    {
        if (i == 0 && input[i] == '-') // se o primeiro caractere for um sinal de negativo, ele ignora
        {
            continue;
        }
        int digit = input[i] - '0'; // converte o caractere para inteiro

        if (i == 1 && input[0] == '-') // se o primeiro caractere for um sinal de negativo, ele transforma o digito em negativo
        {
            digit *= -1;
        }

        if (inserirInicio(l, digit))
        {
            return; // se o número for de apenas um digito, ele adiciona no numero, senão ele sai
        }
    }

    removeZero(l);    // remove os zeros a esquerda
    converteSinal(l); // se o primeiro numero digitado for negativo, transforma os outros digitos em negativos
    mostrar(l);
}

int multiplicacaoSimples(BigInt *l1, int m, BigInt *l2){
    if(l1 == NULL || l2 == NULL) return 1;
    if(listaVazia(l1) == 0) return 2;
    if(m == 1){
        copia(l1,l2);
        return 0;
    }
    if(m == 0){
        inserirFim(l2, 0);
        return 0;
    }

    int p, n, carry = 0, i = 0;

    while(i < tamanho(l1)){
        buscarPosicao(l1, i, &n);
        p = (n * m)  + carry;
        inserirFim(l2,(p%10));
        carry = p/10;
        i++;
    }

    if(carry) inserirFim(l2, carry);

    return 0;
}


int multiplicacao(BigInt *l1, BigInt *l2, BigInt *l3){
     if (l3 == NULL || l1 == NULL || l2 == NULL)
        return 1;

    BigInt *temp = criar();
    BigInt *soma_temp = criar();

    int zeros = 0;
    int i = 0;
    int m;

    while(i < tamanho(l2)){
        while(listaVazia(soma_temp) != 0) removerInicio(soma_temp);
        copia(l3,soma_temp);
        while(listaVazia(l3) != 0) removerInicio(l3);
        while(listaVazia(temp) != 0) removerInicio(temp);

        for(int j = 0; j < zeros; j++){
            inserirFim(temp,0);
        }

        buscarPosicao(l2,i,&m);

        multiplicacaoSimples(l1,m,temp);
        soma(soma_temp,temp,l3);

        i++;
        zeros++;
    }

    limpar(temp);
    limpar(soma_temp);

    return 0;
}