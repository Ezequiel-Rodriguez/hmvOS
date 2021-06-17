
GLOBAL _cli
GLOBAL _sti
GLOBAL picMasterMask
GLOBAL picSlaveMask
GLOBAL haltcpu
GLOBAL pushStateHardware
GLOBAL popStateHardware
GLOBAL _hlt

GLOBAL _irq00Handler
GLOBAL _irq01Handler
GLOBAL _irq02Handler
GLOBAL _irq03Handler
GLOBAL _irq04Handler
GLOBAL _irq05Handler

GLOBAL _sysCall80Handler
GLOBAL _processHandler

GLOBAL _exception00Handler
GLOBAL _exception06Handler

EXTERN irqDispatcher
EXTERN sysCallDispatcher
EXTERN exceptionDispatcher
EXTERN set_up_process

SECTION .text

%macro pushStateHardware 0
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

%macro popStateHardware 0
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

%macro pushStateSysCall 0
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

%macro popStateSysCall 0
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
%endmacro

%macro irqHandlerMaster 1
	pushStateHardware

	mov rdi, %1 ; pasaje de parametro
	call irqDispatcher

	; signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al

	popStateHardware
	iretq
    ; IRET returns from an interrupt (hardware or software) 
	; by means of popping IP (or EIP), CS, and the flags off 
	; the stack and then continuing execution from the new CS:IP.

    ; IRETW pops IP, CS and the flags as 2 bytes each, 
	; taking 6 bytes off the stack in total. IRETD pops EIP 
	; as 4 bytes, pops a further 4 bytes of which the top two 
	; are discarded and the bottom two go into CS, and pops 
	; the flags as 4 bytes as well, taking 12 bytes off the stack.

    ; IRET is a shorthand for either IRETW or IRETD, 
	; depending on the default BITS setting at the time.

	; IRETQ preserves the flags and other things. ;; it is the IRETD of 64 bits.
%endmacro

%macro sysCallHandlerMaster 1
	pushStateSysCall

	mov rcx, rax  ;; TODO: Check this, there has to be a better way of doing it.
	call sysCallDispatcher

	push rax
	; signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al
	pop rax

	popStateSysCall
	iretq
%endmacro


%macro exceptionHandler 1
	pushStateHardware

	mov rdi, %1
	call exceptionDispatcher

	; signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al

	popStateHardware
	iretq
%endmacro


_hlt:
	sti
	hlt
	ret

_cli:
	cli
	ret


_sti:
	sti
	ret

picMasterMask:
	push rbp
    mov rbp, rsp
    mov ax, di
    out	21h,al
    pop rbp
    retn

picSlaveMask:
	push    rbp
    mov     rbp, rsp
    mov     ax, di  ; ax = mascara de 16 bits
    out	0A1h,al
    pop     rbp
    retn


;8254 Timer (Timer Tick)
_irq00Handler:
	irqHandlerMaster 0

;Keyboard
_irq01Handler:
	irqHandlerMaster 1

;Cascade pic never called
_irq02Handler:
	irqHandlerMaster 2

;Serial Port 2 and 4
_irq03Handler:
	irqHandlerMaster 3

;Serial Port 1 and 3
_irq04Handler:
	irqHandlerMaster 4

;USB
_irq05Handler:
	irqHandlerMaster 5

_sysCall80Handler:    ;; TODO: Does 80 need to be here or is it enough calling it "_sysCallhandler"?
	sysCallHandlerMaster 80

_processHandler:
	pushStateHardware
	mov rdi, rsp
	call set_up_process
	mov rsp, rax
	popStateHardware
	
	iretq


;Zero Division Exception
_exception00Handler:
	exceptionHandler 0

_exception06Handler:
	exceptionHandler 6

haltcpu:
	cli
	hlt
	ret

SECTION .bss
	aux resq 1