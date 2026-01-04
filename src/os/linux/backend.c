#include "backend.h"

#include "process_maps.h"
#include "process_memory.h"

/* Attach/detach */

static mf_error_t linux_attach_process(struct mf_process *process)
{
    if (!process) {
        return MF_ERR_INVALID_ARGUMENT;
    }

    /* No Linux, we don't need to "attach" explicitly.
       Access is validated lazily via /proc. */

    return MF_OK;
}

static void linux_detach_process(struct mf_process *process)
{
    (void)process;
}

/* Backend descriptor */

static struct mf_os_backend linux_backend = {
    .name = "linux",

    .attach_process = linux_attach_process,
    .detach_process = linux_detach_process,

    .enumerate_regions = mf_linux_enumerate_maps,
    .read_memory = mf_linux_read_memory
};

struct mf_os_backend *mf_linux_backend(void)
{
    return &linux_backend;
}
