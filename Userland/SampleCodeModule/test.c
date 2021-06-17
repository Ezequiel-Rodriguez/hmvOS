#include <lib.h>
#include <stdarg.h> //Nueva librería incluida para myprintf

int strcmp(char * str1, char * str2);

int strlen(const char* str){
    int i=0;
    while(str[i++]);
    return i-1;
}

int strcmp( char * str1, char * str2) {
    while(*str1 || *str2)
        if (*(str1++) ^ *(str2++)) return *(str2-1) - *(str1-1);
    return 0;
}

void printf(const char * str) {
    print(STDOUT, str, strlen(str));
}

int getchar() {
    char c = 0;
    read(STDIN, &c, 1);
    return c;
}

void putchar(char c) {
    print(STDOUT, &c, 1);
}
