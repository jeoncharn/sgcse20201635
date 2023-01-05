//
//  myshell
//
//  Created by Jeon Charn on 2022/04/03 ~ 2022/04/10
//


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

//fg, bg process를 저장하기 위한 전역 변수
struct executing_process process;
struct bg_process* bg_process = NULL;
int bg_counter = 1;

int main() {
    
    char cmdline[MAXLINE];
    
    // SIGINT(ctrl+C signal)에 대한 signal handler 설정
    if(signal(SIGINT, sigint_handler) == SIG_ERR){
        sio_puts("sigint install error exists.\n");
        exit(0);
    }
    
    // SIGCHLD(child end signal)에 대한 signal handler 설정
    if(signal(SIGCHLD, sigchld_handler) == SIG_ERR){
        sio_puts("sigchld install error exists.\n");
        exit(0);
    }
    
    // SIGSTP(ctrl+Z)에 대한 signal handler 설정
    if(signal(SIGTSTP, sigstp_handler) == SIG_ERR){
        sio_puts("sigstp install error exists.\n");
        exit(0);
    }

    
    // shell의 실행 부분
    while(1){
        process.running = 0;
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
    int bg;
    int j = 0; // pipe 개수를 count하는 변수이다.
    int k = 0;// decompose_argv를 저장하기 위한 변수이다.
    
    strcpy(buf, cmdline);
    
    //Phase 1, 2와 다르게 bg인지 fg인지를 parseline()의 return value로 파악한다.
    bg = parseline(buf, argv);
    
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
    pipe_execute(decompose_argv, STDIN_FILENO, 0, j+1, bg);
    return;
}

void pipe_execute(char* decompose_argv[MAXARGS][10], int fd_in, int argv_num, int argv_left, int bg){
    pid_t pid;
    int status;
    int fd[2];
    
    // foreground executing process strunct에 현재 실행하는 정보를 저장한다.
    strcpy(process.command, "");
    for(int i=0; decompose_argv[argv_num][i]!=NULL; i++){
        strcat(process.command, decompose_argv[argv_num][i]);
        strcat(process.command, " ");
    }
    
    if(!bg){
        process.running = 1;
    }
    
    //실행할 command가 1개 남은 경우
    if(argv_left == 1){
        
        if(!builtin_command(decompose_argv[argv_num])){
            if((pid = Fork()) != 0){
                process.pid = pid;
            }
            
            else{
                // child process들이 ctrl + C signal을 무시하게 만들기 위한 mask
                sigset_t mask;
                
                sigemptyset(&mask);
                sigaddset(&mask, SIGINT);
                sigprocmask(SIG_BLOCK, &mask, NULL);
                

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
            
            if(!bg){
                waitpid(process.pid, &status, WUNTRACED);
            }
            else{
                add_to_list(1);
            }
        }
        
        return;
    }
    
    else{
        if(pipe(fd) < 0){
            sio_puts("there was pipe function error.\n");
            return;
        }
        if(!builtin_command(decompose_argv[argv_num])){
            if((pid = Fork()) != 0){
                process.pid = pid;
            }
            
            else{
                sigset_t mask;
                
                sigemptyset(&mask);
                sigaddset(&mask, SIGINT);
                sigprocmask(SIG_BLOCK, &mask, NULL);
                
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
            if(bg){
                add_to_list(1);
            }
            pipe_execute(decompose_argv, fd[0], argv_num + 1, argv_left - 1, bg);
            close(fd[0]);
            if(!bg){
                waitpid(process.pid, &status, WUNTRACED);
            }
        }
        
        return;
    }
}

int builtin_command(char **argv)
{
    if(!strcmp(argv[0], "exit")){ /* exit command */
        kill_all_list();
        exit(0);
    }
    
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
    
    else if(!strcmp(argv[0], "jobs")){
        print_all_bg_jobs();
        
        return 1;
    }
    
    else if(!strcmp(argv[0], "bg")){
        bg_execute(argv[1]);
        
        return 1;
    }
    
    else if(!strcmp(argv[0], "fg")){
        fg_execute(argv[1]);
        
        return 1;
    }
    
    else if(!strcmp(argv[0], "kill")){
        kill_process(argv[1]);
        
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

// input string을 단위별로 끊어내는 함수이다. &(bg 이면)가 존재하면 1, fg이면 0을 값으로 갖는다.
int parseline(char *buf, char **argv)
{
    int argc = 0;            /* Number of args */
    int save_flag = 0;
    int length;
    
    // input이 존재하지 않는 경우, 바로 return 한다.
    if(strlen(buf) == 1){
        argv[0] = NULL;
        return 0;
    }
    
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
    
    //background인지 foreground인지 파악하는 코드
    if(!strcmp(argv[argc-1],"&")){
        argv[argc-1] = NULL;
        return 1;
    }
    
    return 0;
    
}

            
void add_to_list(int bg_execute) // ctrl + Z가 입력되었을 경우, 혹은 bg execute 인 경우 list에 추가하는 함수, bg_execute = 1인 경우 running, 그 외의 경우 suspended 형태로 저장한다.
{
    struct bg_process* new_process = (struct bg_process*)malloc(sizeof(struct bg_process));
    
    new_process->next = NULL;
    
    //char* 로 link하는 경우, 새로운 cmdline을 input 받으면 발생할 수 있는 error 존재.
    //char[~~] 로 설정한 이후, strcat을 이용한다.
    strcpy(new_process->command, process.command);
    new_process->pid = process.pid;
    new_process->num = bg_counter++;
    
    // bg_execute에 의해 추가되는 경우, running mode 이다.
    if(bg_execute){
        new_process->mode = 1;
    }
    // sigstp에 의해 추가되는 경우, stopped mode 이다.
    else{
        new_process->mode = 0;
    }
    
    //linked list의 마지막에 저장한다.
    if(bg_process == NULL){
        bg_process = new_process;
    }
    
    else{
        struct bg_process* search_process = bg_process;
        
        while(search_process->next != NULL){
            search_process = search_process->next;
        }
        
        search_process->next = new_process;
        
    }
    
    return;
}

void kill_all_list(void) // exit으로 종료하는 경우, 남아있는 bg process를 모두 kill 하는 함수.
{
    struct bg_process* next_process = bg_process;
    while(next_process!=NULL){
        next_process = next_process->next;
        kill(bg_process->pid, SIGKILL);
        bg_process = next_process;
    }
    
    return;
}

void print_all_bg_jobs(void) // jobs의 실행을 위한 함수
{
    
    struct bg_process* search_process = bg_process;

    while(search_process != NULL){
        sio_puts("[");
        sio_putl(search_process->num);
        sio_puts("] ");
        
        if(search_process->mode){
            sio_puts("running ");
        }
        else{
            sio_puts("suspended ");
        }
        
        sio_puts(search_process->command);
        sio_puts("\n");
        
        search_process = search_process->next;
    }
}

void bg_execute(char* num) // stopped bg job을 bg running 시킨다.
{
    if(num == NULL){
        sio_puts("bg usage : bg %job_number\n");
        return;
    }
    
    struct bg_process* search_process = bg_process;
    int converted_num = atoi(num + 1);
    
    if(converted_num == 0){
        sio_puts("bg usage : bg %job_number\n");
        return;
    }

    while(search_process != NULL){
        if(search_process->num == converted_num){
            if(search_process->mode == 0){
                if(kill(search_process->pid, SIGCONT)<0){
                    sio_puts("there is kill command error on bg command\n");
                    return;
                }
                sio_puts("[");
                sio_puts(num+1);
                sio_puts("] ");
                sio_puts("running ");
                sio_puts(search_process->command);
                sio_puts("\n");
                search_process->mode = 1;
                return;
            }
            else{
                sio_puts("This process already running in background.\n");
                return;
            }
        }
        search_process = search_process->next;
    }
    sio_puts("No such Job\n");
    printf("does it happened?\n");
    
    return;
    
}


void fg_execute(char* num) // stopped / running bg job을 fg running 시킨다.
{
    int status;
    
    if(num == NULL){
        sio_puts("fg usage : fg %job_number\n");
        return;
    }
    
    struct bg_process* search_process;
    struct bg_process* save_process;

    int converted_num = atoi(num + 1);
    
    if(converted_num == 0){
        sio_puts("fg usage : fg %job_number\n");
        return;
    }
    
    // bg process를 fg process로 바꾸며, 실행한다. 또한 bg linked list에 있는 해당 process를 제거해준다.
    if(bg_process != NULL){
        
        search_process = bg_process;
        
        // 맨 처음 element인 경우
        if(bg_process->num == converted_num){
            if(bg_process->mode == 0){
                if(kill(search_process->pid, SIGCONT)<0){
                    sio_puts("there is kill command error on fg command\n");
                    return;
                }
                
                bg_process->mode = 1;
            }
            process.pid = bg_process->pid;
            strcpy(process.command, bg_process->command);
            process.running = 1;
            
            sio_puts("[");
            sio_puts(num+1);
            sio_puts("] ");
            sio_puts("running ");
            sio_puts(process.command);
            sio_puts("\n");
            
            save_process = bg_process->next;
            free(bg_process);
            bg_process = save_process;
            
            waitpid(process.pid, &status, WUNTRACED);
            return;
        }
        
        //이외의 경우
        else{
            while(search_process->next != NULL){
                if(search_process->next->num == converted_num){
                    
                    save_process = search_process->next;
                    
                    if(save_process->mode == 0){
                        if(kill(search_process->pid, SIGCONT)<0){
                            sio_puts("there is kill command error on fg command\n");
                            return;
                        }
                        save_process->mode = 1;
                    }
                    process.pid = save_process->pid;
                    strcpy(process.command, save_process->command);
                    process.running = 1;
                    
                    sio_puts("[");
                    sio_puts(num+1);
                    sio_puts("] ");
                    sio_puts("running ");
                    sio_puts(process.command);
                    sio_puts("\n");
                    
                    search_process->next = search_process->next->next;
                    free(save_process);
                    
                    waitpid(process.pid, &status, WUNTRACED);
                    return;
                }
                search_process = search_process->next;
            }
        }
    }
    
    sio_puts("No such Job\n");
    
    return;
}

// input num에 해당하는 process를 종료하는 함수
void kill_process(char* num)
{
    if(num == NULL){
        sio_puts("kill usage : kill %job_number\n");
        return;
    }
    
    int converted_num = atoi(num + 1);
    
    if(converted_num == 0){
        sio_puts("kill usage : kill %job_number\n");
        return;
    }
    
    struct bg_process* search_process = bg_process;

    while(search_process != NULL){
        if(search_process->num == converted_num){
            if(kill(search_process->pid, SIGKILL)<0){
                sio_puts("kill command error exists.\n");
            }
            return;
        }
        search_process = search_process->next;
    }
    
    sio_puts("No such Job\n");
    
    return;
}



//sigint(ctrl+C)를 받는 경우, shell은 종료되지 않도록 설정한다.
void sigint_handler(int sig)
{
    sio_puts("\n");
    if(process.running == 1){
        kill(process.pid, SIGKILL);
        
    }
}

void sigchld_handler(int sig)
{
    
    int errno_before = errno;
    int status;
    pid_t pid;
    struct bg_process* search_process;
    struct bg_process* save_process;
    
    // fg에서 running중인 경우, waitpid로 reap 를 수행하기 때문에, 별다른 signal handling을 수행하지 않는다.
    if(process.running){
        return;
    }
    
    // bg 의 process가 종료된 경우, reaping함과 동시에, 해당 pid를 가진 process를 linked list에서 제거해 주어야 한다.
    while((pid = waitpid(-1, &status, WNOHANG)) > 0){
        //bg process가 존재하는 경우, 실행이 종료된 bg process를 linked list에서 삭제해야 한다.
        if(bg_process != NULL){
            search_process = bg_process;
            
            // 첫 bg process가 종료된 경우
            if(bg_process->pid == pid){
                save_process = bg_process->next;
                free(bg_process);
                bg_process = save_process;
            }
            
            else{
                while(search_process->next != NULL){
                    if(search_process->next->pid == pid){
                        save_process = search_process->next;
                        search_process->next = search_process->next->next;
                        free(save_process);
                        break;
                    }
                    search_process = search_process->next;
                }
            }
        }
    }
    errno = errno_before;
    return;
}

// ctrl + Z가 입력된 경우, 적절한 형태로 signal을 처리한다.
void sigstp_handler(int sig)
{
    sio_puts("\n");
    if(process.running){
        add_to_list(0);
    }
    // bg process도 SIGTSTP를 받기 때문에, suspended 될 수 있다.
    // 따라서 모든 sigcont를 통해 정지된 bg process를 실행시켜야 한다.
    // 하지만 이미 정지되어 있는 bg process의 경우에는 SIGCONT를 보내지 않아도 된다.
    struct bg_process* read_process = bg_process;
    while(read_process!=NULL){
        if(read_process->mode == 1){
            kill(read_process->pid, SIGCONT);
        }
        read_process = read_process->next;
    }
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

ssize_t sio_putl(long v) /* Put long */
{
    char s[128];
    
    sio_ltoa(v, s, 10); /* Based on K&R itoa() */  //line:csapp:sioltoa
    return sio_puts(s);
}

static void sio_ltoa(long v, char s[], int b)
{
    int c, i = 0;
    
    do {
        s[i++] = ((c = (v % b)) < 10)  ?  c + '0' : c - 10 + 'a';
    } while ((v /= b) > 0);
    s[i] = '\0';
    sio_reverse(s);
}

static void sio_reverse(char s[])
{
    int c, i, j;

    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
