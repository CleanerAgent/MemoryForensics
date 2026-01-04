#pragma once

#include "../utils/list.h"
#include "../snapshot.h"
#include "rules.h"

typedef struct mf_region {
    mf_list_node_t node;

    /* Reference to snapshot region (read-only) */
    const struct mf_mem_region *mem;

    /* Classification result */
    mf_region_type_t type;
} mf_region_t;

typedef struct {
    mf_list_t regions;
} mf_region_analyzer_t;

/* Initialize analyzer and classify snapshot regions */
mf_error_t mf_region_analyze(
    mf_region_analyzer_t *analyzer,
    const mf_snapshot_t *snapshot
);

/* Cleanup analyzer-owned data */
void mf_region_analyzer_clear(mf_region_analyzer_t *analyzer);
