#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fila.h"
#include "lista.h"
#include "musica.h"

#include <locale.h> // biblioteca para poder usar acentos

#define TAM_MAX_FILA 5000

// prototipo das funcoes
int Passa_musica(lista *p, fila *f, int loop_anterior);
void Ver_Lista(lista *p);
void Ver_Fila(fila *p);
iterador Busca_Musica (lista *p, char item[], char item2[]);

int main() {
  
  // declaracao e alocacao de arquivo txt, fila, lista e iterador
  FILE *file;
  file = fopen("playlist.txt", "r");
  if(file == NULL){
    printf("Não foi possível iniciar a playlist.\nO programa será encerrado...\n");
    return 0;
  }
  char *musica = (char *)malloc(60 * sizeof(char));
  Musica song;
  lista playlist;

  // inicializando lista e fila
  inicializa_lista(&playlist);
  fila *fila = inicializa_fila(TAM_MAX_FILA);

  // titulo
  printf(" ______   __         ______     __  __     __         __     ______  "
         "   ______  \n");
  printf("/\\  == \\ /\\ \\       /\\  __ \\   /\\ \\_\\ \\   /\\ \\       /\\ "
         "\\   /\\  ___\\   /\\__  _\\ \n");
  printf("\\ \\  __/ \\ \\ \\____  \\ \\  __ \\  \\ \\____ \\  \\ \\ \\____  "
         "\\ \\ \\  \\ \\___  \\  \\/_/\\ \\/ \n");
  printf(" \\ \\_\\    \\ \\_____\\  \\ \\_\\ \\_\\  \\/\\_____\\  \\ "
         "\\_____\\  \\ \\_\\  \\/\\_____\\    \\ \\_\\ \n");
  printf("  \\/_/     \\/_____/   \\/_/\\/_/   \\/_____/   \\/_____/   \\/_/   "
         "\\/_____/     \\/_/ \n");


  while (fscanf(file, "%[^\n] ", musica) != EOF) { // separa nome da musica e artista
    char aux[100]; // guarda temporariamente nome da musica ou artista
    int aspas = 0; // contador de aspas
    int i = 0;     // posicao do indice

    for (; aspas < 2; i++) {  // le o nome da musica ate fechar as aspas
      if (musica[i] == '"') { // confere se o caractere é "
        aspas++;              // se musica[i] for ", o contador de aspas aumenta
      }
      aux[i] = musica[i]; // coloca cada caractere no vetor auxiliar
    }

    aux[i] = '\0'; // coloca \0 no final no vetor
    i = i + 3;
    strcpy(song.nome, aux); // copia nome da musica armazenado no vetor aux para o song.nome

    for (int j = 0; (unsigned int) i <= strlen(musica);
         i++, j++)        // le nome do artista até o fim da string musica
      aux[j] = musica[i]; // coloca caractere do musica[i] para o aux[j]

    aux[strlen(aux) + 1] = '\0'; // coloca \0 no final do vetor
    strcpy(song.artista, aux); // copia nome do artista armazenado no vetor aux
                               // para o n song.artista

    insere_fim_lista(&playlist, song); // insere nome da musica e do artista na lista
  }
  fclose(file); // fecha o arquivo, pois suas informações já foram lidas 

  // inicio do programa, ele começa tocando a playlist e a fila esta vazia
  printf("\nIniciando a playlist\n");
  printf("♫ Tocando agora: %s - %s\n", retorna_inicio_lista(&playlist).nome, retorna_inicio_lista(&playlist).artista); // função retornaI retorna o primeiro elemento da lista

  char operacao[3]; // variavel que dita a operacao

  int loop_anterior = 0; /* variavel utilizada para registrar a origem da musica anterior, serve para comparar as condicoes para alternar entre playlist e fila. 0 = musica anterior estava na lista (playlist), 1 = estava na fila */
  

  // para aparecer as operacoes realizadas pelo tocador de musica
  while (1) {
    printf("\n1. Ver playlist\n");         // mostra a lista
    printf("2. Ver fila\n");               // mostra a fila
    printf("3. Inserir música na fila\n"); // inserir na fila
    printf("4. Pular música\n");           // pula a música
    printf("5. Limpar a fila\n");          // limpar a fila
    printf("6. Sair\n\n");                 //  encerra o programa

    printf("Selecione a operação desejada: ");
    // faz a leitura da operação
    scanf("%s", &operacao); //recebe char pois o usuário pode errar a operação e inserir palavras ao inves dos numeros
    printf("\n");

    int op = atoi(operacao); //transforma a string em int

    switch (op) {
    case 1: { // exibir a playlist 
      printf("Exibindo a playlist:\n");
      Ver_Lista(&playlist);
      break;
    }
    case 2: { // exibir a fila
      if (!vazia_fila(fila)) { //se a fila não está vazia, printa a fila
        Ver_Fila(fila);
      } else {
        printf("Fila vazia.\n"); //se a fila esta vazia, printa fila vazia
        
      }
      break;
    }
    case 3: { // inserir musica na fila
      printf("Digite o nome da música (entre aspas): ");
      scanf("\n%[^\n]", song.nome); //recebe o nome da musica
      printf("Digite o nome do artista: ");
      scanf("\n%[^\n]", song.artista); //recebe o nome do artista
      
      iterador busca = Busca_Musica(&playlist, song.nome, song.artista); //procura a musica digitada pelo usuario na playlist
      if(iterador_vazio_lista(busca)){ //se a musica não for encontrada ela não é adicionada na fila
        printf("\nMúsica não encontrada\n");
      } else if(insere_fila(fila, busca)){ //se a musica for encontrada insere ela na fila
        printf("\nMúsica adicionada à fila: %s - %s\n", iterador_elemento_lista(busca).nome, iterador_elemento_lista(busca).artista);  
      }
    
      break;
    }
    case 4: { // pular a música atual
      loop_anterior = Passa_musica(&playlist, fila, loop_anterior);
      break;
    }
    case 5: { // limpar a fila
      if (vazia_fila(fila)) {
        printf("Fila já vazia.\n"); // se tentar esvaziar uma fila já vazia
      } else {
        limpa_fila(fila); //esvazia a fila
        printf("Fila esvaziada.\n");
      }
      break;
    }
    case 6: { // encerrar programa
      printf("O programa será encerrado...\n");
      // Desalocações:
      free(musica);
      destruir_lista(&playlist); //destruir a playlist
      destroi_fila(fila);
      return 0;
    }
    default: { // operação inválida
      printf("Operação inválida ☹ \nTente novamente.\n");
      break;
    }
    }
  }
  
}


//------------------------- Funçoes -------------------------------------

void Ver_Lista(lista *p) { // imprime a playlist inteira
  for (iterador ite = iterador_primeiro_lista(p); iterador_valido_lista(ite); ite = iterador_proximo_lista(ite)) { //percorre a playlist inteira imprimindo seus elementos
    printf("%s - %s\n",  iterador_elemento_lista(ite).nome,  iterador_elemento_lista(ite).artista);
  }
}

void Ver_Fila(fila *p) { // imprime a fila inteira
  for (Iterador it = iterador_Primeiro_fila(p); iterador_Valido_fila(it); it = *iterador_Proximo_fila(&it)) { //percorre toda a fila e imprime seus elementos
    iterador i = iterador_Elemento_fila(it);
    printf("%s - %s\n", iterador_elemento_lista(i).nome , iterador_elemento_lista(i).artista); 
  }
}

int Passa_musica(lista *p, fila *f, int loop_anterior) { // pula a música
  //ta tocando playlist e continua na playlist
  if (loop_anterior == 0 && vazia_fila(f)) { // se estiver tocando a lista
    Musica item = iterador_elemento_lista(iterador_primeiro_lista(p)); // acessa o primeiro da lista
    printf("▶▶ Pulando: ");
    printf("%s - %s\n", item.nome, item.artista);
    insere_fim_lista(p, item);         // insere no fim
    remove_inicio_lista(p);                       // remove inicio
    Musica item2 = retorna_inicio_lista(p); // acessa o novo primeiro depois da remoção
    printf("♫  Tocando agora: %s - %s\n", item2.nome, item2.artista);
    return 0;
  }
    
  //ta tocando a fila e continua tocar a fila
   else if (loop_anterior == 1 && quantidade_fila(f) > 1){ 
     Musica item = iterador_elemento_lista(iterador_Elemento_fila(iterador_Primeiro_fila(f))); // acessa o primeiro da fila
     retira_lista(iterador_Elemento_fila(iterador_Primeiro_fila(f)));
     remove_fila(f);          // remove da fila
     printf("▶▶ Pulando: ");
     printf("%s - %s\n", item.nome, item.artista);
     insere_fim_lista(p, item); // adiciona a musica que acabou de tocar no final da playlist
     Musica item2 = iterador_elemento_lista(iterador_Elemento_fila(iterador_Primeiro_fila(f))); // acessa o novo primeiro depois da remoção
     printf("♫  Tocando agora: %s - %s\n", item2.nome, item2.artista); // vai pra proxima da fila
     return 1;
   }  
     
  //toca a fila e vai para a playlist
  else if (loop_anterior == 1 && quantidade_fila(f) == 1){
    Musica itemF = iterador_elemento_lista(iterador_Elemento_fila(iterador_Primeiro_fila(f))); // acessa o primeiro elemento da fila
    Musica itemP = retorna_inicio_lista(p); // acessa o primeiro da lista
    retira_lista(iterador_Elemento_fila(iterador_Primeiro_fila(f)));
    remove_fila(f);          // remove da fila
    printf("▶▶ Pulando: ");
    printf("%s - %s\n", itemF.nome, itemF.artista);
    insere_fim_lista(p, itemF); // adiciona a musica que acabou de tocar no final da playlist
    printf("♫  Tocando agora: %s - %s\n", itemP.nome, itemP.artista); // vai para a primeira da playlist
    return 0;
  }
    
  //condição de esta tocando playlist e começa a tocar fila
  else {
    Musica itemP = retorna_inicio_lista(p); // acessa o primeiro da lista
    Musica itemF = iterador_elemento_lista(iterador_Elemento_fila(iterador_Primeiro_fila(f))); // acessa o primeiro elemento da fila
    printf("▶▶ Pulando: ");
    printf("%s - %s\n", itemP.nome, itemP.artista);
    remove_inicio_lista(p);                    // remove a primeira da lista
    insere_fim_lista(p, itemP); // adiciona a musica que acabou de tocar no final da playlist
    printf("♫  Tocando agora: %s - %s\n", itemF.nome, itemF.artista); // vai para a fila 
    return 1;
  } 
}



iterador Busca_Musica (lista *p, char item[], char item2[]){ // busca a musica
  for (iterador it = iterador_primeiro_lista(p); iterador_valido_lista(it); it = iterador_proximo_lista(it)) { //percorre toda a playlist
    if ((strcmp(item, iterador_elemento_lista(it).nome) == 0) && (strcmp(item2, iterador_elemento_lista(it).artista) == 0)){ //compara se a musica digitada está na playlist
      return it;  //se encontrar a música, retorna o iterador dela da lista
    }
  }
  iterador i; //se a musica não for encontrada, retorna NULL
  iterador_nulo_lista(&i); 
  return i;
}