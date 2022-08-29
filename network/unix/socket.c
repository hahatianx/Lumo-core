
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <signal.h>

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "network/unix/socket.h"

static
void init_addrinfo(const char *hostname, const char *port, struct addrinfo **result) {
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_NUMERICSERV | AI_ADDRCONFIG;

    if (getaddrinfo(hostname, port, &hints, result) != 0) {
        perror("getaddrinfo() system call failed.");
        exit(-1);
    }
}

/**
 * @brief 
 * 
 * @param socket_fd 
 * @param hostname 
 * @param port 
 * @return int 
 */
int init_connect(int socket_fd, const char *hostname, const char *port) {
    struct sockaddr_in my_address;
    memset(&my_address, 0, sizeof(my_address));
    
    if (hostname[0] < '0' || hostname[0] > '9') {
        perror("hostname should be an IP address.");
        exit(-1);
    }
    my_address.sin_addr.s_addr = inet_addr(hostname);
    my_address.sin_family = AF_INET;
    my_address.sin_port = htons((unsigned short)atoi(port));

    return connect(socket_fd, (struct sockaddr*)&my_address, sizeof(my_address));
}

/**
 * @brief Set the up connection object
 * 
 * @param hostname 
 * @param port 
 * @return int 
 */
int setup_connection(const char *hostname, const char *port) {
    int socket_fd = -1;
    struct addrinfo *result = NULL;

    // ignore SIGPIPE
    if (signal(SIGPIPE, SIG_IGN) == SIG_ERR) {
        perror("signal() system call failed.");
        exit(-1);
    }

    init_addrinfo(hostname, port, &result);
    struct addrinfo *ai_ptr = NULL;
    for (ai_ptr = result; ai_ptr != NULL; ai_ptr = ai_ptr->ai_next) {
        printf("start socket\n");
        socket_fd = socket(ai_ptr->ai_family, ai_ptr->ai_socktype, ai_ptr->ai_protocol);
        printf("end socket, socket fd: %d\n", socket_fd);
        if (socket_fd == -1) continue;
        if (init_connect(socket_fd, hostname, port) != -1) break;
        close(socket_fd);
        socket_fd = -1;
    }
    freeaddrinfo(result);
    return socket_fd;
}

/*****************************************************************************/
