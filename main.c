#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

void lerNumero(BigInt *l);

int main()
{
    BigInt *l1 = criar();
    BigInt *l2 = criar();
    BigInt *l3 = criar();
    BigInt *l4 = criar();

    lerNumero(l1);
    lerNumero(l2);

    subtracao(l1, l2, l3);
    removeZero(l3);
    mostrar(l3);

    soma(l1, l2, l4);
    removeZero(l4);
    mostrar(l4);

    limpar(l1);
    limpar(l2);
    limpar(l3);
    limpar(l4);

    system("pause");

    return 0;
}

void lerNumero(BigInt *l)
{
    char input[100]; // tamanho máximo da entrada

    printf("Digite um numero:\n");
    scanf("%s", input);

    int length = strlen(input);
    for (int i = 0; i < length; i++)
    {
        int digit = input[i] - '0'; // converte o caractere para inteiro

        if (digit < 10 && digit > -10)
        {
            if (inserirInicio(l, digit))
            {
                return; // se o número for de apenas um digito, ele adiciona no numero, senão ele sai
            }
        }
    }

    removeZero(l);    // remove os zeros a esquerda
    converteSinal(l); // se o primeiro numero digitado for negativo, transforma os outros digitos em negativos
    mostrar(l);
}