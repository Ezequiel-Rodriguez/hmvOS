GLOBAL kbRead

section .text

kbRead: ; unsigned int kbRead(void);
	push rbp
	mov rbp, rsp

	xor rax, rax
	in al, 0x60

	mov rsp, rbp
	pop rbp
	ret
