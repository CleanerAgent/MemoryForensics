#ifndef MF_LINUX_PROCESS_MAPS_H
#define MF_LINUX_PROCESS_MAPS_H

#include <stddef.h>
#include "internal.h"
#include "mf_types.h"

mf_error_t mf_linux_enumerate_maps(
    struct mf_process *process,
    struct mf_mem_region **regions,
    size_t *count
);

#endif
