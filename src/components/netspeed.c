
#include <limits.h>
#include <stdio.h>
#include <stdint.h>

#include "../slstatus.h"
#include "../util.h"

#define NET_RX_BYTES "/sys/class/net/enp2s0/statistics/rx_bytes"
#define NET_TX_BYTES "/sys/class/net/enp2s0/statistics/tx_bytes"

const char *netspeed_rx(void) {
	uintmax_t oldrxbytes;
	static uintmax_t rxbytes;
	extern const unsigned int interval;

	oldrxbytes = rxbytes;

	if (pscanf(NET_RX_BYTES, "%ju", &rxbytes) != 1)
		return NULL;

	if (oldrxbytes == 0)
		return NULL;

	return fmt_human((rxbytes - oldrxbytes) * 1000 / interval);
}

const char *netspeed_tx(void) {
	uintmax_t oldtxbytes;
	static uintmax_t txbytes;
	extern const unsigned int interval;

	oldtxbytes = txbytes;

	if (pscanf(NET_TX_BYTES, "%ju", &txbytes) != 1)
		return NULL;

	if (oldtxbytes == 0)
		return NULL;

	return fmt_human((txbytes - oldtxbytes) * 1000 / interval);
}
