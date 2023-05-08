
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

#include "../util.h"

extern int channel;

const char *sound(void) {
    bool status[2];

    lseek(channel, 0, SEEK_SET);
    read(channel, status, sizeof(status));

    return bprintf("%d %d", status[0], status[1]);
}
