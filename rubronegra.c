//#include "rubronegra.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum tipoCor{
    RED,
    BLACK
}tipoCor;

typedef struct no{
    tipoCor cor;
    char chave[257];
    char conteudo[4097];
    struct no *esq;
    struct no *dir;
    struct no *pai;
} no;

typedef struct arv{
    struct no *raiz;
    struct no *nil;
} arv;

/*
 * Retorna o menor no de uma arvore
 */
no *minimum (no *x)
{
    if (!x || !x -> esq)
        return x;
    return minimum (x -> esq);
}

/*
 * Retorna o maior no de uma arvore
 */
no *maximum (no *x)
{
    if (!x || !x -> dir)
        return x;
    return maximum (x -> dir);
}

/*
 * Rotaciona a arvore para a esqueda
 */
void *leftRotate (arv *t, no *x)
{
    no *y;
    if (!x -> dir)                //Se nao existe filho a direita de x
        return x;            //Retona o proprio x
    y = x -> dir;                //Define y
    x -> dir = y -> esq;            //Faz da subarvore esquerda de y, a subarvore direita de x
    y -> esq -> pai = x;            //Faz o filho a esquerda de y ser filho de x
    y -> pai = x -> pai;            //Liga o pai de x a y
    if (x -> pai == t -> nil)            //Se x nao tem pai, ou seja, eh raiz
        t -> raiz = y;            //y se torna a raiz
    else
        if (x == x -> pai -> esq)    //Se x for filho a esquerda
            x -> pai -> esq = y;    //Novo filho a esquerda eh y
        else                //Se x for filho a direita
            x -> pai -> esq = y;    //Novo filho a direira é y
    y -> esq = x;                //Coloca x a esquerda de y
    x -> pai = y;                //y se torna pai de x
}

/*
 * Rotaciona a arvore para a direita
 */
void *rightRotate (arv *t, no *x)
{
    no *y;
    if (!x -> esq)                //Se não existe filho a esquerda de x
        return x;            //Retorna x
    y = x -> esq;                //Define y
    x -> esq = y -> dir;            //Faz da subarvore direita de y, a subarvore esquerda de x
    y -> dir -> pai = x;            //Faz o filho a direita de y ser filho de x
    y -> pai = x -> pai;            //Liga o pai de x a y
    if (x -> pai == t -> nil)            //Se x nao tem pai, ou seja, eh raiz
        t -> raiz = y;            //y se torna a raiz
    else
        if (x == x -> pai -> dir)    //Se x for filho a direita
            x -> pai -> dir = y;    //Novo filho a direita eh y
        else                //Se x for filho a direita
            x -> pai -> dir = y;    //Novo filho a direira é y
    y -> dir = x;                //Coloca x a direita de y
    x -> pai = y;                //y se torna pai de x
}

/*
 * Busca a chave a ser inserida na arvore
 */
char *busca_insere (no *x, char *chave)
{
    if (!x)                    //Se nao existir arvore, retorna NULL
        return NULL;
    if (strcmp (chave, x -> chave) == 0)    //Se existir a chave desejada, retorna a chave
        return x -> chave;
    if (strcmp (chave, x -> chave) == -1)    //Procura a chave recursivamente
        return busca_insere (x -> esq, chave);
    return busca_insere (x -> dir, chave);
}

/*
 * Busca o no a ser removida da arvore
 */
no *busca_remove (no *x, char *chave)
{
    if (!x)                    //Se nao existir arvore, retorna NULL
        return NULL;
    if (strcmp (chave, x -> chave) == 0)    //Se existir o no com a chave desejada, retorna o no
        return x;
    if (strcmp (chave, x -> chave) == -1)    //Procura a chave recursivamente
        return busca_remove (x -> esq, chave);
    return busca_remove (x -> dir, chave);
}

void rn_lista_conteudo_em(no* t){
    if(t != NULL){
        rn_lista_conteudo_em(t->esq);
        printf("%s\n", t->chave);
        printf("%s\n\n", t->conteudo);
        rn_lista_conteudo_em(t->dir);
    }

}

void rn_lista_conteudo(arv* t){
    rn_lista_conteudo_em(t->raiz);
}


/* rn_lista_estrutura: Imprime a estrutura da Ã¡rvore t na
   saÃ­da padrÃ£o (stdout). A Ã¡rvore deve ser apresentada
   por um caminhamento prÃ©-ordem, ou seja, mostra o nÃ³,
   sua subÃ¡rvore filha Ã  esquerda e sua subÃ¡rvore filha
   Ã  direita. Para cada nÃ³ mostrar:
     chave: a chave do nÃ³
     cor: vermelho ou preto
     pai: a chave do nÃ³ pai ou NULL
     esq: a chave do filho da esquerda ou NULL
     dir: a chave do filho da direita ou NULL
   Caso o nÃ³ nÃ£o possua pai ou filho Ã  esquerda ou filho
   Ã  direita, deve ser mostrado NULL no lugar da chave
   correspondente. Os nÃ³s devem ser separados por uma
   linha em branco. */
void rn_lista_estrutura_pre(no* t){
    printf("%s\n", t->chave);
        if(t->cor == 0)
            printf("vermelho\n");
        else
            printf("preto\n");
        if(t->pai != NULL) //PAI
            printf("%s\n", t->pai->chave);
        else
            printf("NULL\n");
        if(t->esq != NULL) // ESQUERDA
            printf("%s\n", t->esq->chave);
        else
            printf("NULL\n");
        if(t->dir != NULL) //DIREITA
            printf("%s\n", t->dir->chave);
        else
            printf("NULL\n");
        printf("\n");
        rn_lista_estrutura_pre(t->esq);
        rn_lista_estrutura_pre(t->dir);



}

void rn_lista_estrutura(arv *t){
    if(t->raiz != NULL)
        rn_lista_estrutura_pre(t->raiz);

}


/* rn_busca: Busca na Ã¡rvore t a chave passada como parÃ¢metro.
   Se a chave for encontrada retorna um ponteiro para o
   conteÃºdo correpondente, se a chave nÃ£o for encontrada
   retorna NULL. */
char* rn_busca_no(no* t, char* chave){
    if(t == NULL)
        return NULL;
    if(strcmp(t->chave, chave) == 0)
        return t->conteudo;
    if(strcmp(chave, t->chave) == -1)
        return rn_busca_no(t->esq, chave);
    return rn_busca_no(t->dir, chave);
}

char* rn_busca(arv* t, char* chave){
    if(t->raiz == NULL)
        return NULL;
    return rn_busca_no(t->raiz, chave);

}


/*
 * Cria uma arvore para as demais funções
 */
arv *rn_cria_arvore ()
{
    arv *t = (arv*) malloc (sizeof(arv));    //Aloca memoria para a arvore
    return t;
}

/*
 * Arruma a coloração da arvore
 */
void rn_insere_fixup (arv *t, no *z)
{
    no *y;
//    if (z != t -> raiz)    //Se o no for raiz, so pinta raiz de preto
//    {
        while (z != t -> raiz && z -> pai -> cor == RED)    //Enquanto a cor do pai de z for vermelha
        {
            if (z -> pai == z -> pai -> pai -> esq)    //CASO 1: Se o pai de z eh filho a esquerda de seu avo
            {
                y = z -> pai -> pai -> dir;    //y aponta para o tio de z
                if (y != t -> nil && y -> cor == RED)        //Se o tio for vermelho
                {
                    z -> pai -> cor = BLACK;    //Pinta o pai de z de preto
                    y -> cor = BLACK;        //Pinta z de preto
                    z -> pai -> pai -> cor = RED;    //Pinta o avo de z de vermelho
                    z = z -> pai -> pai;    //z aponta para o avo
                }
                else
                {
                    if (z == z -> pai -> dir)    //CASO 2: Se z eh filho a direita
                    {
                        z = z -> pai;        //z aponta para seu pai
                        leftRotate (t, z);    //Faz rotacao a esquerda no pai de z
                    }
                    z -> pai -> cor = BLACK;    //CASO 3: Pinta o pai de z de preto
                    z -> pai -> pai -> cor = RED;    //Pinta o avo de z de vermelho
                    rightRotate (t, z -> pai -> pai);    //Faz rotacao a direita no avo de z
                }
            }
            else
            {
                y = z -> pai -> pai -> esq;    //y aponta para o tio de z
                if (y != t -> nil && y -> cor == RED)        //Se o tio for vermelho
                {
                    z -> pai -> cor = BLACK;    //Pinta o pai de z de preto
                    y -> cor = BLACK;        //Pinta z de preto
                    z -> pai -> pai -> cor = RED;    //Pinta o avo de z de vermelho
                    z = z -> pai -> pai;    //z aponta para o avo
                }
                else
                {
                    if (z == z -> pai -> esq)    //CASO 2: Se z eh filho a direita
                    {
                        z = z -> pai;        //z aponta para seu pai
                        rightRotate (t, z);    //Faz rotacao a esquerda no pai de z
                    }
                    z -> pai -> cor = BLACK;    //CASO 3: Pinta o pai de z de preto
                    z -> pai -> pai -> cor = RED;    //Pinta o avo de z de vermelho
                    leftRotate (t, z -> pai -> pai);    //Faz rotacao a direita no avo de z
                }
            }
        }
//    }
    t -> raiz -> cor = BLACK;    //Pinta raiz de preto
}

/*
 * Insere um no na arvore
 */
char *rn_insere (arv *t, char *chave, char *conteudo)
{
    no *y = t->nil;
    no *x = t->raiz;
    no *p = malloc(sizeof(no));
    strcpy(p->chave, chave);
    strcpy(p->conteudo, conteudo);
    if (t -> raiz == t -> nil)
    {
        t->raiz = p;
        t->raiz->cor = BLACK;
    }
    else
    {
        if(busca_insere(t->raiz, chave) != NULL)
            return NULL;
        while(x != t->nil){
            y = x;
            if(strcmp(p->chave, x->chave) == -1)
            x = x->esq;
            else
            x = x->dir;
        }
        p->pai = y;
        if(y == t->nil)
            t->raiz = p;
        else{
            if(strcmp(p->chave, y->chave) == -1)
                y->esq = p;
            else
                y->dir = p;
        }
        p->esq = t->nil;
        p->dir = t->nil;
        p->cor = RED;
        rn_insere_fixup(t, p);
    }
    return p->conteudo;
}



/*
 * Arruma a coloração da arvore
 */
void *rn_remove_fixup (arv *t, no *x)
{
    no *w = malloc (sizeof(no));
    while (x != t -> raiz && x -> cor == BLACK)
    {
        if (x == x -> pai -> esq)
        {
            w = x -> pai -> dir;
            if (w -> cor == RED)
            {
                w -> cor = BLACK;
                x -> pai -> cor = RED;
                leftRotate (t, x -> pai);
                w = x -> pai -> dir;
            }
            if (w -> esq -> cor == BLACK && w -> dir -> cor == BLACK)
            {
                w -> cor = RED;
                x = x -> pai;
            }
            else
            {
                if (w -> dir -> cor == BLACK)
                {
                    w -> esq -> cor = BLACK;
                    w -> cor = RED;
                    rightRotate (t, w);
                    w = x -> pai -> dir;
                }
                w -> cor = x -> pai -> cor;
                x -> pai -> cor = BLACK;
                w -> dir -> cor = BLACK;
                leftRotate (t, x -> pai);
                x = t -> raiz;
            }
        }
        else
        {
            if (x == x -> pai -> dir)
            {
                w = x -> pai -> esq;
                if (w -> cor == RED)
                {
                    w -> cor = BLACK;
                    x -> pai -> cor = RED;
                    rightRotate (t, x -> pai);
                    w = x -> pai -> esq;
                }
                if (w -> dir -> cor == BLACK && w -> esq -> cor == BLACK)
                {
                    w -> cor = RED;
                    x = x -> pai;
                }
                else
                {
                    if (w -> esq -> cor == BLACK)
                    {
                        w -> dir -> cor = BLACK;
                        w -> cor = RED;
                        leftRotate (t, w);
                        w =  x -> pai -> esq;
                    }
                    w -> cor = x -> pai -> cor;
                    x -> pai -> cor = BLACK;
                    w -> esq -> cor = BLACK;
                    rightRotate (t, x -> pai);
                    x = t -> raiz;
                }
            }
        }
    }
    x -> cor  = BLACK;
}

/*
 * Remove um no da arvore
 */
char *rn_remove(arv *t, char *chave)
{
    no *p = malloc(sizeof(no*));
    no *y = malloc(sizeof(no*));
    no *x = malloc(sizeof(no*));

    p = busca_remove(t->raiz, chave);
    if(!p)
        return NULL;

    if((p->esq = t->nil) || (p->dir == t->nil))
        y = p;
    else
    	y = sucessor(p);
   if(y->esq != t->nil)
   	   x = y->esq;
   else
	   x = y->dir;
   x->pai = y->pai;
   if(y->pai == t->nil){
	   t->raiz = x;

   }
   else
	   if(y == y->pai_esq)
		   y->pai->esq = x;
	   else
		   y->pai->dir = x;
   if(y != p){
	   strcpy(p->chave, y->chave);
	   strcpy(p->conteudo, y->conteudo);
	   p->pai = y->pai;
	   p->dir = y->dir;
	   p->esq = y->esq;
   }
   if(y->cor == BLACK)
	   rn_remove_fixup(t, x);
   return p->conteudo;

}


int main() {
  char buffer_chave[257];
  char buffer_conteudo[4097];
  char *chave, *conteudo;
  char eof;
  arv *t;

  t = rn_cria_arvore();

  eof = getc(stdin);
  while(eof != EOF) {
    ungetc(eof, stdin);
    fgets(buffer_chave, 257, stdin);
    buffer_chave[strlen(buffer_chave) - 1] = '\0'; /* apaga o \n no final*/
    fgets(buffer_conteudo, 4097, stdin);
    buffer_conteudo[strlen(buffer_conteudo) - 1] = '\0';
    chave = strdup(buffer_chave);
    conteudo = strdup(buffer_conteudo);
    rn_insere(t, chave, conteudo);
    eof = getc(stdin);
  }

  printf("buscando o conteudo da chave teste: %s\n",
     rn_busca(t, "teste"));

  printf("removendo a chave teste e seu conteudo: %s\n",
     rn_remove(t, "teste"));

  rn_lista_conteudo(t);

  rn_lista_estrutura(t);

}
