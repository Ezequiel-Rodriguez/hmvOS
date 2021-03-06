#include <interrupts.h>
#include <lib.h>
#include <time.h>
#include <keyboard.h>
#include <naiveConsole.h>
#include <process.h>
#define STDERR 2

typedef void (*PException)();
static void int_00(void);
static void int_06(void);
static PException exceptions[0x20] = {&int_00, 0, 0, 0, 0, 0, &int_06};

static char * messages[2] = {"Division by zero.\n", "Wrong operation code.\n"};
static uint8_t msg_len[2] = {18, 22};

static void exception(char * msg, uint8_t len) {
    print(STDERR, msg, len);
    show_registers();
    print(STDERR, "Press enter to continue...", 26);
    uint8_t sc;
        do{
        if (copy_from_buffer(&sc,1)==-1) 
            _hlt();
    } while(sc != '\n');
    ncNewline();
    restart_process();
}

static void int_00(void){
    exception(messages[0], msg_len[0]);
}

static void int_06(void){
    exception(messages[1], msg_len[1]);
}

void exceptionDispatcher(int exception) {
    PException exc = exceptions[exception];
    ncPrint("Voy a llamar a la excepcion numero ");
    ncPrintHex(exception);
    ncNewline();
    if (exc != 0) exc();
    return;
}
