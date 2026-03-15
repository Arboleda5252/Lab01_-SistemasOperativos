#include <stdio.h>
#include <stdlib.h>
 
int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("wzip: file1 [file2 ...]\n");
        exit(1);
    }
 
    int count = 0;
    char current = '\0';
 
    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("wzip: cannot open file\n");
            exit(1);
        }
 
        int c;
        while ((c = fgetc(fp)) != EOF) {
            char ch = (char)c;
            if (ch == current) {
                count++;
            } else {
                if (count > 0) {
                    fwrite(&count, sizeof(int), 1, stdout);
                    fwrite(&current, sizeof(char), 1, stdout);
                }
                current = ch;
                count = 1;
            }
        }
        fclose(fp);
    }
 
    if (count > 0) {
        fwrite(&count, sizeof(int), 1, stdout);
        fwrite(&current, sizeof(char), 1, stdout);
    }
 
    return 0;
}