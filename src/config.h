
/* interval between updates (in ms) */
const unsigned int interval = 500;

/* text to show if no value can be retrieved */
static const char unknown_str[] = "n/a";

/* maximum output string length */
#define MAXLEN 2048


static const struct arg args[] = {
    /* function format              argument */
    { netspeed_rx,   "| %s ",             NULL },
    { netspeed_tx,   "%s | ",             NULL },
    { keymap,   "%s | ",                  NULL },
    { sound,    "%s | ",                  NULL },
    { cpu_perc, "%2s%% ",                 NULL },
    { ram_perc, "%2s%% | ",               NULL },
    { datetime, "%s",            "%a %m/%d %T" },
};
