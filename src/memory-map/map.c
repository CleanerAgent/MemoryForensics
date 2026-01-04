#include "map.h"
#include <stdlib.h>

void mf_memory_map_init(mf_memory_map_t *map) {
    mf_list_init(&map->regions);
}

void mf_memory_map_add(
    mf_memory_map_t *map,
    const struct mf_mem_region *region
) {
    mf_map_region_t *r = calloc(1, sizeof(*r));
    if (!r)
        return;

    r->mem = region;
    mf_list_push_back(&map->regions, &r->node);
}

const struct mf_mem_region *mf_memory_map_find(
    const mf_memory_map_t *map,
    uintptr_t address
) {
    for (mf_list_node_t *n = map->regions.head; n; n = n->next) {
        mf_map_region_t *r =
            (mf_map_region_t *)((char *)n -
            offsetof(mf_map_region_t, node));

        if (address >= r->mem->start &&
            address <  r->mem->end)
            return r->mem;
    }
    return 0;
}

void mf_memory_map_clear(mf_memory_map_t *map) {
    mf_list_node_t *n = map->regions.head;
    while (n) {
        mf_list_node_t *next = n->next;
        free((char *)n - offsetof(mf_map_region_t, node));
        n = next;
    }
    mf_list_init(&map->regions);
}
