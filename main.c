#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

int main()
{
    BigInt *l1 = criar();

    int x;

    do
    {
        scanf("%d", &x);

        if (x < 10 && x > -10)
        {
            if (inserirInicio(l1, x))
                return 1; // se o número for de apenas um digito, ele adiciona no numero, senão ele sai
        }
    } while (x < 10 && x > -10);

    removeZero(l1);    // remove os zeros a esquerda
    converteSinal(l1); // se o primeiro numero digitado for negativo, transforma os outros digitos em negativos
    mostrar(l1);

    BigInt *l2 = criar();

    do
    {
        scanf("%d", &x);

        if (x < 10 && x > -10)
        {
            if (inserirInicio(l2, x))
                return 1; // se o número for de apenas um digito, ele adiciona no numero, senão ele sai
        }
    } while (x < 10 && x > -10);

    removeZero(l2);    // remove os zeros a esquerda
    converteSinal(l2); // se o primeiro numero digitado for negativo, transforma os outros digitos em negativos
    mostrar(l2);       // mostra o inteiro grande

    BigInt *l3 = criar();

    subtracao(l1, l2, l3);
    removeZero(l3);
    mostrar(l3);

    limpar(l1);
    limpar(l2);
    limpar(l3);

    system("pause");

    return 0;
}