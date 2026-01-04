#pragma once

#include "../utils/list.h"
#include "../mf_types.h"

typedef struct mf_map_region {
    mf_list_node_t node;
    const struct mf_mem_region *mem;
} mf_map_region_t;

typedef struct {
    mf_list_t regions;
} mf_memory_map_t;

void mf_memory_map_init(mf_memory_map_t *map);
void mf_memory_map_add(
    mf_memory_map_t *map,
    const struct mf_mem_region *region
);
const struct mf_mem_region *mf_memory_map_find(
    const mf_memory_map_t *map,
    uintptr_t address
);
void mf_memory_map_clear(mf_memory_map_t *map);
