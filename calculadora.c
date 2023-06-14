#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "lista.h"

void lerNumero(BigInt *l);
void menu();
int multiplicacaoSimples(BigInt *l1, int m, BigInt *l3);
int multiplicacao(BigInt *l1, BigInt *l2, BigInt *l3);
int divisao(BigInt *l1, BigInt *l2, BigInt  *l3);
int resto(BigInt *l1, BigInt *l2, BigInt  *l3);
int fatorial(BigInt *l1, BigInt *l2);
int potencia(BigInt *l1, BigInt *l2, BigInt *l3);

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
        l3 = criar();
        system("cls");
        setbuf(stdin, NULL);

        if(listaVazia(l1) == 0 || listaVazia(l2) == 0){
            printf("Erro!");
            sleep(1);
            break;
        }

        menu();
        scanf("%c", &op);

        sleep(1);
        system("cls");

        switch (op)
        {
        case '1':
            while(listaVazia(l1) != 0) removerInicio(l1);
            while(listaVazia(l2) != 0) removerInicio(l2);
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
        case  '5':
            do
            {
                setbuf(stdin, NULL);
                printf("Inverter:\n(1).Operando 1\n(2).Operando 2\nOpcao: ");
                scanf("%c", &op);
                if(op == '1') {
                    trocaSinal(l1);
                    mostrar(l1);
                } else if(op == '2') {
                    trocaSinal(l2);
                    mostrar(l2);
                }
                    
                if(op != '1' && op != '2'){
                    printf("Opcao invalida!");
                    sleep(1);
                    system("cls");
                }
            } while (op != '1' && op != '2');
            break;
        case '7':
            printf("Ate mais!...");
            break;
        case '6':
            if(potencia(l1,l2,l3) == 0){
                mostrar(l1);
                printf("^");
                mostrar(l2);
                printf(" = ");
                mostrar(l3);                
            } else 
                printf("Erro!");
            limpar(l3);
            break;
        case '!':
            do
            {
                setbuf(stdin, NULL);
                printf("Fatorial do:\n(1).Operando 1\n(2).Operando 2\nOpcao: ");
                scanf("%c", &op);
                if(op == '1') {
                    if(fatorial(l1,l3) == 0){
                        mostrar(l1);
                        printf("! = ");
                        mostrar(l3);                
                    } else 
                        printf("Erro!");
                } else if(op == '2') {
                    if(fatorial(l2,l3) == 0){
                        mostrar(l2);
                        printf("! = ");
                        mostrar(l3);                
                    } else 
                        printf("Erro!");
                }
                if(op != '1' && op != '2'){
                    printf("Opcao invalida!");
                    sleep(1);
                    system("cls");
                }
            } while (op != '1' && op != '2');
            limpar(l3);
            break;
        case '+':
            if(soma(l1, l2, l3) == 0){
                mostrar(l1);
                printf(" + ");
                mostrar(l2);
                printf(" = ");
                mostrar(l3);
                
            } else
                printf("Erro!");
            limpar(l3);
            break;
        case '-':
            if(subtracao(l1, l2, l3) == 0){
                removeZero(l3);
                mostrar(l1);
                printf(" - ");
                mostrar(l2);
                printf(" = ");
                mostrar(l3);
                
            } else
                printf("Erro!");
            limpar(l3);
            break;
        case '*':
            if(multiplicacao(l1, l2, l3) == 0){
                mostrar(l1);
                printf(" * ");
                mostrar(l2);
                printf(" = ");
                mostrar(l3);
            } else 
                printf("Erro!");
            limpar(l3);
            break;
        case '/':
            if(divisao(l1, l2, l3) == 0){
                mostrar(l1);
                printf(" / ");
                mostrar(l2);
                printf(" = ");
                mostrar(l3);
            } else
                printf("Erro!");
            limpar(l3);
            break;
        case '%':
            if(resto(l1, l2, l3) == 0){                
                mostrar(l1);
                printf(" %% ");
                mostrar(l2);
                printf(" = ");
                mostrar(l3);
            } else 
                printf("Erro!");
            limpar(l3);
            break;
        default:
            printf("Opcao invalida");
            break;
        }

        printf("\n");
        system("pause");
    }while(op != '7');

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
    printf("5 - Inverte o sinal de um operando\n");
    printf("6 - Potencia de n1 elevado a n2\n");
    printf("7 - Sair\n");
    printf("Digite simbolos aritmeticos para efetuar operacao(+,-,*,/,%%)\n");
    printf("! - fatorial do primeiro numero\n");
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
        //se o número for multiplicado por 1, o produto é ele mesmo 
        copia(l1,l2);
        return 0;
    }
    if(m == 0){
        //se o número for multiplicado por 0, o produto é 0
        inserirFim(l2, 0);
        return 0;
    }

    int p, //produto
    n,     //dígito do primeiro fator
    carry = 0,
    i = 0; //posição do dígito

    while(i < tamanho(l1)){
        buscarPosicao(l1, i, &n); //pega o dígito na posição i
        p = (n * m)  + carry;     //produto é o dígito vezes o segundo fator mais o carry
        inserirFim(l2,(p%10));    //insere o primeiro dígito do resultado na lista
        carry = p/10;             //o resto do resultado fica como carry
        i++;                      //vai pro próximo digito até a posição ser igual ao tamanho do primeiro fator
    }

    if(carry) inserirFim(l2, carry);

    return 0;
}


int multiplicacao(BigInt *l1, BigInt *l2, BigInt *l3){
    if (l3 == NULL || l1 == NULL || l2 == NULL)
        return 1;
    if (listaVazia(l1) == 0 || listaVazia(l2) == 0)
        return 2;

    BigInt *temp = criar();
    BigInt *soma_temp = criar();

    int zeros = 0,
    i = 0,          //posicao do dígito do segundo fator
    m;              //dígito do segundo fator

    while(i < tamanho(l2)){
        while(listaVazia(soma_temp) != 0) removerInicio(soma_temp);     //limpa o número que estava em soma_temp
        copia(l3,soma_temp);                                            //coloca o produto de l3 de volta pra soma_temp
        while(listaVazia(l3) != 0) removerInicio(l3);                   //limpa l3
        while(listaVazia(temp) != 0) removerInicio(temp);               //limpa o produto da multiplicaoSimples

        for(int j = 0; j < zeros; j++){
            inserirFim(temp,0); //insere zeros de acordo com o dígito do segundo fator
        }

        buscarPosicao(l2,i,&m); //pega o dígito do segundo fator de acordo com a posição i, isso continua até que i seja igual ao tamanho do segundo fator

        multiplicacaoSimples(l1,m,temp); //multiplica o primeiro fator pelo dígito
        soma(soma_temp,temp,l3);         //soma esse resultado com o produto que temos até então e coloca em l3

        i++;        //vai pro próximo dígito
        zeros++;    //aumenta o número de zeros
    }

    limpar(temp);
    limpar(soma_temp);

    return 0;
}

int divisao(BigInt *l1, BigInt *l2, BigInt  *l3){
    if (l3 == NULL || l1 == NULL || l2 == NULL)
        return 1;
    if (listaVazia(l1) == 0 || listaVazia(l2) == 0)
        return 2;

    int n, m;

    buscarPosicao(l2,tamanho(l2) - 1,&n);

    if(n == 0)      //se o denominador é 0, retorna 3
        return 3;

    if (checaSinal(l1) == -1 && checaSinal(l2) == -1)
    {
        BigInt *l4 = criar();
        copia(l2, l4);
        trocaSinal(l4);
        BigInt *l5 = criar();
        copia(l1, l5);
        trocaSinal(l5);
        divisao(l4, l5, l3);
        limpar(l4);
        limpar(l5);
        return 0;
    }
    if (checaSinal(l1) == 1 && checaSinal(l2) == -1)
    {
        BigInt *l4 = criar();
        copia(l2, l4);
        trocaSinal(l4);
        divisao(l1, l4, l3);
        trocaSinal(l3);
        limpar(l4);
        return 0;
    }
    if (checaSinal(l1) == -1 && checaSinal(l2) == 1)
    {
        BigInt *l4 = criar();
        copia(l1, l4);
        trocaSinal(l4);
        divisao(l4, l2, l3);
        trocaSinal(l3);
        limpar(l4);
        return 0;
    }

    buscarPosicao(l1,tamanho(l1) - 1,&m);

    if(m == 0 || maior(l1,l2) == l2){
        inserirFim(l3, 0);  //se o dividendo é 0, ou se o denominador é maior que o dividendo, o quociente é 0
        return 0;
    }

    if((tamanho(l2) - 1 == 0) && n == 1){
        copia(l1,l3);   //se o denominador é 1, o quociente é o próprio dividendo
        return 0;
    }

    BigInt *sub_temp = criar();
    BigInt *temp = criar();
    BigInt *one = criar();
    BigInt *tempSoma = criar();
    inserirFim(one,1);
    copia(l1,sub_temp);
    inserirFim(l3,0);

    while(maior(sub_temp,l2) == sub_temp){//enquanto o dividendo for maior que o denominador
        subtracao(sub_temp,l2,temp);      //subtrai o dividendo pelo denominador
        soma(l3,one,tempSoma);            //soma 1 no quociente
        removeZero(temp);

        //limpa da soma do quociente
        while(listaVazia(l3) != 0) removerInicio(l3);
        copia(tempSoma,l3);     //passa o quociente para l3 para o próximo loop ou pra retornar
        while(listaVazia(tempSoma) != 0) removerInicio(tempSoma);

        //limpa da divisao
        while(listaVazia(sub_temp) != 0) removerInicio(sub_temp);
        copia(temp,sub_temp);   //passa o resto para o próximo loop
        while(listaVazia(temp) != 0) removerInicio(temp);
    }

    limpar(sub_temp);
    limpar(temp);
    limpar(one);
    limpar(tempSoma);

    return 0;
}

int resto(BigInt *l1, BigInt *l2, BigInt  *l3){
    if (l3 == NULL || l1 == NULL || l2 == NULL)
        return 1;
    if (listaVazia(l1) == 0 || listaVazia(l2) == 0)
        return 2;

    int n,m;

    buscarPosicao(l2,tamanho(l2) - 1,&n);

    if(n == 0)      //se o denominador é 0, retorna 3
        return 3;

        if (checaSinal(l1) == -1 && checaSinal(l2) == -1)
    {
        BigInt *l4 = criar();
        copia(l2, l4);
        trocaSinal(l4);
        BigInt *l5 = criar();
        copia(l1, l5);
        trocaSinal(l5);
        resto(l4, l5, l3);
        limpar(l4);
        limpar(l5);
        return 0;
    }
    if (checaSinal(l1) == 1 && checaSinal(l2) == -1)
    {
        BigInt *l4 = criar();
        copia(l2, l4);
        trocaSinal(l4);
        resto(l1, l4, l3);
        trocaSinal(l3);
        limpar(l4);
        return 0;
    }
    if (checaSinal(l1) == -1 && checaSinal(l2) == 1)
    {
        BigInt *l4 = criar();
        copia(l1, l4);
        trocaSinal(l4);
        resto(l4, l2, l3);
        trocaSinal(l3);
        limpar(l4);
        return 0;
    }

    buscarPosicao(l1,tamanho(l1) - 1,&m);

    if(m == 0 || ((tamanho(l2) - 1 == 0) && n == 1)){
        inserirFim(l3, 0);  //se o dividendo for 0 ou se o denominador for 1, o resto vai ser 0
        return 0;
    }

    if(maior(l1,l2) == l2){
        copia(l1,l3);       //se o dividendo for maior que o denominador, o resto vai ser o dividendo
        return 0;
    }

    BigInt *quo_temp = criar();
    BigInt *temp = criar();
    BigInt *one = criar();
    BigInt *tempSoma = criar();

    inserirFim(one,1);
    copia(l1,l3);
    inserirFim(l3,0);

    while(maior(l3,l2) == l3){       //enquanto o dividendo for maior que o denominador
        subtracao(l3,l2,temp);       //subtrai o dividendo pelo denominador
        soma(quo_temp,one,tempSoma); //soma 1 no quociente
        removeZero(temp);

        //limpa da soma do quociente
        while(listaVazia(quo_temp) != 0) removerInicio(quo_temp);
        copia(tempSoma,quo_temp);   //passa o quociente para o próximo loop
        while(listaVazia(tempSoma) != 0) removerInicio(tempSoma);

        //limpa da divisao
        while(listaVazia(l3) != 0) removerInicio(l3);
        copia(temp,l3);     //passa o resto para o próximo loop ou para o retorno
        while(listaVazia(temp) != 0) removerInicio(temp);
    }

    limpar(quo_temp);
    limpar(temp);
    limpar(one);
    limpar(tempSoma);

    return 0;
}

int fatorial(BigInt *l1, BigInt *l2){
    if(l1 == NULL)
        return 1;
    if(l2 == NULL)
        return 2;
    if(checaSinal(l1) == -1)
        return 3;

    int m;

    buscarPosicao(l1,tamanho(l1) - 1,&m);

    if(m == 0 || ((tamanho(l1) - 1 == 0) && m == 1)){
        inserirFim(l2,1);
        return 0;
    }

    BigInt *diminui = criar(), *temp = criar(), *one = criar();

    inserirFim(one,1);
    copia(l1,temp);
    subtracao(l1,one,diminui);

    while(m != 0){     
        multiplicacao(temp,diminui,l2);

        while(listaVazia(temp) != 0) removerInicio(temp);
        copia(l2,temp);
        while(listaVazia(l2) != 0) removerInicio(l2);

        subtracao(diminui,one,l2);
        removeZero(l2);

        while(listaVazia(diminui) != 0) removerInicio(diminui);
        copia(l2,diminui);
        while(listaVazia(l2) != 0) removerInicio(l2);

        buscarPosicao(diminui,tamanho(diminui) - 1,&m);
    }

    copia(temp,l2);
    
    limpar(diminui);
    limpar(one);
    limpar(temp);

    return 0;
}

int potencia(BigInt *l1, BigInt *l2, BigInt *l3){
    if(l1 == NULL)
        return 1;
    if(l2 == NULL)
        return 2;
    if(checaSinal(l2) == -1)
        return 3;

    int m;

    buscarPosicao(l2,tamanho(l2) - 1,&m);

    if(m == 0)
    {
        inserirFim(l3,1);
        return 0;
    }

    if ((tamanho(l2) - 1 == 0) && m == 1)
    {
        copia(l1,l3);
        return 0;
    }

    BigInt *diminui = criar(), *temp = criar(), *one = criar(), *sub_temp = criar();

    inserirFim(one,1);
    copia(l1,temp);
    copia(l2,diminui);

    while(m != 1 || (tamanho(l2) != 1)){     
        multiplicacao(temp,l1,l3);

        while(listaVazia(temp) != 0) removerInicio(temp);
        copia(l3,temp);
        while(listaVazia(l3) != 0) removerInicio(l3);

        subtracao(diminui,one,sub_temp);
        removeZero(sub_temp);

        while(listaVazia(diminui) != 0) removerInicio(diminui);
        copia(sub_temp,diminui);
        while(listaVazia(sub_temp) != 0) removerInicio(sub_temp);

        buscarPosicao(diminui,tamanho(diminui) - 1,&m);
    }
    copia(temp,l3);
    
    limpar(diminui);
    limpar(one);
    limpar(temp);
    limpar(sub_temp);

    return 0;
}