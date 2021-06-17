#ifndef LIB_H
#define LIB_H

#include <stdint.h>
#include <stddef.h>

#define STDOUT 1
#define STDERR 2

void * memset(void * destination, int32_t character, uint64_t length);
void * memcpy(void * destination, const void * source, uint64_t length);

char *cpuVendor(char *result);

int print(unsigned int fd, const char * buf, size_t count);
void show_registers();

#endif