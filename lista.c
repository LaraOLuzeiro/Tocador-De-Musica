#include "lista.h"
#include "musica.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void inicializa_lista(lista *p) {
  struct no *n = (struct no *)malloc(sizeof(struct no));
  n->next = n->prev = p->sentinela = n;
  p->quantidade = 0;
}

void destruir_lista(lista *p) {
  while (!vazia_lista(p)) {
    remove_inicio_lista(p); //vai removendo os elementos da lista do inicio ao fim
  }
  free(p->sentinela); //remove o sentinela da lista
}

int vazia_lista(lista *p) {
  return p->sentinela->next == p->sentinela; // se o elemento após o sentinela for ele mesmo, a lista está vazia
}

int insere_inicio_lista(lista *p, T item) {
  struct no *n = (struct no *)malloc(sizeof(struct no));
  if (n != NULL) {
    n->item = item;
    n->next = p->sentinela->next; /* o next do elemento inserido vai ser o primeiro elemento
                                     antigo(o elemento que o sentinela apontava)*/
    n->prev = p->sentinela; /* como foi inserido no inicio, agr o prev dele
                               aponta para o sentinela */
    p->sentinela->next = n; /* como o elemento foi colocado no inicio o next do sentinela agr tem
                               q apontar para ele, pq ele é o primeiro elemento do lista */
    n->next->prev = n; /* prev do antigo primeiro elemento vai apontar pro novo
                          primeiro elemento */
    p->quantidade++; //incrementa a quantidade
    return 1; //retorna 1 se conseguiu inserir o item na lista
  } else {
    return 0; //retorna 0 se nao conseguiu inserir o item na lista
  }
}


int insere_fim_lista(lista *p, T item) {
  struct no *n = (struct no *)malloc(sizeof(struct no));
  if (n != NULL) {
    n->item = item;
    n->next =
        p->sentinela; /* o next do elemento inserido vai ser o primeiro elemento
                         antigo(o elemento que o sentinela apontava) */
    n->prev = p->sentinela->prev; // como foi inserido no inicio, agr o prev dele aponta para o sentinela
    p->sentinela->prev = n; /* como o elemento foi colocado no inicio o next do sentinela agr tem
                               q apontar para ele, pq ele é o primeiro elemento do lista*/
    n->prev->next = n; // next do antigo ultimo elemento vai apontar para o novo ultimo
    p->quantidade++; //incrementa a quantidade
    return 1; //retorna 1 se conseguiu inserir o item na lista
  } else {
    return 0; //retorna 0 se nao conseguiu inserir o item na lista
  }
}

void remove_inicio_lista(lista *p) {
  if (!vazia_lista(p)) {
    struct no *n = p->sentinela->next; // n é o next do sentinela, aponta pro primeiro elemento
    n->prev->next = n->next; // next do sentinela, aponta pro q era o next do primeiro elemento
    n->next->prev = n->prev; // prev do segundo elemento tem q aponto pro q era o prev do primeiro elemento
    free(n); //desaloca o *n
    p->quantidade--; //decrementa a quantidade
  }
}

void remove_fim_lista(lista *p) {
  if (!vazia_lista(p)) {
    struct no *n = p->sentinela->prev; // prev do sentinela, aponta para o ultimo elemento
    n->next->prev = n->prev; // prev do sentinela, aponta pra onde o prev do ultimo apontava
    n->prev->next = n->next; // next do penultimo agr aponta pro que era o next do ultimo(sentinela)
    free(n);  //desaloca o *n
    p->quantidade--; //decrementa a quantidade
  }
}

T retorna_inicio_lista(lista *p) { 
  return p->sentinela->next->item; //retorna o primeiro elemento da lista
}

/* ---------------------------------------- Mexendo com os iteradores, funções ----------------------------------------------------------- */

iterador iterador_primeiro_lista(lista *p) {
  iterador i;
  // O iterador pega o primeiro elemento na lista
  i.elemento = p->sentinela->next;
  i.lista = p;
  // Faz o retorno do primeiro elemento
  return i;
}

iterador iterador_proximo_lista(iterador i) {
  iterador prox;
  // O iterador prox vai para o proximo elemento, com base no iterador i
  prox.elemento = i.elemento->next;
  prox.lista = i.lista;

  // Faz o retorno de proximo elemento
  return prox;
}
// retornar um dado com base no iterador
T iterador_elemento_lista(iterador i) {
  // deve ser valido
  return i.elemento->item;
}

int iterador_valido_lista(iterador i) {
  // verdadeiro caso tenha algo contido nele, tipo se nao for o sentinela no caso
  return i.elemento != i.lista->sentinela;
}

iterador retira_lista(iterador i) {
  if (iterador_valido_lista(i)) {
    struct no *n = i.elemento;
    // O elemento do iterador recebe o proximo
    i.elemento = i.elemento->next;
    // O apontador anterior do elemento próximo deve ser o anterior do atual, retirando-o
    n->next->prev = n->prev;
    // O apontador próximo do elemento anterior deve ser o próximo do atual, retirando-o
    n->prev->next = n->next;
    // Realiza a desalocação do n
    free(n);
    // Decrementa a quantidade de elementos da lista
    i.lista->quantidade--;
  }
  return i;
}

void iterador_nulo_lista(iterador *i){ 
  i->elemento = NULL; //atribui NULL ao elemento do iterador
}

int iterador_vazio_lista(iterador i){
  if(i.elemento == NULL){ //se o elemento do iterador for NULL, retorna 1
    return 1;
  } else{ //senão, retorna 0
    return 0;
  }
}