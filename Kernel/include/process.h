#ifndef __PROCESS__H_
#define __PROCESS__H_

#include <stdint.h>

#define STACK_SIZE 512
#define DEFAULT_STDIN 0
#define DEFAULT_STDOUT 1
#define AMMOUNT_FDS 2

typedef struct Process{
    uint64_t stack_base;
    uint64_t ip;
    uint64_t sp;
} Process;

typedef struct Process * ProcessPtr;
static ProcessPtr processes[AMMOUNT_FDS] = {0, 0};

uint64_t init_process(uint64_t stack_base, uint64_t rip);
uint64_t get_current_rsp();
void run_process(uint64_t rsp);

void load_processes(ProcessPtr p1, ProcessPtr p2);
void reboot_process(uint8_t id);

uint64_t set_up_process(uint64_t rsp);
void begin();

void restart_process(); // TODO: Check this func.

uint8_t get_current_process();





#endif