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
    puts("========Inicio lista========");
		node *tmp = lista->prox;
		while(tmp != NULL){
  		printf("%d\n", tmp->value);
      tmp = tmp->prox;
    }
    puts("========Fim lista========\n");
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
      value = (rand() % (range+1));
      insertEnd(no, value);
      insert(value, vetor);
  }
  printf("===========\nLista gerada com sucesso!\n===========\n");
}

double search(int num, node *vetor[]){
  clock_t t = clock();
  int key;
  node *temp;

  key = hash(num);
  temp = vetor[key]->prox;
  while(temp != NULL && num >= 0){
    if(temp->value == num){
      puts("\n=====Encontrado=====");
      return (double)(clock()-t)/CLOCKS_PER_SEC; // in seconds
    }
    temp = temp->prox;
  }
  puts("\n=====Nao Encontrado=====");
  return (double)(clock()-t)/CLOCKS_PER_SEC; // in seconds
}

double sequentialSearch(int num, node *lista){
  clock_t t = clock();
  node *temp = lista->prox;
  while(temp != NULL && num >= 0){
    if(temp->value == num){
      puts("\n=====Encontrado=====");
      return (double)(clock()-t)/CLOCKS_PER_SEC; // in seconds
    }
    temp = temp->prox;
  }
  puts("\n=====Nao Encontrado=====");
  return (double)(clock()-t)/CLOCKS_PER_SEC; // in seconds
}

void menu(){
  puts("1 - Listar todos os valores");
  puts("2 - Buscar valor");
  puts("3 - Comparar hash e busca sequencial");
  puts("0 - Sair");
}

int main(void){
  node *vetor[SIZE], *lista;
  lista = (node *) malloc(sizeof(node));
  int busca, op;
  double time_taken;
  startVetor(vetor);
  createList(lista, vetor);
  do{
    menu();
    scanf("%d", &op);
    switch(op){
      case 1:
        showList(lista);
        break;
      case 2:
        printf("Buscar valor: ");
        scanf("%d", &busca);
        time_taken = search(busca, vetor);
        printf("A funcao gastou %f segundos\n\n", time_taken);

        break;
      case 3:
        printf("Buscar valor: ");
        scanf("%d", &busca);

        time_taken = search(busca, vetor);
        printf("A funcao gastou %f segundos\n\n", time_taken);

        time_taken = sequentialSearch(busca, lista);
        printf("A funcao gastou %f segundos\n\n", time_taken);
    }
  }while(op > 0);
  return 0;
}
