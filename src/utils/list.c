#include "list.h"

void mf_list_init(mf_list_t *list) {
    list->head = NULL;
    list->tail = NULL;
    list->count = 0;
}

void mf_list_push_back(mf_list_t *list, mf_list_node_t *node) {
    node->next = NULL;
    node->prev = list->tail;

    if (list->tail)
        list->tail->next = node;
    else
        list->head = node;

    list->tail = node;
    list->count++;
}

void mf_list_remove(mf_list_t *list, mf_list_node_t *node) {
    if (node->prev)
        node->prev->next = node->next;
    else
        list->head = node->next;

    if (node->next)
        node->next->prev = node->prev;
    else
        list->tail = node->prev;

    node->next = node->prev = NULL;
    list->count--;
}
