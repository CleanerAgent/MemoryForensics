#pragma once
#include <stddef.h>

typedef struct mf_list_node {
    struct mf_list_node *prev;
    struct mf_list_node *next;
} mf_list_node_t;

typedef struct {
    mf_list_node_t *head;
    mf_list_node_t *tail;
    size_t count;
} mf_list_t;

void mf_list_init(mf_list_t *list);
void mf_list_push_back(mf_list_t *list, mf_list_node_t *node);
void mf_list_remove(mf_list_t *list, mf_list_node_t *node);
