#include <stdlib.h>

#include "internal.h"
#include "mf_types.h"

/* Linux backend */
#include "os/linux/backend.h"

mf_error_t mf_context_create(struct mf_context **out)
{
    if (!out) {
        return MF_ERR_INVALID_ARGUMENT;
    }

    struct mf_context *ctx = calloc(1, sizeof(*ctx));
    if (!ctx) {
        return MF_ERR_NO_MEMORY;
    }

    /* Attach Linux backend */
    ctx->os = mf_linux_backend();

    if (!ctx->os) {
        free(ctx);
        return MF_ERR_INTERNAL;
    }

    *out = ctx;
    return MF_OK;
}

void mf_context_destroy(struct mf_context *ctx)
{
    if (!ctx) return;

    /* nothing backend-specific yet */
    free(ctx);
}
