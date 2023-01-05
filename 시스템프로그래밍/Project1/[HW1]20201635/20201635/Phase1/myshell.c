//
//  myshell
//
//  Created by Jeon Charn on 2022/03/30 ~ 2022/04/01.
//

#include "myshell.h"

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
    
    strcpy(buf, cmdline);
    parseline(buf, argv);
    
    execute(argv);
    return;
}

void execute(char** argv){
    pid_t pid;
    int status;
    
    // when input dosen't exist(only composed in blankspace)
    if(argv[0] == NULL){
        return;
    }
    
    // builtin command에 존재하지 않는 경우, fork() -> execute() 과정을 수행한다.
    if(!builtin_command(argv)){
        if((pid = Fork()) == 0){
            if(execvp(argv[0], argv) < 0){
                sio_puts(argv[0]);
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

int builtin_command(char **argv)
{
    if(!strcmp(argv[0], "exit")) /* exit command */
    exit(0);
    
    // command input이 cd인 경우
    else if(!strcmp(argv[0], "cd")){
        if(argv[1] == NULL){
            // cd만 input인 경우, getenv("HOME")을 통해 HOME으로의 cd를 수행한다.
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

// input command를 단위별로 나누는 함수이다.
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
