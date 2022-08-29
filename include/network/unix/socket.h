

/**
 * @brief 
 * 
 * @param socket_fd 
 * @param hostname 
 * @param port 
 * @return int 
 */
int init_connect(int socket_fd, const char *hostname, const char *port);

/**
 * @brief Set the up connection object
 * 
 * @param hostname 
 * @param port 
 * @return int 
 */
int setup_connection(const char *hostname, const char *port);

/*****************************************************************************/
