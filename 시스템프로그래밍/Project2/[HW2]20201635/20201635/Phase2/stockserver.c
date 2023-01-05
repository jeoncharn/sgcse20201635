/*
 * stockserver.c - An concurrent stock server, thread based

 //  Created by Jeon Charn on 2022/05/11 ~ 2022/05/~~.
 
 */
#include "csapp.h"

typedef struct node{
    int stock_id;
    int num;
    int cost;
    struct node* left;
    struct node* right;
    sem_t mutex;
} Node;


Node* rootnode = NULL; // tree data의 Root node를 의미한다.

void tree_data(void);
void save_data(Node* node, FILE* file);
void sigint_handler(int sig);
void show(Node* root, char* data, char* save);
Node* find(Node* root, int id);
void* thread(void* vargp);
void stock(int connfd);

int main(int argc, char **argv)
{
    int listenfd, *connfdp;
    socklen_t clientlen = sizeof(struct sockaddr_storage);
    struct sockaddr_storage clientaddr;  /* Enough space for any address */  //line:netp:echoserveri:sockaddrstorage
    char client_hostname[MAXLINE], client_port[MAXLINE];
    pthread_t tid;
    
    
    if (argc != 2) {
    fprintf(stderr, "usage: %s <port>\n", argv[0]);
    exit(0);
    }
    
    signal(SIGINT, sigint_handler);
    tree_data();
    
    listenfd = Open_listenfd(argv[1]);
    
    while (1) {
        connfdp = Malloc(sizeof(int));
        *connfdp = Accept(listenfd, (SA *) &clientaddr, &clientlen);
        Getnameinfo((SA *) &clientaddr, clientlen, client_hostname, MAXLINE,
                    client_port, MAXLINE, 0);
        printf("Connected to (%s, %s)\n", client_hostname, client_port);
        Pthread_create(&tid, NULL, thread, connfdp);
    }
}
/* $end echoserverimain */


void tree_data(void){
    
    FILE* data = fopen("stock.txt", "r");
    int stock_id;
    int num;
    int cost;
    while(!feof(data)){
        if(fscanf(data, "%d %d %d\n", &stock_id, &num, &cost) < 3){
            fprintf(stderr, "stock data scan have some error\n");
            exit(0);
        }
        
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->stock_id = stock_id;
        new_node->num = num;
        new_node->cost = cost;
        new_node->left = NULL;
        new_node->right = NULL;
        Sem_init(&new_node->mutex, 0, 1);
        
        if(rootnode == NULL){
            rootnode = new_node;
        }
        
        else{
            Node* insert_pos = rootnode;

            while(((insert_pos->left!=NULL)&&(insert_pos->stock_id>new_node->stock_id)) || ((insert_pos->right!=NULL)&&(insert_pos->stock_id<new_node->stock_id))){
                if(insert_pos->stock_id > new_node->stock_id){
                    insert_pos = insert_pos->left;
                }
                else{
                    insert_pos = insert_pos->right;
                }
            }
            if(insert_pos->stock_id > new_node->stock_id){
                insert_pos->left = new_node;
            }
            else{
                insert_pos->right = new_node;
            }
        }
    }
    fclose(data);
    
    return;
}


void show(Node* root, char* data, char* save){
    if(root != NULL){
        sprintf(save, "%d %d %d\n", root->stock_id, root->num, root->cost);
        strcat(data, save);
        show(root->left, data, save);
        show(root->right, data, save);
    }
    
    return;
}

Node* find(Node* root, int id){
    if(root == NULL){
        return NULL;
    }
    
    if(root->stock_id == id){
        return root;
    }
    else{
        if(root->stock_id > id){
            return find(root->left, id);
        }
        else{
            return find(root->right, id);
        }
    }
}

void save_data(Node* node, FILE* file){
    if(node != NULL){
        fprintf(file, "%d %d %d\n", node->stock_id, node->num, node->cost);
        save_data(node->left, file);
        save_data(node->right, file);
    }
    
    return;
}

void *thread(void *vargp)
{
    int connfd = *((int *)vargp);
    Pthread_detach(pthread_self()); //line:conc:echoservert:detach
    Free(vargp);                    //line:conc:echoservert:free
    stock(connfd);
    Close(connfd);
    return NULL;
}

void stock(int connfd){
    char buf[MAXLINE];
    char data[MAXLINE];
    rio_t rio;
    int n;

    Rio_readinitb(&rio, connfd);
    while((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0) {
        
        printf("server received %d bytes\n", n);
        // readline이 존재하는 경우, 각 경우에 맞는 행동을 수행한다.
        if(!strcmp(buf, "show\n")){
            char save[MAXLINE];
            strcpy(data, "");
            show(rootnode, data, save);
            Rio_writen(connfd, data, MAXLINE);
        }
        
        else if(!strcmp(buf, "exit\n")){
            strcpy(data, buf);
            Rio_writen(connfd, data, MAXLINE);
            break;
        }
        
        else{
            int i, j;
            int len = strlen(buf);
            // '\n' 처리하기
            buf[len - 1] = '\0';
            for(i=0; i<len; i++){
                if(buf[i] == ' '){
                    buf[i] = '\0';
                    i++;
                    break;
                }
            }
            
            for(j=i; j<len; j++){
                if(buf[j] == ' '){
                    buf[j] = '\0';
                    j++;
                    break;
                }
            }
            
            if(!strcmp(buf, "buy")){
                int buy_id = atoi(&buf[i]);
                int buy_num = atoi(&buf[j]);
                Node* node = find(rootnode, buy_id);
                if(node == NULL){
                    strcpy(data, "There are no such stock\n");
                    Rio_writen(connfd, data, MAXLINE);
                }
                
                else{
                    if(buy_num > node->num){
                        strcpy(data, "Not enough left stock\n");
                        Rio_writen(connfd, data, MAXLINE);
                    }
                    else{
                        P(&node->mutex);
                        node->num -= buy_num;
                        V(&node->mutex);
                        strcpy(data, "[buy] success\n");
                        Rio_writen(connfd, data, MAXLINE);
                    }
                }
                
                
            }
            else{
                int sell_id = atoi(&buf[i]);
                int sell_num = atoi(&buf[j]);
                Node* node = find(rootnode, sell_id);
                if(node == NULL){
                    strcpy(data, "There are no such stock\n");
                    Rio_writen(connfd, data, MAXLINE);
                }
                
                else{
                    P(&node->mutex);
                    node->num += sell_num;
                    V(&node->mutex);
                    strcpy(data, "[sell] success\n");
                    Rio_writen(connfd, data, MAXLINE);
                }
            }
        }
    }
    return;
}

void sigint_handler(int sig){
    printf("The server program ended.\n");
    FILE* save_file = fopen("stock.txt", "w");
    save_data(rootnode, save_file);
    fclose(save_file);
    
    exit(0);
}
