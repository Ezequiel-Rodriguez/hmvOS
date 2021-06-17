#ifndef __LIB_ASM__H__
#define __LIB_ASM__H__

#include <stddef.h>
#include <stdint.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2

void print(unsigned int fd, const char * buf, size_t count);
long read(unsigned int fd, char * buf, size_t count);
void try_catch_ud(void);
void try_catch_zerodiv(void);
int strlen(const char * str);
int strcmp( char * str1, char * str2);
void printf(const char * str);
int getchar();
void putchar(char c);
char check_cpuid_support(void);
void get_cpuid_info(uint32_t * ecx, uint32_t * edx, uint32_t * ebx);
void get_info_reg(void);
uint32_t get_vaesni_info(void);
void get_date_time(char * datebuf, char * timebuf);
void memdump(char * buf, uint8_t *  dir);

#endif
