#ifndef MF_LINUX_BACKEND_H
#define MF_LINUX_BACKEND_H

#include "internal.h"

/*
 * Returns a pointer to the Linux OS backend.
 * Singleton-style backend descriptor.
 */
struct mf_os_backend *mf_linux_backend(void);

#endif
