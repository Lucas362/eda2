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

void createList(node *no){
  int tam, range, i;
  printf("Quantidade de itens da lista: ");
  scanf("%d", &tam);

  printf("Range de itens da lista: ");
  scanf("%d", &range);

  srand((unsigned)time(NULL));
  for (i = 0; i < tam; i++){
      /* gerando valores aleatórios entre zero e o range */
      insertEnd(no, (rand() % (range+1)));

  }
  printf("===========\nLista gerada com sucesso!\n===========\n");
}

int hash(int *value){
    return ((*value % SIZE) + SIZE) % SIZE;
}

void insert(int num, node vetor[]){
  int hashPos;
  node *novo, *p;
  hashPos = hash(&num); /* cálculo do hash */
  if(vetor[hashPos].key == NULL){
    vetor[hashPos].key = hashPos;
    vetor[hashPos].value = num;
  }
  else{ /* caso já exista valor na posição do hash, adicionar à lista */
    novo = (node *) malloc (sizeof(node));
    novo->key = hashPos;
    novo->value = num;
    p = &vetor[hashPos];
    while(p->prox != NULL){
      p = p->prox;
    }
    p->prox = novo;
    novo->ant = p;
    novo->prox = NULL;
  }
}

int search(int num, node vetor[]){
  int key;
  node *temp;

  key= hash(&num);
  if(vetor[key].value == num){
    return 1;
  }
  else{
    temp = &vetor[key];
    while(temp->prox != NULL){
      if(temp->value == num){
        return 1;
      }
      temp = temp->prox;
    }
  }
  return -1;
}

void menu(){
  puts("Escolha uma opcao abaixo");
  puts("1 - Gerar nova lista");
  puts("2 - Listar valores");
  puts("3 - Buscar valor");
  puts("0 - Sair");
}

int main(void){
  node vetor[SIZE], *lista;
  lista = (node *) malloc(sizeof(node));
  int op;
  createList(lista);
  do{
    menu();
    scanf("%d", &op);
    switch (op) {
      case 1:
        clearList(lista);
        createList(lista);
        break;
      case 2:
        showList(lista);
        break;
      // case 3:
      //   search();
    }
  }while(op != 0);
  return 0;
}
