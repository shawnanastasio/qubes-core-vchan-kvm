#include <limits.h>
#include <stdio.h>

#include "libvchan.h"

/**
 * This is a small wrapper library that allows API/ABI compatibility with
 * QubesOS's qubes-core-vchan-xen on libkvmchan.
 */

libvchan_t *libvchan_server_init(int domain, int port, size_t read_min, size_t write_min) {
    return libkvmchan_server_init(domain, port, read_min, write_min);
}

libvchan_t *libvchan_client_init(int domain, int port) {
    return libkvmchan_client_init(domain, port);
}

int libvchan_write(libvchan_t *ctrl, const void *data, size_t size) {
    return libkvmchan_write(ctrl, data, size);
}

int libvchan_send(libvchan_t *ctrl, const void *data, size_t size) {
    return libkvmchan_send(ctrl, data, size);
}

int libvchan_read(libvchan_t *ctrl, void *data, size_t size) {
    return libkvmchan_read(ctrl, data, size);
}

int libvchan_recv(libvchan_t *ctrl, void *data, size_t size) {
    return libkvmchan_recv(ctrl, data, size);
}

int libvchan_wait(libvchan_t *ctrl) {
    /**
     * TODO: libkvmchan currently doesn't have a mechanism
     * for probing whether the other end of the vchan
     * has connected. Until that is implemented, simply return 0
     */
    (void)ctrl;
    return 0;
}

void libvchan_close(libvchan_t *ctrl) {
    libkvmchan_close(ctrl);
}

EVTCHN libvchan_fd_for_select(libvchan_t *ctrl) {
    return libkvmchan_get_eventfd(ctrl);
}

int libvchan_is_open(libvchan_t *ctrl) {
    // TODO: same as libvchan_wait
    (void)ctrl;
    return VCHAN_CONNECTED;
}

int libvchan_data_ready(libvchan_t *ctrl) {
    size_t ret = libkvmchan_data_ready(ctrl);
    if (ret > INT_MAX)
        ret = INT_MAX;
    return ret;
}

int libvchan_buffer_space(libvchan_t *ctrl) {
    size_t ret = libkvmchan_buffer_space(ctrl);
    if (ret > INT_MAX)
        ret = INT_MAX;
    return ret;

}

