#ifndef MF_CONTEXT_H
#define MF_CONTEXT_H

#include "mf_types.h"

/* Create / destroy library context */
mf_error_t mf_context_create(mf_context_t **out);
void mf_context_destroy(mf_context_t *ctx);

#endif /* MF_CONTEXT_H */
