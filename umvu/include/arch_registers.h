#if defined(__x86_64__)

#define SYSCALL_ARG1		rdi
#define SYSCALL_ARG2		rsi
#define SYSCALL_ARG3		rdx
#define SYSCALL_ARG4		r10
#define SYSCALL_ARG5		r8
#define SYSCALL_ARG6		r9
#define SYSCALL_NO			orig_rax
#define SYSCALL_RETURN		rax
#define PROGRAM_COUNTER		rip
#define STACK_POINTER		rsp

#elif defined(__aarch64__)

#define SYSCALL_ARG1		regs[0]
#define SYSCALL_ARG2		regs[1]
#define SYSCALL_ARG3		regs[2]
#define SYSCALL_ARG4		regs[3]
#define SYSCALL_ARG5		regs[4]
#define SYSCALL_ARG6		regs[5]
#define SYSCALL_NO			regs[8]
#define SYSCALL_RETURN		regs[0]
#define PROGRAM_COUNTER		pc
#define STACK_POINTER		sp

#endif
