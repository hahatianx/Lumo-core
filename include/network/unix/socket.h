

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
 * @brief Set up connection object
 * 
 * @param hostname 
 * @param port 
 * @return int 
 */
int setup_connection(const char *hostname, const char *port);

/*****************************************************************************/

/**
 * @brief Get the peer ip port object
 * 
 * @return int 
 */
int get_peer_ip_port(int, uint32_t*, uint16_t*);

/**
 * @brief Create a listening socket object
 * 
 * @return int 
 */
int create_listening_socket(char*, uint16_t);

/**
 * @brief Set the up accept object
 * 
 * @return int 
 */
int setup_accept(const int);
