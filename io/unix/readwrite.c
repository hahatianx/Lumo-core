#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#include "io/readwrite.h"

int write_to_file(int fd, char *buffer, size_t bytes) {
    size_t bytes_remaining = bytes;
    while (bytes_remaining > 0) {
        int bytes_written = write(fd, buffer, bytes_remaining);

        // write with success
        if (bytes_written > 0) {
            bytes_remaining -= bytes_written;
            buffer += bytes_written;
        } else if (bytes_written == -1) {
            // stopped by interruption
            if (errno == EINTR) continue;
            return (-1);
        }
    }
    return bytes;
}

int read_from_file(int fd, char *buffer, size_t bytes) {
    memset(buffer, 0, bytes);
    return 0;
}