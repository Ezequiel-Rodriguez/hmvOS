#ifndef __STDIO__H__
#define __STDIO__H__

#include <stdarg.h>

int strcmp( char * str1, char * str2);
int strlen(const char * str);
void puts(const char * str);
void putchar(char c);
int getchar();
void printf(const char * format, ...);
void scanf(char * buffer, int count);

#endif