#include "analyzer.h"
#include <stdlib.h>

mf_error_t mf_region_analyze(
    mf_region_analyzer_t *analyzer,
    const mf_snapshot_t *snapshot
) {
    if (!analyzer || !snapshot)
        return MF_ERR_INVALID_ARGUMENT;

    mf_list_init(&analyzer->regions);

    size_t count = mf_snapshot_region_count(snapshot);
    const struct mf_mem_region *regions =
        mf_snapshot_regions(snapshot);

    if (!regions)
        return MF_ERR_INTERNAL;

    for (size_t i = 0; i < count; i++) {
        mf_region_t *r = calloc(1, sizeof(*r));
        if (!r)
            return MF_ERR_NO_MEMORY;

        r->mem  = &regions[i];
        r->type = mf_region_classify(r->mem);

        mf_list_push_back(&analyzer->regions, &r->node);
    }

    return MF_OK;
}

void mf_region_analyzer_clear(mf_region_analyzer_t *analyzer) {
    if (!analyzer)
        return;

    mf_list_node_t *node = analyzer->regions.head;
    while (node) {
        mf_list_node_t *next = node->next;
        mf_region_t *r =
            (mf_region_t *)((char *)node -
            offsetof(mf_region_t, node));

        free(r);
        node = next;
    }

    mf_list_init(&analyzer->regions);
}
