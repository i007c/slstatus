/* See LICENSE file for copyright and license details. */
#include <errno.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

char *argv0;

static void
verr(const char *fmt, va_list ap)
{
    if (argv0 && strncmp(fmt, "usage", sizeof("usage") - 1)) {
        fprintf(stderr, "%s: ", argv0);
    }

    vfprintf(stderr, fmt, ap);

    if (fmt[0] && fmt[strlen(fmt) - 1] == ':') {
        fputc(' ', stderr);
        perror(NULL);
    } else {
        fputc('\n', stderr);
    }
}

void
warn(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    verr(fmt, ap);
    va_end(ap);
}

void
die(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    verr(fmt, ap);
    va_end(ap);

    exit(1);
}

static int
evsnprintf(char *str, size_t size, const char *fmt, va_list ap)
{
    int ret;

    ret = vsnprintf(str, size, fmt, ap);

    if (ret < 0) {
        warn("vsnprintf:");
        return -1;
    } else if ((size_t)ret >= size) {
        warn("vsnprintf: Output truncated");
        return -1;
    }

    return ret;
}

int
esnprintf(char *str, size_t size, const char *fmt, ...)
{
    va_list ap;
    int ret;

    va_start(ap, fmt);
    ret = evsnprintf(str, size, fmt, ap);
    va_end(ap);

    return ret;
}

const char *bprintf(const char *fmt, ...) {
    va_list ap;
    int ret;

    va_start(ap, fmt);
    ret = evsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);

    return (ret < 0) ? NULL : buf;
}

const char *fmt_human(uintmax_t num) {
    const char *prefix[] = { "B", "K", "M", "G", "T", "P", "E", "Z", "Y" };

    uint8_t i;
    int64_t scaled = num;
    for (i = 0; i < 9 && scaled >= 1024; i++) {
        scaled /= 1024;
    }

    return bprintf("%3ld %s", scaled, prefix[i]);
}

int pscanf(const char *path, const char *fmt, ...) {
    FILE *fp;
    va_list ap;
    int n;

    if (!(fp = fopen(path, "r"))) {
        warn("fopen '%s':", path);
        return -1;
    }
    va_start(ap, fmt);
    n = vfscanf(fp, fmt, ap);
    va_end(ap);
    fclose(fp);

    return (n == EOF) ? -1 : n;
}
