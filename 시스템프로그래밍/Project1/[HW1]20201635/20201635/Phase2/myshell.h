#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <signal.h>


#define    MAXARGS      128
#define    MAXLINE     8192


void eval(char* cmdline);
void parseline(char* buf, char** argv);
void execute(char** argv);
void pipe_execute(char* decompose_argv[MAXARGS][10], int fd_in, int argv_num, int argv_left);int builtin_command(char** argv);
pid_t Fork(void);
void unix_error(char *msg);
void sigint_handler(int sig);
ssize_t sio_puts(char s[]);
static size_t sio_strlen(char s[]);

