#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

typedef struct no
{
    int valor;
    struct no *prox;
    struct no *ant;
} No;

typedef struct lista
{
    No *inicio;
} BigInt;

BigInt *criar()
{
    BigInt *l = (BigInt *)malloc(sizeof(BigInt));
    l->inicio = NULL;
    return l;
}

int listaVazia(BigInt *l)
{
    if (l == NULL)
        return 2;
    if (l->inicio == NULL)
        return 0;
    else
        return 1;
}

void limpar(BigInt *l)
{
    while (listaVazia(l) != 0)
        removerInicio(l);
    free(l);
    l = NULL;
}

int listaCheia(BigInt *l)
{
    return 1;
}

int tamanho(BigInt *l)
{
    if (l == NULL)
        return -1;

    No *no = l->inicio;

    int cont = 0;

    while (no != NULL)
    {
        cont++;
        no = no->prox;
    }

    return cont;
}

void mostrar(BigInt *l)
{
    if (l != NULL && listaVazia(l) != 0)
    {
        printf("[");

        No *n = l->inicio;

        while (n->prox != NULL)
        {
            n = n->prox;
        }

        printf("%d", n->valor);

        if (n->valor > 0)
        {
            while (n->ant != NULL)
            {
                n = n->ant;
                printf("%d", n->valor);
            }
        }
        else
        {
            while (n->ant != NULL)
            {
                n = n->ant;
                printf("%d", n->valor * (-1));
            }
        }

        printf("]\n");
    }
}

int inserirInicio(BigInt *l, int it)
{
    if (l == NULL)
        return 1;

    No *n = (No *)malloc(sizeof(No));

    n->valor = it;

    n->ant = NULL;
    n->prox = l->inicio;

    if (l->inicio != NULL)
    {
        l->inicio->ant = n;
    }

    l->inicio = n;

    return 0;
}

int inserirFim(BigInt *l, int it)
{
    if (l == NULL)
        return 1;
    if (listaVazia(l) == 0)
        return inserirInicio(l, it);

    No *n = (No *)malloc(sizeof(No));

    n->valor = it;

    No *t = l->inicio;

    while (t->prox != NULL)
    {
        t = t->prox;
    }

    n->ant = t;
    n->prox = NULL;
    t->prox = n;

    return 0;
}

int inserirPosicao(BigInt *l, int it, int pos)
{
    if (l == NULL)
        return 1;
    if (listaVazia(l) == 0)
        return inserirInicio(l, it);
    if (pos == 0)
        return inserirInicio(l, it);
    if (tamanho(l) <= pos)
        return inserirFim(l, it);

    No *n = (No *)malloc(sizeof(No));
    n->valor = it;

    int posicao = 0;

    No *t = l->inicio;
    while (t != NULL && posicao != pos)
    {
        posicao++;
        t = t->prox;
    }

    n->prox = t;
    n->ant = t->ant;
    t->ant->prox = n;
    t->ant = n;

    return 0;
}

int removerInicio(BigInt *l)
{
    if (l == NULL)
        return 1;
    if (listaVazia(l) == 0)
        return 2;

    No *n = l->inicio;

    l->inicio = n->prox;
    if (l->inicio != NULL)
        l->inicio->ant = NULL;

    free(n);

    return 0;
}

int removerFim(BigInt *l)
{
    if (l == NULL)
        return 1;
    if (listaVazia(l) == 0)
        return 2;
    if (tamanho(l) == 1)
        removerInicio(l);

    No *n = l->inicio;

    while (n->prox != NULL)
    {
        n = n->prox;
    }

    n->ant->prox = NULL;

    free(n);

    return 0;
}

int removerPosicao(BigInt *l, int pos)
{
    if (l == NULL)
        return 1;
    if (listaVazia(l) == 0)
        return 2;
    if (tamanho(l) == 1)
        removerInicio(l);
    if (pos == 0)
        return removerInicio(l);
    if (tamanho(l) - 1 <= pos)
        return removerFim(l);

    int posicao = 0;
    No *n = l->inicio;

    while (n->prox != NULL && pos != posicao)
    {
        n = n->prox;
        posicao++;
    }

    n->prox->ant = n->ant;
    n->ant->prox = n->prox;

    free(n);

    return 0;
}

int removerItem(BigInt *l, int it)
{
    if (l == NULL)
        return 1;
    if (listaVazia(l) == 0)
        return 2;

    int i;

    while (buscarItemChave(l, it, &i) == 0)
    {
        removerPosicao(l, i);
    }

    return 0;
}

int buscarPosicao(BigInt *l, int pos, int *retorno)
{
    if (l == NULL)
        return 1;
    if (listaVazia(l) == 0)
        return 2;
    if (pos == 0)
    {
        *retorno = l->inicio->valor;
        return 0;
    }

    int posicao = 0;
    No *n = l->inicio;

    while (n->prox != NULL && pos != posicao)
    {
        n = n->prox;
        posicao++;
    }

    if (pos == posicao)
    {
        *retorno = n->valor;
        return 0;
    }

    return 2;
}

int buscarItemChave(BigInt *l, int chave, int *retorno)
{
    if (l == NULL)
        return 1;
    if (listaVazia(l) == 0)
        return 2;

    No *n = l->inicio;

    int pos = 0;

    while (n->prox != NULL && chave != n->valor)
    {
        n = n->prox;
        pos++;
    }

    if (chave == n->valor)
    {
        *retorno = pos;
        return 0;
    }

    return 2;
}

int converteSinal(BigInt *l)
{
    if (l == NULL)
        return 1;
    if (listaVazia(l) == 0)
        return 2;

    No *n = l->inicio;

    while (n->prox != NULL)
    { // vai até o último número da lista
        n = n->prox;
    }

    if (n->valor < 0)
    { // se o digito mais significativo é negativo
        while (n != NULL)
        {
            if (n->valor > 0)
                n->valor = n->valor * (-1); // se o número é positivo, vira negativo e n passa pro anterior
            n = n->ant;
        }
    }

    return 0;
}

int removeZero(BigInt *l)
{
    if (l == NULL)
        return 1;
    if (listaVazia(l) == 0)
        return 2;

    No *n = l->inicio;

    while (n->prox != NULL)
    { // vai até o último número da lista
        n = n->prox;
    }

    while (n != NULL && tamanho(l) != 1)
    {
        if (n->valor == 0)
        { // se for zero, vai pro digito anterior e o remove
            n = n->ant;
            removerFim(l);
        }
        else
        { // se não, ele para
            return 0;
        }
    }

    return 0;
}

int soma(BigInt *l1, BigInt *l2, BigInt *l3)
{
    if (l3 == NULL)
        return 1;
    if (l1 == NULL || l2 == NULL)
        return 2;
    if (checaSinal(l1) == 1 && checaSinal(l2) == -1)
    {
        BigInt *l4 = criar();
        copia(l2, l4);
        trocaSinal(l4);
        subtracao(l1, l4, l3);
        limpar(l4);
        return 0;
    }
    if (checaSinal(l1) == -1 && checaSinal(l2) == 1)
    {
        BigInt *l4 = criar();
        copia(l1, l4);
        trocaSinal(l4);
        subtracao(l2, l4, l3);
        limpar(l4);
        return 0;
    }

    No *n = l1->inicio;
    No *m = l2->inicio;

    int s, r = 0; // s -> soma, r -> resto

    while (n != NULL && m != NULL)
    {
        s = n->valor + m->valor;
        inserirFim(l3, (s % 10) + r); // insere o primeiro dígito da soma de dois digítos da lista mais o resto da última soma

        r = s / 10; // resto da soma

        m = m->prox;
        n = n->prox;
    }

    while (n != NULL)
    {
        inserirFim(l3, n->valor + r);
        r = 0;
        n = n->prox;
    }

    while (m != NULL)
    {
        inserirFim(l3, m->valor + r);
        r = 0;
        m = m->prox;
    }

    if (n == NULL && m == NULL && r != 0)
        inserirFim(l3, r); // Se todos os digítos foram somados e ainda existe resto, insere o resto

    return 0;
}

int subtracao(BigInt *l1, BigInt *l2, BigInt *l3)
{
    if (l3 == NULL)
        return 1;
    if (l1 == NULL || l2 == NULL)
        return 2;
    
    BigInt *l4 = criar();

    if ((checaSinal(l1) == 1 && checaSinal(l2) == -1) || (checaSinal(l1) == -1 && checaSinal(l2) == 1))
    {
        copia(l2, l4);
        trocaSinal(l4);
        soma(l1, l4, l3);
        limpar(l4);
        return 0;
    }

    if (checaSinal(l1) == -1 && checaSinal(l2) == -1)
    {
        copia(l2, l4);
        trocaSinal(l4);
        BigInt *l5 = criar();
        copia(l1, l5);
        trocaSinal(l5);
        subtracao(l4, l5, l3);
        limpar(l4);
        limpar(l5);
        return 0;
    }

    printf("%d", copia(l1,l4));
    mostrar(l4);

    No *n = maior(l4, l2)->inicio; // pega o maior número
    No *m, *extra;

    int a = 0;

    if (n == l4->inicio)
        m = l2->inicio; // m pega o outro número
    else
    {
        m = l4->inicio;
        a = 1;
    }

    int s;

    while (n != NULL && m != NULL)
    {
        extra = n;
        if (n->valor >= m->valor || n->prox == NULL)
            s = n->valor - m->valor; // se o dígito for maior igual do que o dígito do subtraendo, então s é o digíto menos o outro
        else
        {
            do
            {
                extra = extra->prox; // extra vai até o primeiro dígito diferente de 0
            } while (extra->valor == 0);

            extra->valor--; // subtraí 1 dele

            while (extra->ant != n)
            { // passa pelos anteriores somando 10 e subtraindo 1 até chegar no digíto original
                extra = extra->ant;
                extra->valor = extra->valor + 9;
            }

            n->valor = n->valor + 10; // E enfim soma 10 ao digíto e efetua a subtração

            s = n->valor - m->valor;
        }

        inserirFim(l3, s); // insere a subtração
        m = m->prox;       // vai pro próximo digíto
        n = n->prox;
    }

    while (n != NULL)
    { // caso n seja maior que m, insere os digítos que faltam
        inserirFim(l3, n->valor);
        n = n->prox;
    }

    if (a)
        trocaSinal(l3); // se o maior número era o subtraendo quer dizer que a subtração foi feita "ao contrário", por isso precisamos inverter o resultado

    limpar(l4);

    return 0;
}

BigInt *maior(BigInt *l1, BigInt *l2)
{
    if (l1 != NULL && l2 != NULL)
    {
        if(checaSinal(l1) == 1 && checaSinal(l2) == -1) 
            return l1; // se l1 é positivo e l2 é negativo, l1 é maior
        if(checaSinal(l1) == -1 && checaSinal(l2) == 1) 
            return l2; // se l2 é positivo e l1 negativo, l2 é maior
        if (tamanho(l1) > tamanho(l2))
            return l1; // se o tamanho de uma das listas for maior, então essa é a lista maior
        if (tamanho(l1) < tamanho(l2))
            return l2;

        No *n = l1->inicio;
        No *m = l2->inicio;

        while (n->prox != NULL && m->prox != NULL)
        { // vai até o último digíto
            m = m->prox;
            n = n->prox;
        }

        while (n != NULL && m != NULL)
        {
            if (n->valor > m->valor)
                return l1; // Compara cada digíto até que ache um digíto maior que o outro, assim retornando a lista com o dígito maior
            if (n->valor < m->valor)
                return l2;

            n = n->ant;
            m = m->ant;
        }

        return l1; // se os números forem iguais, retorna l1
    }
}

int copia(BigInt *l1, BigInt *l2)
{
    if (l1 == NULL)
        return 1;
    if (listaVazia(l1) == 0)
        return 2;

    No *n = l1->inicio;

    while (n != NULL)
    {
        inserirFim(l2, n->valor);
        n = n->prox;
    }

    return 0;
}

int trocaSinal(BigInt *l)
{
    if (l == NULL)
        return 1;
    if (listaVazia(l) == 0)
        return 2;

    No *n = l->inicio;

    while (n != NULL)
    {
        n->valor = n->valor * (-1);
        n = n->prox;
    }

    return 0;
}

int checaSinal(BigInt *l)
{
    if (l == NULL || listaVazia(l) == 0)
        return 0;
    int n;
    buscarPosicao(l,tamanho(l) - 1, &n);
    if(n >= 0)
        return 1;
    else
        return -1;
}
