#ifndef __HASH_H
#define __HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef INIT_HASH_SIZE
#define INIT_HASH_SIZE 32
#endif /* INIT_HASH_SIZE */

/**
 * @brief A node of hashmap, made by key-value.
 * @details Every node of hashmap is a linked list for managing collisions,
 *          it contains a reference to the next node that can be NULL if
 *          there isn't collisions or if it's the last one node.
 *
 * @param key (char*) The key string used to identify the value.
 * @param value (char*) The value string associated to the key.
 * @param reference (Node*) A pointer to the next node.
 */
typedef struct node {
    char *key;
    char *value;
    struct node *reference;
} Node;

/**
 * @brief The hashmap.
 * @details An array of pointer to linked list of nodes (Node*[]),
 *          every cell contains a pointer to a node or NULL.
 */
typedef Node** Hash;

Hash hash();
unsigned int hash_index(char*);
int push(Hash, char*, char*);
Node* pop(Hash, char*);
Node* search_key(Hash, char*);
void show_hash(Hash);
unsigned int enum_hash(Hash);
void destroy_hash(Hash);
void destroy_nodes(Node*);

/**
 * @brief Create and initialize new hashmap. (malloc)
 * @details Allocates memory for a new hashmap and initialize all position to NULL,
 *          the size of the hashmap is defined in INIT_HASH_SIZE constant, defaults: 32.
 *
 * @return (Hash) A pointer to new hashmap, or NULL if memory allocation failed.
 */
Hash hash() {
    Hash hash = (Hash) malloc(sizeof(Node*) * INIT_HASH_SIZE);
    if (!hash) return NULL;

    for (int i = 0; i < INIT_HASH_SIZE; i++) hash[i] = NULL;
    return hash;
}

/**
 * @brief Calculate the key index in the hashmap.
 * @details By an algorithm it calculate the position of the node in the hashmap
 *          on the key string value. DO NOT USE this function into source code!
 *
 * @param key (char*) The key for index calculation.
 * @return (unsigned int) The index calcutaled.
 */
unsigned int hash_index(char *key) {
    int size = strlen(key);
    unsigned int index = 0;

    for (int i = 0; i < size; i++) {
        index += key[i];
        index = (index * key[i]) % INIT_HASH_SIZE;
    }

    return index;
}

/**
 * @brief Add or update new key-value node to the hashmap. (malloc)
 * @details Is allocated memory for the node and for the two strings (key and value).
 *
 * @param hash (Hash) The hashmap where add the node.
 * @param key (char*) The key string.
 * @param value (char*) The value string.
 * @return (int) Zero if successful, or negative value if memory allocation failed.
 */
int push(Hash hash, char *key, char *value) {
    if (!hash || !key || !value) return -1;

    Node *existing_node = search_key(hash, key);
    if (existing_node) {
        char *previous_value = existing_node->value;

        existing_node->value = strdup(value);
        if (!existing_node->value) {
            existing_node->value = previous_value;
            return -2;
        }

        if (previous_value) free(previous_value);
    } else {
        Node *node = (Node*) malloc(sizeof(Node));
        if (!node) return -3;
        node->key = strdup(key);
        node->value = strdup(value);

        if (!node->key || !node->value) {
            if (node->key) free(node->key);
            if (node->value) free(node->value);
            free(node);
            return -4;
        }

        unsigned int index = hash_index(key);
        node->reference = hash[index];
        hash[index] = node;
    }

    return 0;
}

/**
 * @brief Remove a node from the hashmap. (malloc)
 * @details Search the node to remove by the key string value and return a
 *          pointer to it without deallocating it. The node is still allocated!
 *
 * @param hash (Hash) The hashmap where remove the node.
 * @param key (char*) The key string to find.
 * @return (Node*) A pointer to the node removed, or NULL if not found.
 */
Node* pop(Hash hash, char *key) {
    if (!hash || !key) return NULL;

    unsigned int index = hash_index(key);
    Node *res = hash[index];
    Node *node = NULL;

    while (res && strcmp(res->key, key)) {
        node = res;
        res = res->reference;
    }

    if (!res) return NULL;
    if (!node) hash[index] = res->reference;
    else node->reference = res->reference;

    res->reference = NULL;
    return res;
}

/**
 * @brief Search a node in the hashmap by key.
 * @details Search the node by the key string value without removing it,
 *          just return a pointer to it.
 *
 * @param hash (Hash) The hashmap where search the node.
 * @param key (char*) The key string.
 * @return A pointer the to node in the hashmap.
 */
Node* search_key(Hash hash, char *key) {
    if (!hash || !key) return NULL;

    unsigned int index = hash_index(key);
    Node *node = hash[index];

    while (node && strcmp(node->key, key))
        node = node->reference;
    return node;
}

/**
 * @brief Print the hashmap content.
 *
 * @param hash (Hash) The hashmap to print.
 */
void show_hash(Hash hash) {
    int rows = 0;

    for (int i = 0; i < INIT_HASH_SIZE && hash; i++) {
        if (hash[i]) {
            Node *node = hash[i];

            while (node) {
                printf("%s\n  \"%s\": \"%s\"",
                    (rows ? "," : "{"), node->key, node->value);
                node = node->reference;
                rows++;
            }
        }
    }

    printf("%s}\n", (rows ? "\n" : "{ NULL "));
}

/**
 * @brief Count the number of records stored into the hashmap.
 *
 * @param hash (Hash) The hashmap.
 * @return (int) The number of records into the hashmap.
 */
unsigned int enum_hash(Hash hash) {
    if (!hash) return 0;
    unsigned int records = 0;

    for (int i = 0; i < INIT_HASH_SIZE; i++) {
        if (hash[i]) {
            Node *node = hash[i];

            while (node) {
                records++;
                node = node->reference;
            }
        }
    }

    return records;
}

/**
 * @brief Deallocate all nodes of the hashmap. (free)
 *
 * @param hash (Hash) The hashmap to destroy.
 */
void destroy_hash(Hash hash) {
    if (!hash) return;

    for (int i = 0; i < INIT_HASH_SIZE; i++)
        if (hash[i]) destroy_nodes(hash[i]);
    if (hash) free(hash);
}

/**
 * @brief Deallocate a linked list of nodes or a single one. (free)
 * @details Deallocate the entire linked list starting by the node in input,
 *          or just the node in input if it's not connected to any other.
 *
 * @param node (Node*) The first node of the list.
 */
void destroy_nodes(Node *node) {
    if (node) {
        destroy_nodes(node->reference);
        if (node->key) free(node->key);
        if (node->value) free(node->value);
        free(node);
    }
}

#endif /* __HASH_H */
