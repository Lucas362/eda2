#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100 /* Tamanho do vetor */

typedef struct node{ /* Lista encadeada para colisões de hash */
  struct node *prox;
  struct node *ant;
  int value;
  int key; /* índice do hash */
}node;

void startVetor(node *vetor[]){
  int i;
  for(i = 0; i < SIZE; i++){
    vetor[i] = (node *) malloc (sizeof(node));
  }
}

void insertEnd(node *lista, int valor){
	node *novo = (node *) malloc(sizeof(node));
	novo->value = valor;
	novo->prox = NULL;

	if(lista->prox == NULL){
		lista->prox=novo;
    novo->ant = NULL;
	}else{
		node *tmp = lista->prox;

		while(tmp->prox != NULL)
			tmp = tmp->prox;

		tmp->prox = novo;
    novo->ant = tmp;
	}
}

void showList(node *lista){
		node *tmp = lista->prox;

		while(tmp != NULL){
  		printf("%d\n", tmp->value);
      tmp = tmp->prox;
    }

}

void clearList(node *lista){
  node *tmp = lista->prox, *aux;
  while(tmp != NULL){
    aux = tmp;
    tmp =tmp->prox;
    free (aux);
  }
  lista->prox = NULL;
}

int hash(int value){
    return ((value % SIZE) + SIZE) % SIZE;
}

void insert(int num, node *vetor[]){
  int hashPos;
  node *novo, *p;
  hashPos = hash(num); /* cálculo do hash */
  insertEnd(vetor[hashPos], num);
}

void createList(node *no, node *vetor[]){
  int tam, range, i, value;
  printf("Quantidade de itens da lista: ");
  scanf("%d", &tam);

  printf("Range de itens da lista: ");
  scanf("%d", &range);

  srand((unsigned)time(NULL));
  for (i = 0; i < tam; i++){
      /* gerando valores aleatórios entre zero e o range */
      value = (rand() % (range))+1;
      insertEnd(no, value);
      insert(value, vetor);

  }
  showList(no);
  printf("===========\nLista gerada com sucesso!\n===========\n");
}

int search(int num, node *vetor[]){
  int key;
  node *temp;

  key = hash(num);
  if (vetor[key]->prox == NULL)
    return -1;
  if(vetor[key]->prox->value == num){
    return 1;
  }else{
    temp = vetor[key]->prox;
    while(temp != NULL){
      if(temp->value == num){
        return 1;
      }
      temp = temp->prox;
    }
  }
  return -1;
}

int main(void){
  node *vetor[SIZE], *lista;
  lista = (node *) malloc(sizeof(node));
  int busca;
  startVetor(vetor);
  createList(lista, vetor);
  do{
    printf("Buscar valor (0 ou menos para sair): ");
    scanf("%d", &busca);
    if(busca > 0)
      search(busca, vetor)==1 ? puts("Encontrado") : puts("Nao Encontrado");
  }while(busca > 0);
  return 0;
}
