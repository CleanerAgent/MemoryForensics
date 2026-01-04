#include "rules.h"

/*
 * Very conservative initial classification.
 * This should evolve over time.
 */
mf_region_type_t mf_region_classify(
    const struct mf_mem_region *region
) {
    if (!region)
        return MF_REGION_UNKNOWN;

    /* Example permission-based heuristics */
    const uint32_t p = region->permissions;

    /* Executable regions are likely code */
    if (p & 0x4) { /* example: EXEC bit */
        return MF_REGION_CODE;
    }

    /* Writable but non-executable regions */
    if ((p & 0x2) && !(p & 0x4)) {
        return MF_REGION_MAPPED;
    }

    return MF_REGION_UNKNOWN;
}
