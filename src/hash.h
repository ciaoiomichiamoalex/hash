#ifndef HASH_H
#define HASH_H

#ifndef INIT_HASH_SIZE
#define INIT_HASH_SIZE 32
#endif /* INIT_HASH_SIZE */

/**
 * @brief A node of hashmap, made by key-value.
 * @details Every node of hashmap is a linked list for managing collisions, it contains a reference to the
 *          next node that can be NULL if there isn't collisions or if it's the last one node.
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
 * @details An array of pointer to linked list of nodes (Node*[]), every item contains a pointer to a node or NULL.
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

#endif /* HASH_H */
