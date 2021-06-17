GLOBAL _cpuid_support


;; el bit 21 de los rflags me determina si el procesador soporta la instruccion cpuid 
_cpuid_support:
    push rbx            ; guardo valores para conservarlos luego de retornar
    pushfq
    pop rax
    mov rbx, rax

    xor rax, 200000h    ; "prendo" el bit 21 que determina si el mp soporta cpuid
    push rax            ; pusheo estos cambios que le hice al registro de flags
    popfq               ; popeo este ultimo valor que pushie a los rflags. El mp cambiara el bit 21 automaticamente
                        ; si es que no tiene support para el cpuid.
    pushfq              
    pop rax             ; cargo en rax, el valor actualizado por el procesador
    cmp rax, rbx        ; comparo mi nuevo valor de registros luego del xor con el original

    jz no_cpuid         ; si el procesador cambió automaticamente el bit nro 21 a 0, dara distinto y salta (no cpuid support)
    pop rbx             ; devuelvo el valor de rbx
    mov rax, 1          ; valor de retorno 1
    ret

no_cpuid:
    pop rbx
    mov rax, 0
    ret