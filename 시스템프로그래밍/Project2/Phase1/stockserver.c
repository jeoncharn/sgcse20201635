/* 
 * stockserver.c - An concurrent stock server, event based

 //  Created by Jeon Charn on 2022/05/09 ~ 2022/04/01.
 
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

typedef struct {
    int maxfd;
    fd_set read_set;
    fd_set ready_set;
    int nready;
    int maxi;
    int clientfd[FD_SETSIZE];
    rio_t clientrio[FD_SETSIZE];
} pool;

int byte_cnt = 0;

Node* rootnode = NULL; // tree data의 Root node를 의미한다.

void echo(int connfd);
void tree_data(Node* root);
void init_pool(int listenfd, pool* p);
void add_client(int connfd, pool* p);
void check_clients(pool* p);

int main(int argc, char **argv) 
{
    int listenfd, connfd;
    socklen_t clientlen = sizeof(sockaddr_storage);
    struct sockaddr_storage clientaddr;  /* Enough space for any address */  //line:netp:echoserveri:sockaddrstorage
    static pool pool;
    char client_hostname[MAXLINE], client_port[MAXLINE];

    if (argc != 2) {
	fprintf(stderr, "usage: %s <port>\n", argv[0]);
	exit(0);
    }

    tree_data(rootnode);
    
    listenfd = Open_listenfd(argv[1]);
    init_pool(listenfd, &pool);
    
    while (1) {
        pool.ready_set = pool.read_set;
        pool.nready = Select(pool.maxfd + 1, &pool.ready_set, NULL, NULL, NULL);
        
        if(FD_ISSET(listenfd, &pool.ready_set)){
            connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
            add_client(connfd, &pool);
        }
        
        check_clients(&pool);
    }
}
/* $end echoserverimain */


void tree_data(Node* root){
    
    data = fopen("stock.txt", "r");
    int stock_id;
    int num;
    int cost;
    while(!feof(data)){
        fscanf(data, "%d %d %d\n", &stock_id, &num, &cost);
        
        Node* new_node = malloc(sizeof(Node));
        new_node->stock_id = stock_id;
        new_node->num = num;
        new_node->cost = cost;
        new_node->left = NULL;
        new_node->right = NULL;
        
        if(root == NULL){
            root = new_node;
        }
        
        else{
            node* insert_pos = root;
            while(insert_pos->left!=NULL&&insert_pos->stock_id>new_node->stock_id || insert_pos->right!=NULL&&insert_pos->stock_id<new_node->stock_id){
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
    close(data);
    
    return;
}

void init_pool(int listenfd, pool* p){
    p->maxi = -1;
    for(int i=0; i<FD_SETSIZE; i++){
        p->clientfd[i] = -1;
    }
    
    p->maxfd = listenfd;
    FD_ZERO(&p->read_set);
    FD_SET(listenfd, &p->read_set);
}

void add_client(int connfd, pool* p){
    int i;
    p->nready--;
    for(i = 0; i<FD_SETSIZE; i++){
        if(p->clientfd[i] < 0){
            p->clientfd[i] = connfd;
            Rio_readinitb(&b->clientrio[i], connfd);
            
            FD_SET(connfd, &p->read_set);
            
            if(connfd > p->maxfd){
                p->maxfd = connfd;
            }
            if(i > p->maxi){
                p->maxi = i;
            }
            break;
        }
    }
    if(i == FD_SETSIZE){
        app_error("add_client error : Too many clients\n");
    }
}

void check_clients(pool* p){
    int i, connfd, n;
    char buf[MAXLINE];
    rio_t rio;
    
    for(i = 0; (i<=p->maxi)&&(p->nready>0); i++){
        connfd = p->clientfd[i];
        rio = p->clientrio[i];
        
        if((connfd>0) && (FD_ISSET(connfd, &p->ready_set))){
            p->nready--;
            if((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0){
                byte_cnt += n;
                
                // readline이 존재하는 경우, 각 경우에 맞는 행동을 수행한다.
                if(strcmp(buf, "exit")){
                    
                }
                else if(strcmp(buf, "exit")){
                    
                }
                else if(strcmp(buf, "exit")){
                    
                }
            }
            
            else{
                Close(connfd);
                FD_CLR(connfd, &p->read_set);
                p->clientfd[i] = -1;
            }
        }
    }
    
    
}
