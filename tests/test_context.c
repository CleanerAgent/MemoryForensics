#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "internal.h"
#include "mf_types.h"

/* Core */
mf_error_t mf_context_create(struct mf_context **out);
void mf_context_destroy(struct mf_context *ctx);

mf_error_t mf_process_create(
    struct mf_context *ctx,
    int pid,
    struct mf_process **process
);

void mf_process_destroy(struct mf_process *process);

int main(void)
{
    struct mf_context *ctx = NULL;
    struct mf_process *proc = NULL;
    struct mf_mem_region *regions = NULL;
    size_t count = 0;

    mf_error_t err;

    err = mf_context_create(&ctx);
    if (err != MF_OK) {
        printf("context create failed: %d\n", err);
        return 1;
    }

    err = mf_process_create(ctx, getpid(), &proc);
    if (err != MF_OK) {
        printf("process create failed: %d\n", err);
        return 1;
    }

    err = ctx->os->enumerate_regions(proc, &regions, &count);
    if (err != MF_OK) {
        printf("enumerate regions failed: %d\n", err);
        return 1;
    }

    printf("Process %d has %zu memory regions:\n", proc->pid, count);

    for (size_t i = 0; i < count; i++) {
        printf(
            "%016lx-%016lx perms=%u\n",
            regions[i].start,
            regions[i].end,
            regions[i].permissions
        );
    }

    free(regions);
    mf_process_destroy(proc);
    mf_context_destroy(ctx);

    return 0;
}
