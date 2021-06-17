#include <stdint.h>
#include <process.h>
// Debug includes
#include <time.h>
#include <naiveConsole.h>

static uint8_t activeProcess = 0;

void load_processes(ProcessPtr p1, ProcessPtr p2) {
    processes[0] = p1;
    processes[1] = p2;
    processes[0]->sp = init_process(processes[0]->stack_base, processes[0]->ip);
    processes[1]->sp = init_process(processes[1]->stack_base, processes[1]->ip);
}

uint64_t set_up_process(uint64_t rsp) {
    processes[activeProcess]->sp = rsp;
    activeProcess = 1 - activeProcess;
    return processes[activeProcess]->sp;
}

void begin() {
    if(processes[0] != 0) run_process(processes[0]->sp);
}

void restart_process(){
    processes[activeProcess]->sp = init_process(processes[activeProcess]->stack_base, processes[activeProcess]->ip);
}

uint64_t get_current_rsp() {
    return processes[activeProcess]->sp;
}

uint8_t get_current_process() {
    return activeProcess;
}