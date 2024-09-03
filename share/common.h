#ifndef __COMMON_H
#define __COMMON_H

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

char* console();
char* decode_csv(FILE*, char);
void lowercase(char*);
void raise_error(char*, int);
int random_number(int, int);
char** split(char*, char*);
void swap(char*, char*);
char* trim(char*);
void uppercase(char*);

char* console() {
    char buffer[BUFFER_SIZE] = {0};
    for (int i = 0; (buffer[i] = getchar()) != '\n'; i++) { }
    return strdup(buffer);
}

char* decode_csv(FILE *in, char divider) {
    char buffer[BUFFER_SIZE];
    int i = 0;

    for (; ((buffer[i] = fgetc(in)) != divider) &&
        (buffer[i] != '\n') && (buffer[i] != EOF); i++) { }

    if (!i) return NULL;
    buffer[i] = '\0';
    return strdup(buffer);
}

void lowercase(char *string) {
    for (; *string; string++)
        if ((*string >= 'A') && (*string <= 'Z'))
            *string = *string - 'A' + 'a';
}

void raise_error(char *error, int code) {
    printf("ERROR in %s - %d - %s\n",
        error, errno, strerror(errno));
    printf("EXIT code: %d\n", code);
    exit(code);
}

int random_number(int min, int max) {
    srand(getpid() * time(NULL));
    return rand() % (max - min + 1) + min;
}

char** split(char *string, char *divider) {
    char *buffer[BUFFER_SIZE];
    char *clone = strdup(string);
    char *token = strtok(clone, divider);

    int size = 0;
    for (; token; size++) {
        buffer[size] = strdup(token);
        token = strtok(NULL, divider);
    }
    buffer[size] = NULL;
    free(clone);

    char **res = (char**) malloc(sizeof(char*) * size);
    for (int i = 0; *(res + i) = buffer[i]; i++) { }
    return res;
}

void swap(char *sx, char *dx) {
    char tmp = *sx;
    *sx = *dx;
    *dx = tmp;
}

char* trim(char *string) {
    char buffer[BUFFER_SIZE] = {0};
    int sx = 0, dx = strlen(string) - 1;

    while (isspace(*(string + sx))) sx++;
    while (isspace(*(string + dx))) dx--;

    for (int i = 0; sx <= dx; i++, sx++)
        buffer[i] = *(string + sx);
    return strdup(buffer);
}

void uppercase(char *string) {
    for (; *string; string++)
        if ((*string >= 'a') && (*string <= 'z'))
            *string = *string - 'a' + 'A';
}

#endif /* __COMMON_H */
