# Projeto Prático de Estrutura de Dados 
* Grupo: Daniella Yuka Hirosue, Giulia Namie Azeka, Lara Oliveira Luzeiro e Laura Rieko Marçal Imai
* Desenvolveu-se um sistema que, por meio de uma lista e uma fila, é responsável por emular o comportamento de uma playlist em linguagem C.

## Desenvolvimento 
Na realização da aplicação foram implementados os seguintes recursos:
*Uma fila estática com alocação dinâmica e iteradores, que representa a fila de músicas a serem tocadas preferencialmente.
*Uma lista duplamente encadeada com sentinela e iteradores, que cumpre o papel de reter os dados da playlist, guardando assim as músicas.
*Além disso, temos um arquivo texto, que já possui músicas previamente selecionadas, para que o processo de inserção na playlist seja menos repetitivo para o usuário toda vez que o programa for compilado novamente.

### Sobre a implementação da lista
* Struct lista - é inicializada na main.c e é uma das obrigação do usuário, tendo em vista que não é possível manter a generalidade da lista com o campo struct definido. 
* void inicializa_lista(lista *p) - é a função responsável pela inicialização da lista criada pelo usuário, é necessário se atentar ao fato de que ela demanda um ponteiro para a lista que será inicializada.
* void destruir_lista(lista *p) - a operação que destrói a lista, faz uso da função de remover no início, void lremoveI(lista *p) , para ir eliminando os elementos até que a flag de verificação de lista vazia, a int lvazia(lista *p) , seja atinginda e, nesse momento, um free é realizado para a liberação do espaço alocado que prevenirá o vazamento de memória.
* int vazia_lista(lista *p) - é uma função de tipo inteiro que verifica se a lista está vazia ou não, ou seja, se há ou não elementos inseridos nela, em caso positivo ela retorna 1, e em caso negativo ela retorna 0;
* int insere_inicio_lista(lista *p, T item) - função que deve inserir um elemento ao início da lista, elemento este de tipo T, um tipo genérico que pode ser alterado pelo usuário por demanda. Nesse caso, o tipo int da função possibilita que ao retornarmos 1, tenhamos uma inserção bem sucedida e ao retornarmos 0 temos uma alocação de memória que não ocorreu de modo ideal. 
* int insere_fim_lista(lista *p, T item) - função que realiza as inserções de elemento ao fim da lista, nesse sentido, tem-se novamente o tipo T, que corresponde ao tipo genético do dado que há de ser inserido no fim da lista, este pode ser mudado pelo usuário sob demanda. O princípio do retorno da função segue análogo ao de inserção no início, em que 0 é inserção mal sucedida e 1 bem sucedida.
* void remove_inicio_lista(lista *p) - é a função responsável por retirar elementos a partir do início da lista, para fazer isso, é requerida a verificação de que a lista está ou não vazia, por meio da função int lvazia(lista *p), uma vez que caso a lista esteja vazia não é possível retirar elementos dela.
* void remove_fim_lista(lista *p) - é a função que utilizamos para remover elementos do fim da lista, nesse sentido, é igualmente necessária a verificação de caso vazia, que é presente no lremoveI(lista *p). 
* T retorna_inicio_lista(lista *p) - retorna o primeiro elemento presente na lista, fazendo o uso de iteradores para isso.
* iterador iterador_primeiro_lista(lista *p) - é a função que retorna o iterador contendo o primeiro elemento da lista.
* iterador iterador_proximo_lista(iterador i) - é a função que retorna o próximo iterador, tendo como referência um iterador anterior que é passado como parâmetro da função.
* T iterador_elemento_lista(iterador i) - retorna um dado, do tipo T genérico, que é referenciado pelo iterador, para isso, a função int it_validoL(iterador i) deve ser verdadeira;
* int iterador_valido_lista(iterador i) - verifica se o iterador está de fato apontando para um elemento da lista, retornando verdadeiro caso o iterador não esteja referenciando o sentinela da lista.
* iterador retira_lista(iterador i) - remove um elemento da lista encadeada que está sendo referenciado pelo iterador, entretanto, para isso, é preciso que o iterador seja válido, ou seja se ele de fato está apontando para um elemento que pertence à lista. Se o retorno é positivo, temos que o processo de remoção é feito e posteriormente usa-se o free para desalocar a memória.
* void iterador_nulo_lista(iterador *i) - indica que a busca na lista não encontrou nenhum elemento que corresponda ao desejado, sendo assim um iterador inválido.
* int iterador_vazio_lista(iterador i) - recebe um iterador como parâmetro e verifica se seu elemento atual é NULL, ou seja se sua posição é inválida e aponta para a lista encadeada ou não. Retorna 1 se sim, retorna 0 caso não aponte para o NULL.

### Sobre a implementação da fila
* Struct fila -  é inicializada na main.c e é uma das obrigação do usuário, tendo em vista que não é possível manter a generalidade da lista com o campo struct definido. 
* fila* inicializa_fila(int qtMax) - realiza a inicialização da fila proposta pelo usuário no começo da execução, retornando, assim, o endereço alocado por ela.
* int vazia_fila(fila *f) - retorna verdadeiro caso ela esteja vazia, senão retorna falso, por vazia entende-se que não há elementos presentes na fila.
* int cheia_fila(fila *f) - retorna verdadeiro caso todos os espaços do bloco de memória que correspondem ao vetor da fila estejam ocupados, senão retorna falso, indicando que há espaços disponíveis.
* void limpa_fila(fila *f) - limpa a fila, no sentido de que a percorre, liberando os espaços de memória utilizados.
* void destroi_fila(fila *f) - destrói a fila, desalocando-a ao final da execução
* int insere_fila(fila *f, j dado) - insere, ao final da fila um determinado elemento, seguindo a proposta de FIFO, em que o primeiro a entrar é o primeiro a sair e, portanto, as inserções devem ocorrer sempre ao fim. O tipo da função é inteiro e retorna 1 caso a inserção do dado de tipo j - um tipo genérico que cabe ao usuário definição - tenha ocorrido de maneira adequada, caso a alocação não tenha ocorrido como o proposto, 0 é retornado.
* j* remove_fila(fila *f) - faz a remoção do elemento da fila, seguindo novamente a proposta do FIFO. Nesse sentido, caso a remoção ocorra de maneira adequada, retornar-se-á o ponteiro que indica o elemento a ser removido, senão retorna NULL que indica que não é possível realizar a operação.
* unsigned quantidade_fila(fila *f) - retorna a quantidade de elementos da fila.
* void iterador_inicializa_fila(Iterador *i, fila *f) - inicializa os iteradores, recebendo do usuário um ponteiro para a struct e um ponteiro para a fila. Essa inicialização garante que quando a iteração começar, o iterador já estará apontando para o primeiro elemento da fila.
* Iterador* iterador_Proximo_fila(Iterador *i) - incrementa o índice do elemento atual, passando para o endereço do próximo iterador, que é então retornado.
* Iterador iterador_Primeiro_fila(fila *f) - a função cria um iterador e o passa como parâmetro, verifica se a fila está vazia ou não. Se estiver vazia, o iterador é inicializado com o valor NULL. Caso contrário, o iterador é inicializado com o endereço do primeiro elemento da fila e retorna por fim o iterador criado e inicializado.
* int iterador_Valido_fila(Iterador i) - retorna 1 caso seja válido e 0 se não for. Para realizar essa verificação, a função compara o endereço de memória do elemento atual com o endereço de memória do último elemento da fila, caso ele esteja alocado após ele, é inválido;
* j iterador_Elemento_fila(Iterador i) - retorna o elemento atual dos iteradores, para isso o itValidoF(Iterador i) deve ser verdadeiro.

### Sobre o musica.h
* É este o arquivo responsável por conter a struct que é usada para armazenar os campos de nome e do artista da canção em questão. Pode ser alterado pelo usuário.

### Sobre a main.c
* A aplicação em questão emula o funcionamento de uma playlist de música, que contém também uma fila com as prioridades, em que músicas são selecionadas, reproduzidas e posteriormente inseridas no fim da lista.
