#ifndef FILA_H
#define FILA_H

#include "musica.h"
#include "lista.h"

typedef iterador j;

typedef struct fila {
  j *elemento; // ponteiro para os elementos da fila
  int inicio; // indice do primeiro elemento da fila 
  int fim; // indice do ultimo elemento da fila
  unsigned quantidade; // quantidade de elementos presentes na fila 
  unsigned qtMax; // quantidade maxima de elementos que podem ser colocados na fila
} fila;

typedef struct {
  j *elemento_atual;
  fila *fila;
} Iterador;

fila* inicializa_fila(int qtMax); // inicializa a fila no começo da execução

int vazia_fila(fila *f); // Retorna verdadeiro se ela está vazia, senão falso

int cheia_fila(fila *f); // Retorna verdadeiro caso cheia, senão falso

void limpa_fila(fila *f); // Limpa a fila

void destroi_fila(fila *f); // Desaloca a memória que foi usada na fila 

int insere_fila(fila *f, j dado); // Insere no final do vetor

j* remove_fila(fila *f); // Remove no inicio do vetor

unsigned quantidade_fila(fila *f); // Retorna a quantidade de elementos

void iterador_inicializa_fila(Iterador *i, fila *f); // Inicializa o iterador

Iterador* iterador_Proximo_fila(Iterador *i); // Retorna o iterador do proximo elemento

Iterador iterador_Primeiro_fila(fila *f); // Retorna o iterador do primeiro elemento

int iterador_Valido_fila(Iterador i); // Checa se o iterador é valido

j iterador_Elemento_fila(Iterador i); // Retorna elemento que o iterador aponta

#endif