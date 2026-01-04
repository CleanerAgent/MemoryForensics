#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

/* API pública */
#include "../src/context.h"
#include "../src/process.h"
#include "../src/snapshot.h"
#include "../src/mf_types.h"

/* interno (ok para teste) */
#include "../src/region-analyzer/analyzer.h"

int main(int argc, char **argv) {
    mf_error_t err;
    mf_context_t *ctx = NULL;
    mf_process_t *proc = NULL;
    mf_snapshot_t *snap = NULL;

    if (argc != 2) {
        fprintf(stderr, "usage: %s <pid>\n", argv[0]);
        return 1;
    }

    int pid = atoi(argv[1]);

    /* Context */
    err = mf_context_create(&ctx);
    if (err != MF_OK) {
        fprintf(stderr, "mf_context_create failed\n");
        return 1;
    }

    /* Process */
    err = mf_process_create(ctx, pid, &proc);
    if (err != MF_OK) {
        fprintf(stderr, "mf_process_create failed\n");
        goto cleanup;
    }

    /* Snapshot */
    err = mf_snapshot_create(proc, &snap);
    if (err != MF_OK) {
        fprintf(stderr, "mf_snapshot_create failed\n");
        goto cleanup;
    }

    size_t region_count = mf_snapshot_region_count(snap);
    printf("[+] snapshot regions: %zu\n", region_count);

    /* Region analyzer */
    mf_region_analyzer_t analyzer;
    err = mf_region_analyze(&analyzer, snap);
    if (err != MF_OK) {
        fprintf(stderr, "mf_region_analyze failed\n");
        goto cleanup;
    }

    size_t analyzed = 0;
    for (mf_list_node_t *n = analyzer.regions.head; n; n = n->next) {
        mf_region_t *r =
            (mf_region_t *)((char *)n -
            offsetof(mf_region_t, node));

        printf(
            "region %zu: [%p - %p] type=%d\n",
            analyzed++,
            (void *)r->mem->start,
            (void *)r->mem->end,
            r->type
        );
    }

    printf("[+] analyzed regions: %zu\n", analyzed);

    mf_region_analyzer_clear(&analyzer);

cleanup:
    mf_snapshot_destroy(snap);
    mf_process_destroy(proc);
    mf_context_destroy(ctx);
    return 0;
}
