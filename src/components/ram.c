
#include <stdio.h>
#include <stdint.h>

#include "../util.h"

const char *ram_perc(void) {
    uintmax_t total, free, buffers, cached;

    if (pscanf("/proc/meminfo",
               "MemTotal: %ju kB\n"
               "MemFree: %ju kB\n"
               "MemAvailable: %ju kB\n"
               "Buffers: %ju kB\n"
               "Cached: %ju kB\n",
               &total, &free, &buffers, &buffers, &cached) != 5) {
        return NULL;
    }

    if (total == 0) return NULL;
    

    return bprintf("%d", 100 * ((total - free) - (buffers + cached)) / total);
}
