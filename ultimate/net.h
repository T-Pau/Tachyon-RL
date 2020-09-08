#ifndef HAD_ULTIMATE_NET_H
#define HAD_ULTIMATE_NET_H

unsigned char ultimate_net_close(unsigned char socket);
unsigned char ultimate_net_connect(const unsigned char *host, unsigned int port);
unsigned char ultimate_net_read(const unsigned char socket, unsigned char *buffer, unsigned int length);
unsigned char ultimate_net_write(const unsigned char socket, const unsigned char *buffer, unsigned int length);

#endif /* HAD_ULTIMATE_NET_H */
