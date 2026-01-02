#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

#include "internal.h"
#include "mf_types.h"
#include "process_maps.h"

int main(void)
{
    struct mf_process proc = {
        .pid = getpid(),
        .ctx = NULL
    };

    struct mf_mem_region *regions = NULL;
    size_t count = 0;

    mf_error_t err = mf_linux_enumerate_maps(&proc, &regions, &count);
    if (err != MF_OK) {
        printf("Error: %d\n", err);
        return 1;
    }

    printf("Found %zu memory regions:\n", count);

    for (size_t i = 0; i < count; i++) {
        printf(
            "%016lx-%016lx perms=%u\n",
            (unsigned long)regions[i].start,
            (unsigned long)regions[i].end,
            regions[i].permissions
        );
    }

    free(regions);
    return 0;
}
