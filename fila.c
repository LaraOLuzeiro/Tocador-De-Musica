#include "fila.h"
#include "musica.h"
#include <stdio.h>
#include <stdlib.h>

fila *inicializa_fila(int qtMax) {
  fila *f =
      (fila *)malloc(sizeof(fila)); // aloca memória para a estrutura da fila
  f->elemento =
      (j *)malloc(sizeof(j) * qtMax); // aloca memória para o vetor de elementos

  f->inicio = 0;     // o primeiro indice do vetor
  f->fim = -1;       // incializa o último índice do vetor
  f->quantidade = 0; // inicializa o tamanho do vetor como zero
  f->qtMax = qtMax;

  return f; // retorna a fila com capacidade especifica
}

int vazia_fila(fila *f) {
  return f->quantidade == 0; // Retorna 1 se a quantidade de elemento for zero e
                             // a fila estiver vazia
}

int cheia_fila(fila *f) { 
  return f->quantidade == f->qtMax; }

void limpa_fila(fila *f) {

  f->inicio = 0;     // o primeiro indice do vetor
  f->fim = -1;       // incializa o último índice do vetor
  f->quantidade = 0; // inicializa o tamanho do vetor como zero
}

void destroi_fila(fila *f) {
  free(f->elemento);
  free(f);
}

int insere_fila(fila *f, j dado) {
  if ((cheia_fila(f)) && (dado.elemento != NULL)) // caso em que a fila está cheia e não conseguimos inserir
    return 0;
  f->fim =
      (f->fim + 1) % f->qtMax; // vê qual será o índice para alocar o elemento
  f->elemento[f->fim] = dado;

  f->quantidade++; // Incremento um na quantidade de elementos do vetor

  return 1; // Inserido com sucesso
}

j* remove_fila(fila *f) {
  if (!vazia_fila(f)) {
    j *aux = &f->elemento[f->inicio];
    f->inicio = (f->inicio + 1) % f->qtMax;
    f->quantidade--;
    return aux;
  } // não é possível remover pois não há elementos na fila
  else {
    return NULL;
  }
}

unsigned quantidade_fila(fila* fila){
  return fila->quantidade;
}

void iterador_inicializa_fila(Iterador *i, fila *f) {
  i->fila = f;                                 // fila do iterador recebe a fila
  i->elemento_atual = &f->elemento[f->inicio]; //
}

Iterador *iterador_Proximo_fila(Iterador *i) {
  i->elemento_atual++; // incrementa o indice do elemento atual

  return i;
}

Iterador iterador_Primeiro_fila(fila *f) {
  Iterador iterador;
  iterador.fila = f;
  if (f->quantidade == 0) {
    iterador.elemento_atual = NULL;
  } else {
    iterador.elemento_atual = &(f->elemento[f->inicio]);
  }
  return iterador;
}

int iterador_Valido_fila(Iterador i) {
  if (i.elemento_atual >
      &(i.fila->elemento[i.fila->fim])) { // se o elemento atual passa o fim do
                                          // vetor retorna 0
    return 0;
  } else {
    return 1;
  }
}

j iterador_Elemento_fila(Iterador i) { 
  return *i.elemento_atual; 
}
