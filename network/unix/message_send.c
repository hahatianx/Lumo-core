#include <stdio.h>
#include <string.h>

#include "core.h"
#include "network/message.h"
#include "network/message_send.h"
#include "network/unix/socket.h"
#include "io/readwrite.h"

static
int ip_int_to_string(uint32_t ipaddr, char *buffer, size_t size) {
    memset(buffer, 0, size);
    snprintf(buffer, size, "%d.%d.%d.%d", 
        (ipaddr >> 24) & 0xff, (ipaddr >> 16) & 0xff, (ipaddr >> 8) & 0xff, (ipaddr) & 0xff);
    return 0;
}

void send_message(message_task_t *msg_task) {
    char *buffer = (char*)malloc(msg_task->size);
    char dest_addr[16];
    int socket_fd = -1;
    size_t bytes_to_send;

    message_to_block(msg_task->msg, buffer, msg_task->size);
    ip_int_to_string(msg_task->dst_addr, dest_addr, 16);
    printf("Connecting %s:%s ...\n", dest_addr, "11451");
    socket_fd = setup_connection(dest_addr, "11451");

    if (socket_fd == -1) {
        perror("socket() application failed.");
        exit(-1);
    }
    write_to_file(socket_fd, buffer, msg_task->size);

    free(buffer);
}

void send_file(char *path) {

}
