#ifndef MF_LOG_H
#define MF_LOG_H

#include <stdio.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ============================
 * Log levels
 * ============================ */

typedef enum {
    MF_LOG_NONE = 0,
    MF_LOG_ERROR,
    MF_LOG_WARN,
    MF_LOG_INFO,
    MF_LOG_DEBUG,
    MF_LOG_TRACE
} mf_log_level_t;

/* ============================
 * Configuration
 * ============================ */

/* Set global log level */
void mf_log_set_level(mf_log_level_t level);

/* Set output stream (default: stderr) */
void mf_log_set_output(FILE *out);

/* ============================
 * Logging API (internal)
 * ============================ */

void mf_log(
    mf_log_level_t level,
    const char *component,
    const char *fmt,
    ...
);

/* ============================
 * Convenience macros
 * ============================ */

#define MF_LOG_ERROR(comp, fmt, ...) \
    mf_log(MF_LOG_ERROR, comp, fmt, ##__VA_ARGS__)

#define MF_LOG_WARN(comp, fmt, ...) \
    mf_log(MF_LOG_WARN, comp, fmt, ##__VA_ARGS__)

#define MF_LOG_INFO(comp, fmt, ...) \
    mf_log(MF_LOG_INFO, comp, fmt, ##__VA_ARGS__)

#define MF_LOG_DEBUG(comp, fmt, ...) \
    mf_log(MF_LOG_DEBUG, comp, fmt, ##__VA_ARGS__)

#define MF_LOG_TRACE(comp, fmt, ...) \
    mf_log(MF_LOG_TRACE, comp, fmt, ##__VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif /* MF_LOG_H */
