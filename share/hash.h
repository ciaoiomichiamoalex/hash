#ifndef __HASH_H
#define __HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef INIT_SIZE
#define INIT_SIZE 32
#endif /* INIT_SIZE */

#ifndef MAX_HSTR
#define MAX_HSTR 256
#endif /* MAX_HSTR */

typedef struct node {
    char key[MAX_HSTR];
    char value[MAX_HSTR];
    struct node *_ref;
} Hnode;

typedef Hnode* Node;
typedef Node* Hash;

Hash hash();
unsigned int _indexing(char*);
void push(Hash, char*, char*);
Node pop(Hash, char*);
Node search_key(Hash, char*);
void show_hash(Hash);
unsigned int enum_hash(Hash);
void destroy_hash(Hash);
void destroy_node(Node);

Hash hash() {
    Hash hash = (Hash) malloc(sizeof(Node) * INIT_SIZE);
    for (int i = 0; i < INIT_SIZE; i++) hash[i] = NULL;
    return hash;
}

unsigned int _indexing(char *key) {
    int size = strnlen(key, MAX_HSTR - 1);
    unsigned int index = 0;

    for (int i = 0; i < size; i++) {
        index += key[i];
        index = (index * key[i]) % INIT_SIZE;
    }

    return index;
}

void push(Hash hash, char *key, char *value) {
    Hnode *node = (Node) malloc(sizeof(Hnode));
    strncpy(node->key, key, MAX_HSTR - 1);
    node->key[MAX_HSTR - 1] = '\0';
    strncpy(node->value, value, MAX_HSTR - 1);
    node->value[MAX_HSTR - 1] = '\0';

    unsigned int index = _indexing(node->key);
    node->_ref = hash[index];
    hash[index] = node;
}

Node pop(Hash hash, char *key) {
    unsigned int index = _indexing(key);
    Hnode *res = hash[index];
    Hnode *node = NULL;

    while (res && strncmp(res->key, key, MAX_HSTR - 1)) {
        node = res;
        res = res->_ref;
    }

    if (!res) return NULL;
    if (!node) hash[index] = res->_ref;
    else node->_ref = res->_ref;

    return res;
}

Node search_key(Hash hash, char *key) {
    unsigned int index = _indexing(key);
    Hnode *res = hash[index];

    while (res && strncmp(res->key, key, MAX_HSTR - 1))
        res = res->_ref;
    return res;
}

void show_hash(Hash hash) {
    int rows = 0;

    for (int i = 0; i < INIT_SIZE; i++) {
        if (hash[i]) {
            Hnode *node = hash[i];

            while (node) {
                printf("%s\n  \"%s\": \"%s\"",
                    (rows ? "," : "{"), node->key, node->value);
                node = node->_ref;
                rows++;
            }
        }
    }

    printf("%s}\n", (rows ? "\n" : "{ NULL "));
}

unsigned int enum_hash(Hash hash) {
    unsigned int records = 0;

    for (int i = 0; i < INIT_SIZE; i++) {
        if (hash[i]) {
            Hnode *node = hash[i];

            while (node) {
                records++;
                node = node->_ref;
            }
        }
    }

    return records;
}

void destroy_hash(Hash hash) {
    for (int i = 0; i < INIT_SIZE; i++)
        if (hash[i]) destroy_node(hash[i]);
    free(hash);
}

void destroy_node(Hnode *node) {
    if (node) {
        destroy_node(node->_ref);
        free(node);
    }
}

#endif /* __HASH_H */
