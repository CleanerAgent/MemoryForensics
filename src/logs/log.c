#include "log.h"
#include <time.h>

/* ============================
 * Global state
 * ============================ */

static mf_log_level_t g_log_level = MF_LOG_NONE;
static FILE *g_log_output = NULL;

/* ============================
 * Internal helpers
 * ============================ */

static const char *level_to_string(mf_log_level_t level)
{
    switch (level) {
        case MF_LOG_ERROR: return "ERROR";
        case MF_LOG_WARN:  return "WARN";
        case MF_LOG_INFO:  return "INFO";
        case MF_LOG_DEBUG: return "DEBUG";
        case MF_LOG_TRACE: return "TRACE";
        default:           return "NONE";
    }
}

static void get_timestamp(char *buf, size_t size)
{
    time_t now = time(NULL);
    struct tm tm_now;

#if defined(_WIN32)
    localtime_s(&tm_now, &now);
#else
    localtime_r(&now, &tm_now);
#endif

    strftime(buf, size, "%Y-%m-%d %H:%M:%S", &tm_now);
}

/* ============================
 * Public internal API
 * ============================ */

void mf_log_set_level(mf_log_level_t level)
{
    g_log_level = level;
}

void mf_log_set_output(FILE *out)
{
    g_log_output = out;
}

void mf_log(
    mf_log_level_t level,
    const char *component,
    const char *fmt,
    ...
)
{
    if (level == MF_LOG_NONE || level > g_log_level) {
        return;
    }

    if (!g_log_output) {
        g_log_output = stderr;
    }

    char timestamp[32];
    get_timestamp(timestamp, sizeof(timestamp));

    fprintf(
        g_log_output,
        "[%s] [%s] [%s] ",
        timestamp,
        level_to_string(level),
        component ? component : "core"
    );

    va_list args;
    va_start(args, fmt);
    vfprintf(g_log_output, fmt, args);
    va_end(args);

    fputc('\n', g_log_output);
    fflush(g_log_output);
}
