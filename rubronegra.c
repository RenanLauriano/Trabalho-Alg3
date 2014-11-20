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
	if (!x -> dir)				//Se nao existe filho a direita de x
		return x;			//Retona o proprio x
	y = x -> dir;				//Define y
	x -> dir = y -> esq;			//Faz da subarvore esquerda de y, a subarvore direita de x
	y -> esq -> pai = x;			//Faz o filho a esquerda de y ser filho de x
	y -> pai = x -> pai;			//Liga o pai de x a y
	if (x -> pai == t -> nil)			//Se x nao tem pai, ou seja, eh raiz
		t -> raiz = y;			//y se torna a raiz
	else
		if (x == x -> pai -> esq)	//Se x for filho a esquerda
			x -> pai -> esq = y;	//Novo filho a esquerda eh y
		else				//Se x for filho a direita
			x -> pai -> esq = y;	//Novo filho a direira Ã© y
	y -> esq = x;				//Coloca x a esquerda de y
	x -> pai = y;				//y se torna pai de x
}

/*
 * Rotaciona a arvore para a direita
 */
void *rightRotate (arv *t, no *x)
{
	no *y;
	if (!x -> esq)				//Se nÃ£o existe filho a esquerda de x
		return x;			//Retorna x
	y = x -> esq;				//Define y
	x -> esq = y -> dir;			//Faz da subarvore direita de y, a subarvore esquerda de x
	y -> dir -> pai = x;			//Faz o filho a direita de y ser filho de x
	y -> pai = x -> pai;			//Liga o pai de x a y
	if (x -> pai == t -> nil)			//Se x nao tem pai, ou seja, eh raiz
		t -> raiz = y;			//y se torna a raiz
	else
		if (x == x -> pai -> dir)	//Se x for filho a direita
			x -> pai -> dir = y;	//Novo filho a direita eh y
		else				//Se x for filho a direita
			x -> pai -> dir = y;	//Novo filho a direira Ã© y
	y -> dir = x;				//Coloca x a direita de y
	x -> pai = y;				//y se torna pai de x
}

/*
 * Busca a chave a ser inserida na arvore
 */
char *busca_insere (no *x, char *chave)
{
	if (!x)					//Se nao existir arvore, retorna NULL
		return NULL;
	if (strcmp (chave, x -> chave) == 0)	//Se existir a chave desejada, retorna a chave
		return x -> chave;
	if (strcmp (chave, x -> chave) == -1)	//Procura a chave recursivamente
		return busca_insere (x -> esq, chave);
	return busca_insere (x -> dir, chave);
}

/*
 * Busca o no a ser removida da arvore
 */
no *busca_remove (no *x, char *chave)
{
	if (!x)					//Se nao existir arvore, retorna NULL
		return NULL;
	if (strcmp (chave, x -> chave) == 0)	//Se existir o no com a chave desejada, retorna o no
		return x;
	if (strcmp (chave, x -> chave) == -1)	//Procura a chave recursivamente
		return busca_remove (x -> esq, chave);
	return busca_remove (x -> dir, chave);
}

/*
 * Troca de lugar os nos u e v
 */
void rn_transplant (arv *t, no *u, no *v)
{
	v = malloc (sizeof(no));
	if (u -> pai == t -> nil)		//Se o pai de u eh o sentinela
		t -> raiz = v;			//v se torna a raiz
	else
		if (u == u -> pai -> esq)	//Se nao, se u eh filho a esquerda
			u -> pai -> esq = v;	//v se torna u (esquerda)
		else
			u -> pai -> dir = v;	//Se nÃ£o v se torna u (direita)
		v -> pai = u -> pai;		//Pai de v se torna pai de u
}

/*
 * Imprime chave e conteudo dos nos, em ordem
 */
void rn_lista_conteudo(no *x) /****PARAMETRO ALTERADO****/
{
	if (!x)
		return;
	rn_lista_conteudo (x -> esq);
	printf ("%s\n%s\n\n", x -> chave, x -> conteudo);
	rn_lista_conteudo (x -> dir);
}

/*
 * Imprime chave, cor, pai, filho a esquerda e filho a direita dos nos, respectivamente, pre-ordem
 */
void rn_lista_estrutura(no *x) /****PARAMETRO ALTERADO****/
{
	char *cor;
	if (!x)
		return;
	if (x -> cor == RED)
		cor = "VERMELHO";
	else
		if (x -> cor == BLACK)
			cor = "PRETO";
	printf ("chave: %s\ncor: %s\n", x -> chave, cor);
	if (x -> pai != NULL)
		printf("pai: %s\n", x -> pai -> chave);
	else
		printf("pai: NULL\n");

	if (x -> esq != NULL)
		printf("esq: %s\n", x -> esq -> chave);
	else
		printf("esq: NULL\n");

	if (x -> dir != NULL)
		printf("dir: %s\n", x -> dir -> chave);
	else
		printf("dir: NULL\n");
	rn_lista_estrutura (x -> esq);
	rn_lista_estrutura (x -> dir);
}

/*
 * Busca uma chave na arvore
 */
char *rn_busca(no *x, char *chave)
{
	if (!x)						//Se nao existir arvore, retorna NULL
		return NULL;
	if (strcmp (x -> chave, chave) == 0)		//Se existir no com a chave procurada, retorna seu conteudo
		return x -> conteudo;
	if (strcmp (x -> chave, chave) == -1)		//Procura na arvore recursivamente
		return rn_busca (x -> esq, chave);
	return rn_busca (x -> dir, chave);
}

/*
 * Cria uma arvore para as demais funÃ§Ãµes
 */
arv *rn_cria_arvore ()
{
	arv *t = (arv*) malloc (sizeof(arv));	//Aloca memoria para a arvore
	if (t == NULL)
		printf("Nao foi possivel criar a arvore.\n");
	else
		printf("A arvore foi criada.\n");
	return t;
}

/*
 * Arruma a coloraÃ§Ã£o da arvore
 */
void rn_insere_fixup (arv *t, no *z)
{
	no* y = malloc(sizeof(no*));
	no* x = malloc(sizeof(no*));
	while(z->pai == RED){
		if(z->pai == z->pai->pai->esq){
			y = z->pai->pai->dir;
			if(y->cor == RED){
				z->pai->cor = BLACK;
				y->cor = BLACK; // tio
				z->pai->pai->cor = RED;
				z = z->pai->pai;

			}
			else
				if(z == z->pai->dir){
					z = z->pai;
					leftRotate(t, z);
				}
				z->pai->cor = BLACK;
				z->pai->pai->cor = RED;
				rightRotate(t, z->pai->pai);
		}
		else{
			y = z->pai->pai->esq;
			if(y->cor == RED){
				z->pai->cor = BLACK;
				y->cor = BLACK; // tio
				z->pai->pai->cor = RED;
				z = z->pai->pai;

			}
			else
				if(z == z->pai->esq){
					z = z->pai;
					leftRotate(t, z);
				}
				z->pai->cor = BLACK;
				z->pai->pai->cor = RED;
				rightRotate(t, z->pai->pai);
		}
	}
	t->raiz->cor = BLACK;
}

no* busca_no(no* p, char* chave){
	if((p == NULL) || (strcmp(t->chave, chave) == 0))
		return p;
	if(strcmp(chave, p->chave) == -1)
		return rn_busca(p->esq, chave);
	return rn_busca(p->dir, chave);
}
/*
 * Insere um no na arvore
 */
char *rn_insere (arv *t, char *chave, char *conteudo)
{
	no *y = t->nil;
	no *x = t->raiz;
	no *p = malloc(sizeof(no*));
	if(busca_no(t->raiz, chave) == NULL)
		return NULL;
	strcpy(p->chave, chave);
	strcpy(p->conteudo, conteudo);
	while(x != t->nil){
		y = x;
		if(strcmp(p->chave, x->chave) == -1)
			x = x->esq;
		else
			x = x->dir;
	}
	p->pai = y;
	if(y == t->nil)
		t->raiz = z;
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
	return p->conteudo;
}

/*
 * Arruma a coloraÃ§Ã£o da arvore
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
	no *x = malloc (sizeof(no));
	no *y = malloc (sizeof(no));
	no *z = malloc (sizeof(no));
	int cor_y;
	z = busca_remove (t -> raiz, chave);		//Busca o no com a chave a ser removida
	if (z != NULL)					//Se o no existe
	{
		y = z;					//y aponta para o no a ser removido
		cor_y = y -> cor;			//cor_y recebe a cor de z
		if (z -> esq == t -> nil)		//Se z nao tiver filho a esquerda
		{
			x = z -> dir;			//x aponta para seu filho a direita
			rn_transplant (t, z, z -> dir);	//Troca z com seu filho a direita
		}
		else
		{
			if (z -> dir == t -> nil)	//Se z nao tiver filho a direita
			{
				x = z -> esq;		//x aponta para seu filho a esquerda
				rn_transplant (t, z, z -> esq);	//Troca z com seu filho a esquerda
			}
			else
			{
				y = minimum (z -> dir);		//y aponta para o sucessor de z
				cor_y = y -> cor;		//cor_y recebe a cor do sucessor de z
				x = y -> dir;			//x aponta para o filho a direita do sucessor de z
				if (y -> pai == z)		//Se o pai do sucessor for z
					x -> pai = y;		//y se torna pai de x
				else
				{
					rn_transplant (t, y, y -> dir);	//Troca o sucessor com seu filho a direita
					y -> dir = z -> dir;		//
					y -> dir -> pai = y;
				}
				rn_transplant (t, z, y);
				y -> esq = z -> esq;
				y -> esq -> pai = y;
				y -> cor = z -> cor;
			}
			if (cor_y == BLACK)
				rn_remove_fixup (t, x);
			return z -> conteudo;
		}
		return NULL;
	}
}
/*
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
    buffer_chave[strlen(buffer_chave) - 1] = '\0'; /* apaga o \n no final
    fgets(buffer_conteudo, 4097, stdin);
    buffer_conteudo[strlen(buffer_conteudo) - 1] = '\0';
    chave = strdup(buffer_chave);
    conteudo = strdup(buffer_conteudo);
    rn_insere(t, chave, conteudo);
    eof = getc(stdin);
  }
  
  printf("buscando o conteudo da chave teste: %s\n",
	 rn_busca(t -> raiz, "teste"));
  
  printf("removendo a chave teste e seu conteudo: %s\n",
	 rn_remove(t, "teste"));
  
  rn_lista_conteudo(t -> raiz);

  rn_lista_estrutura(t -> raiz);

}*/


int main() {
  char buffer_chave[257];
  char buffer_conteudo[4097];
  char *chave, *conteudo, *retorno;
  char eof;
  arv *t;
int num;

  t = rn_cria_arvore();

	printf("Entre com um valor:\n1.Inserir     2.Remover     3.Buscar    4.FIM!\n");
	scanf ("%d", &num);
	while (num != 4)
	{
		switch(num)
		{
			case (1):
				while (getchar() != '\n');		//Limpa buffer
				printf("Entre com a chave a ser inserida na arvore:\n");
				fgets(buffer_chave, 257, stdin);
				buffer_chave[strlen(buffer_chave) - 1] = '\0'; /* apaga o \n no final*/
				printf("Entre com o conteudo a ser inserido na arvore:\n");
				fgets(buffer_conteudo, 4097, stdin);
				buffer_conteudo[strlen(buffer_conteudo) - 1] = '\0';
				chave = strdup(buffer_chave);
				conteudo = strdup(buffer_conteudo);
				retorno = rn_insere(t, chave, conteudo);
				printf("\n");
				rn_lista_conteudo(t -> raiz); /****PARAMETRO ALTERADO****/

				rn_lista_estrutura(t -> raiz); /****PARAMETRO ALTERADO****/
			break;
			case(2):
				while (getchar() != '\n');		//Limpa buffer
				printf("Entre com a chave a ser removida da arvore:\n");
				fgets(buffer_chave, 257, stdin);
				buffer_chave[strlen(buffer_chave) - 1] = '\0'; /* apaga o \n no final*/
				chave = strdup(buffer_chave);
				retorno = rn_remove(t, chave);
				printf("\n");
				rn_lista_conteudo(t -> raiz); /****PARAMETRO ALTERADO****/

				rn_lista_estrutura(t -> raiz); /****PARAMETRO ALTERADO****/
			break;
			case(3):
				while (getchar() != '\n');		//Limpa buffer
				printf("Entre com a chave a ser buscada na arvore:\n");
				fgets(buffer_chave, 257, stdin);
				buffer_chave[strlen(buffer_chave) - 1] = '\0'; /* apaga o \n no final*/
				chave = strdup(buffer_chave);
				retorno = rn_busca(t -> raiz, chave);
				printf("\n");
				rn_lista_conteudo(t -> raiz); /****PARAMETRO ALTERADO****/

				rn_lista_estrutura(t -> raiz); /****PARAMETRO ALTERADO****/
			break;
		}
	printf("\n\nEntre com um valor:\n1.Inserir     2.Remover     3.Buscar    4.FIM!\n");
	scanf ("%d", &num);
	}

}
