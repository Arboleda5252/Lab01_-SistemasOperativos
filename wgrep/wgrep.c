#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void buscar(FILE *fp, char *termino) {
    char *linea = NULL;
    size_t capacidad = 0;
    ssize_t leido;

    while ((leido = getline(&linea, &capacidad, fp)) != -1) {
        if (strstr(linea, termino) != NULL) {
            printf("%s", linea);
        }
    }

    free(linea);
}

int main(int argc, char *argv[]) {
    // Sin argumentos
    if (argc == 1) {
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    }

    char *termino = argv[1];

    // Solo termino, sin archivos
    if (argc == 2) {
        buscar(stdin, termino);
        exit(0);
    }

    // Con archivos
    for (int i = 2; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("wgrep: cannot open file\n");
            exit(1);
        }

        buscar(fp, termino);
        fclose(fp);
    }

    return 0;
}
