/*
Desafio Mega-sena - C

Faça um programa que gere N jogos para o usuário concorrer à mega-sena. O usuário deve
informar a quantidade M de bolas por jogo, que pode ser de 6 a 15 bolas. 
Dica: uma sequência não tem números repetidos.

Requisitos - o seu programa deve:
   //- Obter do usuário a quantidade N de jogos. (0 < N <= 20)
   //- Obter do usuário a quantidade M de dezenas em cada um dos jogos. (6 <= M <= 15)
   //- Gerar N conjuntos de M dezenas contidas entre 1 e 60 de forma
aleatória.
   //- Garantir que não haja dezenas repetidas em um mesmo jogo.
   //- Exibir os jogos gerados.
   //- Fazer uso de ponteiros e alocação dinâmica de memória
   //- Acrescentar comentários explicativos em inglês

Bônus - não é necessário, mas conta positivamente :
//- Ordenação das sequências
//- Uso de recursividade
- Readme no Github com orientações de compilação e para rodar a aplicação.
//- Legibilidade do código é sempre visto com bons olhos!

Assim que você estiver satisfeito(a) com a solução pode adicionar o projeto no GitHub e nos enviar o link ou então enviar os arquivos zipados por email.*/
#include <stdio.h>
#include <stdlib.h>

//this function alocate the space to store the dozens and randomly generate its values
char * gera_jogo(char M){
    int i = 0, j = 0;
    char *ptr = (char *) malloc(M * sizeof(char)); //alocating room for M dozens for the game.
    if(ptr == NULL){ //checking if the malloc call was successful
        printf("something went wrong");
        exit(2);
    }

    for(i = 0; i < M; i++){ //randomly generating M dozens
        j = 0;
        ptr[i] = (rand() % 60) + 1;
        while(j<i){ //making sure I am not repeating a dozen
            if(ptr[i] == ptr[j]){
                ptr[i] = (rand() % 60) + 1;
                j = 0;
            }
            j++;
        }
    }
    
    return ptr;
    
}

//simple bubble sort algorithm
void simpleBubbleSort(char *vetor, char vector_size){
    int i = 0, j = 0;
    for(i = 0; i < vector_size-1;i++){
        for(j = 0; j < vector_size-i-1;j++){
            if(vetor[j] > vetor[j+1]){
                vetor[j] += vetor[j+1];
                vetor[j+1] = vetor[j]-vetor[j+1];
                vetor[j] -= vetor[j+1];
            }
        }
    }

}

//this function will dinamically alocate one vector for each game.
void gera_jogos(char ***jogos, char N, char M){

    *jogos = (char **) malloc(N*sizeof(char*)); //alocating N vectors for N games
    if(*jogos == NULL){ //checking if the malloc call was successful
        printf("something went wrong");
        exit(1);
    }
    while(N--){
        (*jogos)[N] = NULL;
        
        (*jogos)[N] = gera_jogo(M); //generating random dozens
        
    }
}

//this function will ask the user for inputs as it will also validate the user's input.
void get_input(char *N, char *M){
    do{
        printf("digite o numero de jogos (0 < N <= 20)\n");
        scanf("%d",N);
    }while(*N <= 0 || *N > 20);
    
    do{
        printf("digite a quantidade de dezenas em cada um dos jogos (6 <= M <= 15)\n");
        scanf("%d",M);
    }while(*M < 6 || *M > 15);
}

//before the program ends we need to free the memory we alocate to store the games
void libera_jogos(char **jogos, char N){
    while(N--){
        free(jogos[N]);
    }
    free(jogos);
}

//this function will run bubbleSort(a sorting algorithm) in each game.
//there was no need for this function to be recursive, I did it on porpuse to check all the elements in the list ;)
void ordena_jogos(char **jogos,char N, char M){
    if(!N--) return; //base case: if N = 0 stop.

    simpleBubbleSort(jogos[N],M);
    ordena_jogos(jogos,N,M);
}

//this function shows the generated games in terminal
void printa_jogos(char **jogos, char N, char M){
    int i;
    while(N--){
        for(i = 0; i < M;i++){
            printf("%3d",jogos[N][i]);
        }
        printf("\n");
    }
}

int main(void){
    char N = 0; //Number of games
    char M = 0; //Number of dozens in a game
    char ** jogos = NULL;

    get_input(&N,&M); //ask the user the number of games and the amount of dozens he wants to generate.
    gera_jogos(&jogos,N,M); //generating the games randomly
    ordena_jogos(jogos,N,M); //ordering the dozens of each game
    printa_jogos(jogos,N,M); //showing the games in the terminal
    libera_jogos(jogos,N); // freeing the space alocated to save the games 

    return 0;
}