#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM_CHAVES 2
#define NUM_FILHOS NUM_CHAVES + 1

typedef struct no {
    int num_chaves_inserida;
    int chaves[NUM_CHAVES];
    struct no * filhos[NUM_FILHOS];
} NO_AUX, * NO;

NO noConstructor () {
    NO aux = malloc(sizeof(NO_AUX));
    aux->num_chaves_inserida = 0;
    for (int i = 0; i < NUM_CHAVES; ++i) aux->chaves[i] = -1;
    for (int i = 0; i < NUM_FILHOS; ++i) aux->filhos[i] = NULL;

    return aux;
}

int compare(const void* a, const void* b) {
     int int_a = * ( (int*) a );
     int int_b = * ( (int*) b );

     if ( int_a == int_b ) return 0;
     else if ( int_a < int_b ) return -1;
     else return 1;
}

int main(int argc, char *argv[]) {
    // Cria no raiz
    NO raiz = NULL;

    // Abre arquivo
    FILE * file = fopen(argv[1], "r");
    char comando[7];
    int numero;
    
    while (fscanf(file, "%s %i", comando, &numero) != EOF) {
        // Comando insere
        if (strcmp(comando, "insere") == 0) {
            printf("%s %i\n", comando, numero);

            if (raiz == NULL) {
                raiz = noConstructor();
            } else {
                NO aux = raiz;
                int inserido = 0;

                while (inserido == 0) {
                    if (aux->num_chaves_inserida < NUM_CHAVES) {
                        aux->chaves[aux->num_chaves_inserida] = numero;
                        qsort(aux->chaves, NUM_CHAVES, sizeof(int), compare);
                        aux->num_chaves_inserida++;
                        inserido = 1;
                    } else {
                        
                        inserido = 1;
                    }
                }
            }

            for (int i = 0; i < NUM_CHAVES; i++) printf("%i\n", raiz->chaves[i]);
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
