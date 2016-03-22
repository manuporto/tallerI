#ifndef SOCKET_API_H_
#define SOCKET_API_H_

#include<stdio.h>
#include<string.h>

void cliente(char *hostname, char *port, char *old_local_file, char *new_local_file, char *new_remote_file, int block_size);
#endif
