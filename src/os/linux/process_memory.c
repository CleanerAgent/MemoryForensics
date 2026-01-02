#include "process_memory.h"

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

#include "internal.h"
#include "mf_types.h"

mf_error_t mf_linux_read_memory(
    struct mf_process *process,
    uintptr_t address,
    void *buffer,
    size_t size
)
{
    if (!process || !buffer || size == 0) {
        return MF_ERR_INVALID_ARGUMENT;
    }

    char path[64];
    snprintf(path, sizeof(path), "/proc/%d/mem", process->pid);

    FILE *fp = fopen(path, "rb");
    if (!fp) {
        return MF_ERR_PROCESS_ACCESS;
    }

    if (fseek(fp, (off_t)address, SEEK_SET) != 0) {
        fclose(fp);
        return MF_ERR_PROCESS_ACCESS;
    }

    size_t nread = fread(buffer, 1, size, fp);
    fclose(fp);

    if (nread != size) {
        return MF_ERR_PROCESS_ACCESS;
    }

    return MF_OK;
}
