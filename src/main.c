#include "hash.h"

int main(int argc, char **argv) {
    Hash hashmap = hash();
    show_hash(hashmap);

    push(hashmap, "name", "John");
    push(hashmap, "surname", "Thomas");
    push(hashmap, "surname", "Murphy");
    push(hashmap, "nickname", "Fury");

    show_hash(hashmap);
    int records_num = enum_hash(hashmap);
    printf("There's %d records!\n", records_num);

    Node *record = search_key(hashmap, "name");
    printf("%s key 'name': %s\n",
        record ? "Found" : "Unfound",
        record ? record->value : "NULL");

    record = search_key(hashmap, "cars");
    printf("%s key 'cars': %s\n",
        record ? "Found" : "Unfound",
        record ? record->value : "NULL");

    record = pop(hashmap, "surname");
    printf("%s key 'surname': %s\n",
        record ? "Found" : "Unfound",
        record ? record->value : "NULL");
    destroy_nodes(record);

    show_hash(hashmap);
    records_num = enum_hash(hashmap);
    printf("There's %d records!\n", records_num);

    destroy_hash(hashmap);
    return 0;
}
