#include <time.h>
#include <keyboard.h>
#include <stdint.h>
#include <naiveConsole.h>
#include <lib.h>
#include <interrupts.h>
#include <cpu_support.h>
#include <clock.h>

typedef uint64_t (*PSysCall)(uint64_t, uint64_t, uint64_t);

long write(unsigned int fd, const char * buf, size_t count); // TODO: Fix long for ssize_t
long read(unsigned int fd, char * buf, size_t count);
uint64_t cpuid_support(uint64_t rdi, uint64_t rsi, uint64_t rdx);
uint64_t info_reg(uint64_t rdi, uint64_t rsi, uint64_t rdx);
uint64_t mem_dump_32B(uint8_t * buf, uint8_t * dir, uint64_t rdx);
uint64_t fecha_y_hora(char * datebuf, char * timebuf, uint64_t rdx);

static PSysCall sysCalls[255] = {(PSysCall)&read, (PSysCall)&write, (PSysCall)&cpuid_support, (PSysCall)&info_reg, (PSysCall)&mem_dump_32B, (PSysCall)&fecha_y_hora};

long write(unsigned int fd, const char * buf, size_t count) {
    if (buf == NULL)
        return -1;
    int i;
    uint32_t front = fd == STDERR ? RED : WHITE;
    for(i = 0; buf[i] && i < count; i++) {
        if (buf[i] == '\n')     // TODO: idk why this creates an exception.
            ncNewline();
        else if (buf[i] == '\b')
            ncErase(1);
        else
            ncPrintCharAtt(buf[i], front, BLACK);
    }
    return i == 0? -1 : i;  // TODO: see if this return value is valid. Or should we send codes?
}

long read(unsigned int fd, char * buf, size_t count) {
    // TODO: What could we use fd for¿?
    long read_count = -1;
    while ( read_count == -1 ) {
        if ((read_count = copy_from_buffer(buf, count)) == -1)
            _hlt();
    }
    return read_count;
}

uint64_t info_reg(uint64_t rdi, uint64_t rsi, uint64_t rdx) {
    show_registers();
    return 0;
}

uint64_t cpuid_support(uint64_t rdi, uint64_t rsi, uint64_t rdx) {
    return _cpuid_support();
}

uint64_t mem_dump_32B(uint8_t * buf, uint8_t *  dir, uint64_t rdx) {
    uint8_t value;
    int i = 0;
    while (i < 64) {
        value = *(dir) & 0x0F;
        buf[i+7] = value > 9 ? (value - 10) + 'A' : value + '0';
        value = (*(dir) & 0xF0) >> 4;
        buf[i+6] = value > 9 ? (value - 10) + 'A' : value + '0';
        value = *(dir+1) & 0x0F;
        buf[i+5] = value > 9 ? (value - 10) + 'A' : value + '0';
        value = (*(dir+1) & 0xF0) >> 4;
        buf[i+4] = value > 9 ? (value - 10) + 'A' : value + '0';
        value = *(dir+2) & 0x0F;
        buf[i+3] = value > 9 ? (value - 10) + 'A' : value + '0';
        value = (*(dir+2) & 0xF0) >> 4;
        buf[i+2] = value > 9 ? (value - 10) + 'A' : value + '0';
        value = *(dir+3) & 0x0F;
        buf[i+1] = value > 9 ? (value - 10) + 'A' : value + '0';
        value = (*(dir+3) & 0xF0) >> 4;
        buf[i] = value > 9 ? (value - 10) + 'A' : value + '0';
        dir += 4; i += 8;
    }
    buf[i] = 0;
    return i;
}

uint64_t fecha_y_hora(char * datebuf, char * timebuf, uint64_t rdx){
	dateToStr(datebuf);
	timeToStr(timebuf);
    return 0;
}

uint64_t sysCallDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rax) {  // TODO: Depending on how many sysCalls we have we have to see wich regiters we use.
    PSysCall sysCall = sysCalls[rax];
    if (sysCall != 0) return sysCall(rdi, rsi, rdx);
    return 0;
}
