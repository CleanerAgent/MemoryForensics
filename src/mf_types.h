#ifndef MF_TYPES_H
#define MF_TYPES_H

#include <stdint.h>
#include <stddef.h>

/* ============================
 * Error codes
 * ============================ */

typedef enum {
    MF_OK = 0,

    MF_ERR_INVALID_ARGUMENT,
    MF_ERR_NO_MEMORY,
    MF_ERR_PROCESS_ACCESS,

    MF_ERR_INTERNAL,          /* erro interno da lib */
    MF_ERR_SNAPSHOT_FAILED,
    MF_ERR_BACKEND_FAILED

} mf_error_t;


/* ============================
 * Opaque public types
 * ============================ */

typedef struct mf_context mf_context_t;
typedef struct mf_process mf_process_t;

/* ============================
 * Memory region (public read-only)
 * ============================ */

struct mf_mem_region {
    uintptr_t start;
    uintptr_t end;
    uint32_t permissions;
};

#endif /* MF_TYPES_H */
