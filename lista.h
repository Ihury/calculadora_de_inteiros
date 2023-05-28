typedef struct lista BigInt;
typedef struct no No;

BigInt *criar();
void limpar(BigInt *l);

int inserirInicio(BigInt *l, int it);
int inserirFim(BigInt *l, int it);
int inserirPosicao(BigInt *l, int it, int pos);

int removerInicio(BigInt *l);
int removerFim(BigInt *l);
int removerPosicao(BigInt *l, int pos);
int removerItem(BigInt *l, int it);

int buscarItemChave(BigInt *l, int chave, int *retorno);
int buscarPosicao(BigInt *l, int pos, No *retorno);

int listaVazia(BigInt *l);
int listaCheia(BigInt *l);
int tamanho(BigInt *l);

int checaSinal(BigInt *l);
int converteSinal(BigInt *l);
void mostrar(BigInt *l);
int trocaSinal(BigInt *l);
int removeZero(BigInt *l);
BigInt *maior(BigInt *l1, BigInt *l2);

int soma(BigInt *l1, BigInt *l2, BigInt *l3);
int subtracao(BigInt *l1, BigInt *l2, BigInt *l3);