#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM_CHAVES 2
#define NUM_FILHOS NUM_CHAVES + 1

typedef struct no {
    int num_chaves_inserida;
    int chaves[NUM_CHAVES];
    struct no * filhos[NUM_FILHOS];
} NO;

int main(int argc, char *argv[]) {
    //Cria no vazio
    // NO raiz = malloc(sizeof(NO));
    // for (int i = 0; i < NUM_CHAVES; ++i) {raiz->chaves = NULL;

    FILE * file = fopen(argv[1], "r");
    char comando[7];
    int numero;
    
    while (fscanf(file, "%s %i", comando, &numero) != EOF) {
        if (strcmp(comando, "insere") == 0) {
            printf("%s %i\n", comando, numero);
        }

        if (strcmp(comando, "remove") == 0) {
            printf("%s %i\n", comando, numero);
        }

        if (strcmp(comando, "imprime") == 0) {
            printf("%s\n", comando);
        }

        if (strcmp(comando, "fim") == 0) {
            printf("%s\n", comando);
        }   
    }
}