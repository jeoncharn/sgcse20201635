#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "threads/vaddr.h"


static void syscall_handler (struct intr_frame *);

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

// esp로 전달된 argument가 타당한 위치에 있는지 파악하는 함수이다.
void check_address(void* addr){
    if(!is_user_vaddr(addr)){
        exit(-1);
    }
}

/* 각 system call을 수행하는 함수이다. */

// pintos 자체를 종료하는 함수
void halt(void)
{
    shutdown_power_off();
}

// 현재 user program을 종료
void exit(int status)
{
    
    // int status를 thread sturuct에 할당한다.
    struct thread* cur = thread_current();
    //cur->status = THREAD_DYING;
    cur->exit_status = status;
    //process_exit();
    
    //printf("%s: exit(%d)\n", cur->name, cur->exit_status);
    
    thread_exit();
    //printf("EXIT func executed.\n");
    
}

// pid_t 로 안되는 이우??
tid_t exec(const char* cmd_line)
{
    // cmd_line 기준 file name이 잘못된 경우??
    
    
    return process_execute(cmd_line);
}

int wait(tid_t pid)
{
    // child thread ID check
    // exit status 받기
    return process_wait(pid);
}

int read(int fd, void* buffer, unsigned size)
{
    // standard input이 아닌 경우
    if(fd != 0){
        return -1;
    }
    for(int i=0; i<size; i++){
        if(input_getc() == '\0'){
            break;
        }
    }
}

int write(int fd, const void* buffer, unsigned size)
{
    // standard output이 아닌 경우
    if(fd != 1){
        return -1;
    }
    putbuf(buffer, size);
    return size;
}

int fibonacci(int n){
    int n_1 = 0;
    int n_2 = 0;
    int result = 1;
    
    for(int i=1; i<n; i++){
        n_2 = n_1;
        n_1 = result;
        result = n_1 + n_2;
    }
    
    return result;
    
}

int max_of_four_int(int a, int b, int c, int d){
    
    int max = a;
    
    if(max<b){
        max = b;
    }
    if(max<c){
        max = c;
    }
    if(max<d){
        max = d;
    }
    
    return max;
}


static void
syscall_handler (struct intr_frame *f UNUSED) 
{
    //printf("current system call num : %d\n", *(uint32_t *)(f->esp));
    //hex_dump(f->esp, f->esp, 100, 1);
    
    //thread_exit();
        
    switch (*(uint32_t *)(f->esp)) {
        case SYS_HALT:
            halt();
            break;
            
        case SYS_EXIT:
            check_address(f->esp + 4);
            exit(*(uint32_t *)(f->esp + 4));
            break;
            
        case SYS_EXEC:
            check_address(f->esp + 4);
            f->eax = exec(*(uint32_t *)(f->esp + 4));
            break;
            
        case SYS_WAIT:
            check_address(f->esp + 4);
            f->eax = wait(*(uint32_t *)(f->esp + 4));
            break;
            
        case SYS_READ:
            check_address(f->esp + 4);
            check_address(f->esp + 8);
            check_address(f->esp + 12);
            f->eax = read(*(uint32_t *)(f->esp + 4), *(uint32_t *)(f->esp + 8), *(uint32_t *)(f->esp + 12));
            break;
            
        case SYS_WRITE:
            check_address(f->esp + 4);
            check_address(f->esp + 8);
            check_address(f->esp + 12);
            f->eax = write(*(uint32_t *)(f->esp + 4), *(uint32_t *)(f->esp + 8), *(uint32_t *)(f->esp + 12));
            //printf("%d %p %d\n", *(uint32_t *)(f->esp + 4), *(uint32_t *)(f->esp + 8), *(uint32_t *)(f->esp + 12));
            break;
            
        case SYS_FIBONACCI:
            check_address(f->esp + 4);
            f->eax = fibonacci(*(uint32_t *)(f->esp + 4));
            break;
        
        case SYS_MAX_OF_FOUR_INT:
            check_address(f->esp + 4);
            check_address(f->esp + 8);
            check_address(f->esp + 12);
            check_address(f->esp + 16);
            f->eax = max_of_four_int(*(uint32_t *)(f->esp + 4), *(uint32_t *)(f->esp + 8), *(uint32_t *)(f->esp + 12), *(uint32_t *)(f->esp + 16));
            break;
    }
}
