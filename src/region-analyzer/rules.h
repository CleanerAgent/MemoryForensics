#pragma once

#include "../mf_types.h"

/* Internal region classification */
typedef enum {
    MF_REGION_UNKNOWN = 0,
    MF_REGION_CODE,
    MF_REGION_HEAP,
    MF_REGION_STACK,
    MF_REGION_MAPPED
} mf_region_type_t;

/* Classify a memory region based on its attributes */
mf_region_type_t mf_region_classify(
    const struct mf_mem_region *region
);
