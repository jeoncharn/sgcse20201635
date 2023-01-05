#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>


#define    MAXARGS      128
#define    MAXLINE     8192

void eval(char* cmdline);
int parseline(char* buf, char** argv);
void pipe_execute(char* decompose_argv[MAXARGS][10], int fd_in, int argv_num, int argv_left, int bg);
int builtin_command(char** argv);
pid_t Fork(void);
void unix_error(char *msg);

void add_to_list(int bg_execute); // foreground에서 ctrl + Z가 입력되었을 경우, 혹은 bg execute 인 경우 list에 추가하는 함수
void kill_all_list(void); // exit으로 종료하는 경우, 아직 실행중인 bg process들을 종료하는 함수
void print_all_bg_jobs(void); // jobs의 실행을 위한 함수
void bg_execute(char* num); // stopped bg job을 bg running 시킨다.
void fg_execute(char* num); // stopped / running bg job을 fg running 시킨다.
void kill_process(char* num); // bg job을 kill 시킨다.

void sigint_handler(int sig);
void sigchld_handler(int sig);
void sigstp_handler(int sig);
ssize_t sio_puts(char s[]);
static size_t sio_strlen(char s[]);
ssize_t sio_putl(long v);
static void sio_ltoa(long v, char s[], int b);
static void sio_reverse(char s[]);

struct bg_process{
    pid_t pid;
    
    // 명령어를 저장하는 변수
    char command[64];
    
    //jobs를 시행했을 때, background number를 print하는 변수
    int num;
    
    // 1이라면 running, 0이라면 suspended를 의미한다.
    int mode;
    
    // linked list로 background process를 저장하기 위해 필요한 변수이다.
    struct bg_process* next;
};

struct executing_process{
    pid_t pid;
    
    // 명령어를 저장하는 변수
    char command[64];
    
    // running = 1이라면 command가 실행중이며, running = 0이라면 이미 종료된 process이다.
    int running;
};