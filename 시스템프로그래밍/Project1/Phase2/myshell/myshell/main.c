//
//  myshell
//
//  Created by Jeon Charn on 2022/03/30 ~ 2022/04/03.
//

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



int main() {
    
    char cmdline[MAXLINE];
    
    // SIGINT(ctrl+C signal)에 대한 signal handler 설정
    if(signal(SIGINT, sigint_handler) == SIG_ERR){
        sio_puts("signal install error exists.\n");
        exit(0);
    }
    
    // shell의 실행 부분
    while(1){
        sio_puts(" > ");
        fgets(cmdline, MAXLINE, stdin);
        
        if(feof(stdin)){
            exit(0);
        }
        
        // eval은 parseline / execute 로 구성된다.
        eval(cmdline);
    }
    return 0;
}

void eval(char* cmdline)
/* this function gets command line input and evaluate input
   this function also calls execve function to execute the command */
{
    char* argv[MAXARGS];
    char buf[MAXLINE];
    char* decompose_argv[MAXARGS][10];
    int j = 0; // pipe 개수를 count하는 변수이다.
    int k = 0; // decompose_argv를 저장하기 위한 변수이다.
    
    strcpy(buf, cmdline);
    parseline(buf, argv);
    
    // when input dosen't exist(only composed blankspace)
    if(argv[0] == NULL){
        return;
    }
    
    for(int i=0; argv[i]!=NULL; i++){
        if(!strcmp(argv[i],"|")){
            j++;
            k = 0;
            //error을 체크하기 위한 방법 (decompose[][0] == NULL 이라면 에러이다.)
            decompose_argv[j][k] = NULL;
        }
        else{
            decompose_argv[j][k] = argv[i];
            k++;
            decompose_argv[j][k] = NULL;
        }
    }
    
    // pipe 개수와 argv 개수가 알맞지 않은 경우에, error이다.
    for(int i=0; i<=j; i++){
        if(decompose_argv[i][0]==NULL){
            sio_puts("command number error with pipes\n");
            return;
        }
    }
    // 받은 command들을 실행한다.
    pipe_execute(decompose_argv, STDIN_FILENO, 0, j+1);
    return;
}

// Phase 1의 execute() 함수의 기능을 확장한 함수이다.
void pipe_execute(char* decompose_argv[MAXARGS][10], int fd_in, int argv_num, int argv_left){
    pid_t pid;
    int status;
    int fd[2];
    
    //실행할 command가 1개 남은 경우
    if(argv_left == 1){
        //
        if(!builtin_command(decompose_argv[argv_num])){
            if((pid = Fork()) == 0){
                dup2(fd_in, STDIN_FILENO);
                if(fd_in != STDIN_FILENO){
                    close(fd_in);
                }
                if(execvp(decompose_argv[argv_num][0], decompose_argv[argv_num]) < 0){
                    sio_puts(decompose_argv[argv_num][0]);
                    sio_puts(" : command not found.\n");
                    exit(0);
                }
            }
            if(waitpid(pid, &status, 0) < 0){
                unix_error("waitfg : waitpid error\n");
            }
        }
        
        return;
    }
    
    else{
        // 새로운 pipe를 만들어낸다.(pipe의 input은 현재 command의 output, pipe의 output은 다음 command의 input)
        if(pipe(fd) < 0){
            sio_puts("there was pipe function error.\n");
            return;
        }
        if(!builtin_command(decompose_argv[argv_num])){
            if((pid = Fork()) == 0){
                dup2(fd_in, STDIN_FILENO);
                if(fd_in!=STDIN_FILENO){
                    close(fd_in);
                }
                dup2(fd[1], STDOUT_FILENO);
                close(fd[1]);
                
                if(execvp(decompose_argv[argv_num][0], decompose_argv[argv_num]) < 0){
                    sio_puts(decompose_argv[argv_num][0]);
                    sio_puts(" : command not found.\n");
                    exit(0);
                }
            }
            close(fd[1]);
            //recursive 하게 pipelining을 구현한다.
            pipe_execute(decompose_argv, fd[0], argv_num + 1, argv_left - 1);
            close(fd[0]);
            
            if(waitpid(pid, &status, 0) < 0){
                unix_error("waitfg : waitpid error\n");
            }
        }
        
        return;
    }
}

int builtin_command(char **argv)
{
    if(!strcmp(argv[0], "exit")) /* exit command */
    exit(0);
    
    else if(!strcmp(argv[0], "cd")){
        if(argv[1] == NULL){
            argv[1] = getenv("HOME");
        }
        if(chdir(argv[1]) < 0){
            sio_puts("cd: no such dirctory: ");
            sio_puts(argv[1]);
            sio_puts("\n");
                     
        }
        return 1;
    }
    
    return 0;
}


pid_t Fork(void)
{
    pid_t pid;

    if ((pid = fork()) < 0)
    unix_error("Fork error");
    return pid;
}


void unix_error(char *msg) /* Unix-style error */
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
}

void parseline(char *buf, char **argv)
{
    int argc = 0;            /* Number of args */
    int save_flag = 0;
    int length;
    
    buf[strlen(buf)-1] = '\0';  /* Replace trailing '\n' with space */
    while (*buf && (*buf == ' ')) /* Ignore leading spaces */
    buf++;
    
    length = strlen(buf);
    /* Build the argv list */
    for(int i = 0; i<length; i++){
        // 큰따음표인 경우
        if(buf[i]=='\"'){
            argv[argc++] = (&buf[i]) + 1;
            i++;
            
            while(buf[i]!='\"'){
                i++;
            }
            //다음 큰 따음표를 NULL로 바꾸어 준다.
            buf[i] = '\0';
        }
        
        // 작은 따음표인 경우
        else if(buf[i]=='\''){
            argv[argc++] = (&buf[i]) + 1;
            i++;
            
            while(buf[i]!='\''){
                i++;
            }
            
            buf[i] = '\0';
        }
        
        //space인 경우
        else if(buf[i]==' '){
            save_flag = 0;
            buf[i] = '\0';
        }
        
        //Phase 2 & 3 에서 |, & 를 사용하는 경우
        else if(buf[i]=='|'){
            save_flag = 0;
            argv[argc++] = "|";
            buf[i] = '\0';
        }
        
        else if(buf[i]=='&'){
            save_flag = 0;
            argv[argc++] = "&";
            buf[i] = '\0';
        }
        
        else{
            if(!save_flag){
                argv[argc++] = (&buf[i]);
                save_flag = 1;

            }
        }
    }
    argv[argc] = NULL;
    
    return;
}

//sigint(ctrl+C)를 받는 경우, shell은 종료되지 않도록 설정한다.
void sigint_handler(int sig)
{
    sio_puts("\n");
}

ssize_t sio_puts(char s[])
{
    return write(STDOUT_FILENO, s, sio_strlen(s));
}

static size_t sio_strlen(char s[])
{
    int i = 0;

    while (s[i] != '\0')
        ++i;
    return i;
}
