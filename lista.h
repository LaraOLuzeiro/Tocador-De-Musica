#ifndef LISTA_H
#define LISTA_H

#include "musica.h"

// Musica = struct de campos nome e artista
typedef Musica T;

struct no {
  T item;
  struct no *next; // ponteiro q aponta pro proximo nó, que aponta para o
                   // próximo, ligando a lista
  struct no *prev; // ponteiro q aponta pro nó anterior, que aponta para o
                   // anterior, ligando a lista
};

typedef struct { // mudar para encadeamento duplo
  struct no *sentinela;
  unsigned quantidade;
} lista;

typedef struct {
  struct no *elemento;
  lista *lista;
} iterador;

void inicializa_lista(lista *p); // inicializa a lista no início da execução

void destruir_lista(lista *p); // destroi a lista no final da execução

int vazia_lista(lista *p); // checa se a lista está vazia

int insere_inicio_lista(lista *p, T item); // insere um item no início lista

int insere_fim_lista(lista *p, T item); // insere um item no final da lista

void remove_inicio_lista(lista *p); // remove o início da lista

void remove_fim_lista(lista *p); // remove o final da lista

T retorna_inicio_lista(lista *p); // retorna o primeiro elemento da lista

/* ----------------- Mexendo com os iteradores, funções ----------------------- */

iterador iterador_primeiro_lista(lista *p); // retorna o iterador do primeiro elemento

iterador iterador_proximo_lista(iterador i); // retorna o iterador do proximo elemento

T iterador_elemento_lista(iterador i); // retorna o elemento apontado pelo iterador i

int iterador_valido_lista(iterador i); // retorna 1 se iterador é válido, 0 se não é

iterador retira_lista(iterador i); // retira o elemento apontado pelo iterador i

void iterador_nulo_lista(iterador *i); // atribui NULL ao elemento do iterador

int iterador_vazio_lista(iterador i); // retorna 1 se o iterador for nulo, e zero se nao

#endif