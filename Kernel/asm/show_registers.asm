section .text
GLOBAL show_registers

extern ncPrint
extern ncPrintReg
extern ncNewline

%macro pushRegisters 0
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
%endmacro

%macro popRegisters 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro

show_registers:
    pushRegisters
    mov rdi, reg1
    call ncPrint
    mov rdi, rax
    call ncPrintReg
    call ncNewline
    popRegisters

    pushRegisters
    mov rdi, reg2
    call ncPrint
    mov rdi, rbx
    call ncPrintReg
    call ncNewline
    popRegisters

    pushRegisters
    mov rdi, reg3
    call ncPrint
    mov rdi, rcx
    call ncPrintReg
    call ncNewline
    popRegisters

    pushRegisters
    mov rdi, reg4
    call ncPrint
    mov rdi, rdx
    call ncPrintReg
    call ncNewline
    popRegisters

    pushRegisters
    mov rbx, rdi
    mov rdi, reg5
    call ncPrint
    mov rdi, rbx
    call ncPrintReg
    call ncNewline
    popRegisters

    pushRegisters
    mov rdi, reg6
    call ncPrint
    mov rdi, rsi
    call ncPrintReg
    call ncNewline
    popRegisters

    pushRegisters
    mov rdi, reg7
    call ncPrint
    mov rdi, [rsp + 15*8]  ;; Change line to obtain rip value
    call ncPrintReg
    call ncNewline
    popRegisters

    pushRegisters
    mov rdi, reg8
    call ncPrint
    mov rdi, rsp
    call ncPrintReg
    call ncNewline
    popRegisters

    pushRegisters
    mov rdi, reg9
    call ncPrint
    mov rdi, rbp
    call ncPrintReg
    call ncNewline
    popRegisters
    
    pushRegisters
    mov rdi, reg16
    call ncPrint
    mov rdi, r8
    call ncPrintReg
    call ncNewline
    popRegisters

    pushRegisters
    mov rdi, reg17
    call ncPrint
    mov rdi, r9
    call ncPrintReg
    call ncNewline
    popRegisters

    pushRegisters
    mov rdi, reg10
    call ncPrint
    mov rdi, r10
    call ncPrintReg
    call ncNewline
    popRegisters

    pushRegisters
    mov rdi, reg11
    call ncPrint
    mov rdi, r11
    call ncPrintReg
    call ncNewline
    popRegisters

    pushRegisters
    mov rdi, reg12
    call ncPrint
    mov rdi, r12
    call ncPrintReg
    call ncNewline
    popRegisters

    pushRegisters
    mov rdi, reg12
    call ncPrint
    mov rdi, r12
    call ncPrintReg
    call ncNewline
    popRegisters

    pushRegisters
    mov rdi, reg13
    call ncPrint
    mov rdi, r13
    call ncPrintReg
    call ncNewline
    popRegisters

    pushRegisters
    mov rdi, reg14
    call ncPrint
    mov rdi, r14
    call ncPrintReg
    call ncNewline
    popRegisters

    pushRegisters
    mov rdi, reg15
    call ncPrint
    mov rdi, r15
    call ncPrintReg
    call ncNewline
    popRegisters

    ret

section .data
reg1 db "RAX: ", 0
reg2 db "RBX: ", 0
reg3 db "RCX: ", 0
reg4 db "RDX: ", 0
reg5 db "RDI: ", 0
reg6 db "RSI: ", 0
reg7 db "RIP: ", 0
reg8 db "RSP: ", 0
reg9 db "RBP: ", 0
reg10 db "R10: ", 0
reg11 db "R11: ", 0
reg12 db "R12: ", 0
reg13 db "R13: ", 0
reg14 db "R14: ", 0
reg15 db "R15: ", 0
reg16 db "R8:  ", 0
reg17 db "R9:  ", 0