#include <lib.h>
#include <shell.h>
#include <cpuid.h>
#define COMMANDS 7
#define MAX_BUFFER_LENGTH 256


typedef void (*Pcommands)(void);
void fechayhora_2();

// TODO: should be compared with strcmp
char * commands[COMMANDS] = {"ayuda", "inforeg", "support", "zerodiv", "wrongop", "fechayhora", "printmem"};

// TODO: implement printf along with scanf, putChar and getChar in order for this functionality to work
void ayuda() {
    printf("\nLos comandos disponibles son los siguientes:\n\n");
    printf("inforeg       -imprime en pantalla el valor de todos los registros.\n");
    printf("printmem      -realiza un volcado de memoria de 32 bytes a partir de la\n");
    printf("               direccion que se recibe como argumento.\n");
    printf("fechayhora    -desplega en pantalla el dia y la hora del sistema.\n");
    printf("ayuda         -muestra todos los comandos disponibles.\n");
    printf("zerodiv       -lanza una excepcion de codigo 00. Division by zero.\n");
    printf("wrongop       -lanza una excepcion de codigo 06. Wrong Operand Code.\n");
}

// TODO: after merging, this function should call show_registers
void inforeg(){
    get_info_reg();
}

void features_support(){
    printf("cpuid support: ");
    if(check_cpuid_support()){
        printf("yes.\n");
        uint32_t ecx = 1, edx, ebx;
        get_cpuid_info(&ecx, &edx, &ebx);

        printf("sse support: ");
        available(edx, 25);
        printf("sse2 support: ");
        available(edx, 26);
        printf("sse3 support: ");
        available(ecx, 0);
        printf("sse4.1 support: ");
        available(ecx, 19);
        printf("sse4.2 support: ");
        available(ecx, 20);
        printf("aesni support: ");
        available(ecx, 25);
        printf("pclmulqdq support: ");
        available(ecx, 1);
        printf("avx support: ");
        available(ecx, 28);
        printf("f16c support: ");
        available(ecx, 29);
        printf("fma support: ");
        available(ecx, 12);

        ecx = 7; edx = 0;
        get_cpuid_info(&ecx, &edx, &ebx);
        printf("avx2 support: ");
        available(ebx, 6);
        printf("vpclmulqdq support: ");
        available(ecx, 10);
        printf("vaesni support: ");
        if(get_vaesni_info()){
            printf("yes.\n");
        } else {
            printf("no.\n");
        }

    } else {
        printf("no.\n");
    }
    return;
}

void available(uint64_t reg, char moves) {
    if(((reg >> moves) & 0x01) == 1)
        printf("yes.\n");
    else
        printf("no.\n");
}

uint64_t pow(uint64_t a, uint64_t b) {
    uint64_t aux=1;
    while (b != 0) {
        aux *= a; b--;
    }
    return aux;
}

void printmem() {
    printf("Memory dump at : 0x");
    char buf[17]={0};
    int i = 0;
    char c;
    while((c = getchar()) != '\n' && i < 16) {
        if(c == '\t') {
            change_shell();
        } else if (c == '\b' && i>0) {
            putchar(c);
            i--;
        } else if (c != '\b') {
            putchar(buf[i++] = c);
        }
    }
    buf[i]=0;
    putchar('\n');
    uint64_t pos=0, aux, len = i;
    for(i=0; buf[i]!='\0'; i++) {
        if(buf[i]>='0' && buf[i]<='9') {
            aux = buf[i] - 48;
        }
        else if(buf[i]>='a' && buf[i]<='f') {
            aux = buf[i] - 97 + 10;
        }
        else if(buf[i]>='A' && buf[i]<='F') {
            aux = buf[i] - 65 + 10;
        } else {
            printf("Wrong value.\n"); 
            return;
        }

        pos += aux * pow(16, len);
        len--;
    }
    char mem[64] = {0};
    memdump(mem, (uint8_t *)pos);
    printf(mem);
    printf("\n");
}

int get_comm(char * buffer){
    int idx = 0;
    while(idx < COMMANDS){
        if(strcmp(commands[idx], buffer) == 0)
            return idx;
        idx++;
    }
    return -1;
}

void command_listener(char * buffer) {
    int i = 0;
    unsigned char c;
    while((c = getchar()) != '\n') {
        if(c == '\t'){
            change_shell();
        } else if (c == '\b' && i>0) {
            putchar(c);
            i--;
        } else if (c != '\b') {
            putchar(buffer[i++] = c);
        }
    }
    if (c == '\n') {
        putchar(c);
    }
    buffer[i] = 0;
}

void dummy(char * buffer) {
    int i = 0;
    unsigned char c;
    while((c = getchar()) != '\n') {
        if(c == '\t'){
            change_shell();
        } else if (c == '\b' && i>0) {
            putchar(c);
            i--;
        } else if (c != '\b') {
            putchar(buffer[i++] = c);
        }
    }
    if (c == '\n') {
        putchar(c);
    }
    buffer[i] = 0;
}

int get_correct_command(char * buffer){
    int idx = 0;
    while(idx < COMMANDS){
        if(strcmp(commands[idx], buffer) == 0)
            return idx;
        idx++;
    }
    return -1;
}

void zerodiv(){
    try_catch_zerodiv();
}

void wrongop(){
    try_catch_ud();
}

void fechayhora(){
    char timebuf[9];
    char datebuf[9];
    get_date_time(datebuf, timebuf);
    printf("Time: ");
    printf(timebuf);
    printf(" (UTC) \nDate: ");
    printf(datebuf);
    printf("\n");
}

Pcommands command_codes[] = {&ayuda, &inforeg, &features_support, &zerodiv, &wrongop, &fechayhora_2, &printmem};

int run_shell() {
    printf("\n");
    char buffer[MAX_BUFFER_LENGTH] = {0};
    while(1) {
        printf(">> ");
        dummy(buffer);
        int idx = get_correct_command(buffer);
        if(idx == -1)
            printf("No such command. Run command \"ayuda\" to see all commands.\n");
        else {
           Pcommands command = command_codes[idx];
           command();
        }
    }
    return 0; // TODO: Manage what we return.
}


void fechayhora_2(){
    char timebuf[9];
    char datebuf[9];
    get_date_time(datebuf, timebuf);
    printf("Time: ");
    printf(timebuf);
    printf(" (UTC) \nDate: ");
    printf(datebuf);
    printf("\n");
}

