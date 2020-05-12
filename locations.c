/*Hvar consulting - EX 3. LOCATIONS - RESOLUÇÃO POR ARVORES ENÁRIAS*/

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#define limite 100
#define numNos 7

typedef struct aux{
struct aux* sub;
struct aux* prox;
char cep[20];
}LOCAL;


int numeroLocais(LOCAL* raiz){
	if(raiz == NULL) return 0;
	return 1 + numeroLocais(raiz->sub) + numeroLocais(raiz->prox);
}/*Retorna número de locais abaixo da origem SE "numeroLocais(m->sub) OBS: +1 se numeroLocais(m)"*/

int altura(LOCAL* m){
	if(!m) return -1;
	int max = -1;
	int aux;
	LOCAL* filhos = m->sub;
	   while (filhos != NULL){
	      aux = altura(filhos);
	      if (aux > max) max = aux;
	      filhos = filhos->prox;
	   }
	   return max + 1;
}/*Retorna o número de níveis*/

void ordena(char (*array)[20]){
	int i, j;
	char temp[20];
	for (i = 0; i < numNos; ++i) {
		for (j = i + 1; j < numNos; ++j) {
		    if (strcmp(array[i], array[j]) > 0) {
		        strcpy(temp, array[i]);
		        strcpy(array[i], array[j]);
		        strcpy(array[j], temp);
		    }
		}
	}
}/*Ordena as strings pelos seus valores ascii utilizando "strcmp()"*/

void copia(LOCAL* m, char (*array)[20], int *cont){
	if(m == NULL) return;
	strcpy(array[*cont], m->cep);
	(*cont)++;
	copia(m->prox, array, cont);
	copia(m->sub, array, cont);
	return;
}/*Copia as strings para um array*/

LOCAL* busca(LOCAL* raiz, char nome[20]){
	if(raiz == NULL) return NULL;
	if(strcmp(raiz->cep, nome) == 0) return raiz;
	LOCAL* aux = busca(raiz->sub, nome);
	if (aux) return aux;
	return busca(raiz->prox, nome);
}/*Busca um nó qualquer usando recursão*/

LOCAL* criaLocal(char nome[20]){
	LOCAL* novoLocal = (LOCAL*)malloc(sizeof(LOCAL));
	novoLocal->sub = NULL;
	novoLocal->prox = NULL;
	strcpy(novoLocal->cep, nome);
	return novoLocal;
}/*Cria um nó*/


void insere(LOCAL* m, char local[20], char destino[20]){
	int n = altura(m);
	if(n >= 100) {
	printf("Altura máxima alcançada!\n");
	return;
	}
	LOCAL* dest = busca(m, destino);
	if(!dest) return;
	LOCAL* novo = criaLocal(local);
	novo->sub = NULL;
	novo->prox = dest->sub;
	dest->sub = novo;
}/*Insere na árvore*/

void imprime(LOCAL* m, char(*array)[20]){
	int i, n;
	n = 0;
	LOCAL* atual;
	for(i = 0; i < numNos; i++){
	atual = busca(m, array[i]);
	n = numeroLocais(atual->sub);
	printf("%s %i\n", array[i], n);
	}
}/*Imprime um array ordenado ou não, e o número de sub locais*/


int main()
{
LOCAL* m;
char destino[20];
char local[20];
scanf("%s", local);
m = criaLocal(local);

int i;
for(i = 0;i < numNos-1; i++){
scanf("%s %s", local, destino);
insere(m, local, destino);
}

char array[numNos][20];
int cont = 0;
int n = altura(m);

copia(m, array, &cont);
ordena(array);
imprime(m, array);

return 0;
}/*Main*/
