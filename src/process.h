#ifndef MF_PROCESS_H
#define MF_PROCESS_H

#include "mf_types.h"

/* Create / destroy process handle */
mf_error_t mf_process_create(
    mf_context_t *ctx,
    int pid,
    mf_process_t **out
);

void mf_process_destroy(mf_process_t *process);

#endif /* MF_PROCESS_H */
