#ifndef USERPROG_SYSCALL_H
#define USERPROG_SYSCALL_H

void syscall_init (void);


/* system call 함수를 각각 구현한다. */
/* pintos manual 의 설명을 바탕으로 구현할 함수이다. */

void halt(void);
void exit(int status);
pid_t exec(const char* cmd_line);
int wait(pid_t pid);
int read(int fd, void* buffer, unsigned size);
int write(int fd, const void* buffer, unsigned size);


/* 추가로 구현할 system call 이다. */
int fibonacci(int num);
int max_of_four_int(int num1, int num2, int num3, int num4);


#endif /* userprog/syscall.h */
