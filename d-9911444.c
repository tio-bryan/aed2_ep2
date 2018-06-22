#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM_CHAVES 2
#define NUM_FILHOS NUM_CHAVES + 1

typedef struct no {
    int num_chaves_inserida;
    int chaves[NUM_CHAVES];
    struct no * filhos[NUM_FILHOS];
} NO_atual, * NO;

NO noConstructor () {
    NO atual = malloc(sizeof(NO_atual));
    atual->num_chaves_inserida = 0;
    for (int i = 0; i < NUM_CHAVES; ++i) atual->chaves[i] = 2147483647;
    for (int i = 0; i < NUM_FILHOS; ++i) atual->filhos[i] = NULL;

    return atual;
}

// Funcao compare para o qsort http://www.cplusplus.com/reference/cstdlib/qsort/
int compare (const void * a, const void * b) {
    return ( *(int*)a - *(int*)b );
}

int main(int argc, char *argv[]) {
    // Cria no raiz
    NO raiz = NULL;

    // Nos para percorrer a arvore
    NO paiDoAtual = NULL;
    NO atual = NULL;

    // Abre arquivo
    FILE * file = fopen(argv[1], "r");
    char comando[7];
    int numero;
    
    while (fscanf(file, "%s %i", comando, &numero) != EOF) {
        // Comando insere
        if (strcmp(comando, "insere") == 0) {
            printf("%s %i\n", comando, numero); 

            if (raiz == NULL) raiz = noConstructor();

            NO atual = raiz;

            // Vai até a folha a ser inserida (insercao por baixo)
            int eh_folha = 1;
            for (int i = 0; i < NUM_FILHOS; i++) if (atual->filhos[i] != NULL) eh_folha = 0;

            if (eh_folha == 0) {
                for (int i = 0; i < NUM_CHAVES; i++) {
                    if (numero < atual->chaves[i]);
                }
            }

            if (atual->num_chaves_inserida < NUM_CHAVES) {
                atual->chaves[atual->num_chaves_inserida] = numero;
                qsort(atual->chaves, NUM_CHAVES, sizeof(int), compare);
                atual->num_chaves_inserida++;

            } else { // Overflow... Split
                // Montra array de chaves + o overflow para depois dividir em esq, meio, dir
                int array_split[NUM_FILHOS];
                
                for (int i = 0; i < NUM_CHAVES; i++) {
                    array_split[i] = atual->chaves[i];
                }

                array_split[NUM_CHAVES] = numero;

                int esq[NUM_CHAVES];
                int meio[NUM_CHAVES];
                int dir[NUM_CHAVES];

                for (int i = 0; i < NUM_CHAVES; ++i) esq[i] = 2147483647;
                for (int i = 0; i < NUM_CHAVES; ++i) meio[i] = 2147483647;
                for (int i = 0; i < NUM_CHAVES; ++i) dir[i] = 2147483647;
                
                for (int i = 0; i < NUM_CHAVES / 2; ++i) esq[i] = array_split[i];
                meio[0] = array_split[NUM_CHAVES / 2];
                for (int i = NUM_CHAVES / 2 + 1; i < NUM_FILHOS; ++i) dir[i - (NUM_CHAVES / 2 + 1)] = array_split[i];
                
                if (atual == raiz) {
                    raiz->filhos[0] = noConstructor();
                    for (int i = 0; i < NUM_CHAVES; i++) raiz->filhos[0]->chaves[i] = esq[i];

                    for (int i = 0; i < NUM_CHAVES; i++) raiz->chaves[i] = meio[i];

                    raiz->filhos[1] = noConstructor();
                    for (int i = 0; i < NUM_CHAVES; i++) raiz->filhos[1]->chaves[i] = dir[i];

                } else {
                    
                }
            }
            //printf("%i\n", raiz->chaves[0]);
            //for (int i = 0; i < NUM_CHAVES; i++) printf("%i\n", raiz->filhos[0]->chaves[i]);
        }

        if (strcmp(comando, "remove") == 0) {
            //printf("%s %i\n", comando, numero);
        }

        if (strcmp(comando, "imprime") == 0) {
            //printf("%s\n", comando);
        }

        if (strcmp(comando, "fim") == 0) {
            //printf("%s\n", comando);
        }   
    }
}
