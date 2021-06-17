#include <time.h>
#include <keyboard.h>
#include <stdint.h>

typedef void (*PInterruption)(void);

static void int_20();
static void int_21();

static PInterruption interruptions[255] = {&int_20, &int_21};

void int_20() {
    timer_handler();
}

void int_21() {
	keyboard_handler();
}

void irqDispatcher(uint64_t irq) {
    PInterruption interruption = interruptions[irq];
    if (interruption != 0) interruption();
    return;
}
