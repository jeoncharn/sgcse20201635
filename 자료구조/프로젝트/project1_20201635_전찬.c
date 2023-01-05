//
//  main.c
//  tree_project
//
//  Created by Jeon Charn on 2021/05/29.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct student{
    char id[10];
    char name[40];
    char course[40];
    int score;
} STUDENT;

typedef struct _treenode* Treepointer;
typedef struct _treenode{
    STUDENT student_info;
    struct _treenode* left_child;
    struct _treenode* right_child;
} TreeNode;

int InsertNode(TreeNode* root, STUDENT key);
int DeleteNode(TreeNode* root, char* id);
void SearchCourse(TreeNode* node, char* course);
void SearchName(TreeNode* node, char* name);
int SearchID(TreeNode* node, char* id);
void MakeTree(TreeNode** root);
void SaveTree(TreeNode* root, FILE* savefile);

int main() {
    // insert code here...
    //첫 번째 문제는 How to make balanced binary search tree??
    //프로그램이 처음 실행인지, 그 이후 실행인지 알 방법이 없다. 그냥 preorder로 읽어들여야 하는가?
    TreeNode* root = NULL;
    FILE* savefile;

    MakeTree(&root);
    
    
    savefile = fopen("input.txt", "w"); // 저장할 파일의 이름, 나중에 input.txt로 변경
    SaveTree(root, savefile);
    fclose(savefile);
    
    return 0;
}

// InsertNode 또한 root의 값은 변경할 수 없다.
int InsertNode(TreeNode* root, STUDENT key)
{
    //1. malloc을 통해 동적 할당 가능한가, 2. search했을 때 같은 id 값이 없는가? 이후에 저장
    TreeNode* newnode = (TreeNode*)malloc(sizeof(TreeNode));
    TreeNode* temp = root;
    if(newnode==NULL)
    {
        printf("we can't insert a node(malloc issue!)\n");
        return 0;
    }
    newnode->student_info = key;
    newnode->left_child = NULL;
    newnode->right_child = NULL;
    
    while(1)
    {
        if(atoi(key.id)<atoi(temp->student_info.id))
        {
            if(temp->left_child==NULL)
            {
                break;
            }
            
            temp = temp->left_child;
        }
        else if(atoi(key.id)>atoi(temp->student_info.id))
        {
            if(temp->right_child==NULL)
            {
                break;
            }
            temp = temp->right_child;

        }
        else
        {
            printf("the id %s already exist!\n", key.id);
            free(newnode); // 동적할당을 수행했지만, 이미 그 id가 존재하는 경우
            return 0;
        }
    }
    
    if(atoi(key.id)<atoi(temp->student_info.id))
    {
        temp->left_child = newnode;
    }
    else
    {
        temp->right_child = newnode;
    }
    
    return 1;
}

//15를 제거하고 싶었는데 14가 제거됨 ㅇㅇ
int DeleteNode(TreeNode* root, char* id)
{
    //id가 같은 node가 있는가, child 가 2개 존재할 때 제거 방법?
    //root를 바꿀 수는 없기 때문에, root를 삭제하는 경우는 right 또는 left의 student info를 복사해오는 형식으로 구현
    TreeNode* temp = root; // 삭제 노드의 부모 노드를 저장하는 변수
    TreeNode* temp_before = NULL;
    
    //삭제 node가 root node인 경우에
    if(strcmp(root->student_info.id, id)==0)
    {
        if(root->left_child&&root->right_child)
        {
            STUDENT save = root->right_child->student_info;
            DeleteNode(root, save.id);
            root->student_info = save;
            
        }
        
        else if(root->left_child)
        {
            TreeNode* save = root->left_child;
            root->student_info = save->student_info;
            root->left_child = save->left_child;
            root->right_child = save->right_child;

            free(save);
        }
        
        else if(root->right_child)
        {
            TreeNode* save = root->right_child;
            root->student_info = save->student_info;
            root->left_child = save->left_child;
            root->right_child = save->right_child;
            
            free(save);
        }
        
        return 1;
        // 둘 다 null 인 경우는 고려해주지 않는다.(root node 하나만 존재한다는 의미이다.)
    }
    
    else
    {
        while(temp!=NULL)
        {
            
            if(atoi(id)<atoi(temp->student_info.id))
            {
                temp_before = temp;
                temp = temp->left_child;
            }
            else if(atoi(id)>atoi(temp->student_info.id))
            {
                temp_before = temp;
                temp = temp->right_child;
            }
            //id를 찾은 경우
            else
            {
                if(temp->left_child&&temp->right_child)
                {
                    STUDENT save = temp->right_child->student_info;
                    DeleteNode(root, save.id);
                    temp->student_info = save;
                }
                else if(temp->left_child)
                {
                    TreeNode* save = temp->left_child;
                    temp->student_info = save->student_info;
                    temp->left_child = save->left_child;
                    temp->right_child = save->right_child;
                    free(save);
                }
                else if(temp->right_child)
                {
                    TreeNode* save = temp->right_child;
                    temp->student_info = save->student_info;
                    temp->left_child = save->left_child;
                    temp->right_child = save->right_child;
                    free(save);
                }
                //leaf node를 삭제하는 경우
                else
                {
                    if(atoi(temp->student_info.id)<atoi(temp_before->student_info.id))
                    {
                        temp_before->left_child = NULL;
                        free(temp);
                    }
                    else
                    {
                        temp_before->right_child = NULL;
                        free(temp);
                    }
                }
                
                return 1;
            }
        }
    }
    return 0;
}

void SearchCourse(TreeNode* node, char* course)
{
    if(node!=NULL)
    {
        SearchCourse(node->left_child, course);
        if(strcmp(node->student_info.course, course)==0)
        {
            printf("%s %s %s %d\n", node->student_info.id, node->student_info.name, node->student_info.course, node->student_info.score);
        }
        SearchCourse(node->right_child, course);
    }
    
    return;
}

void SearchName(TreeNode* node, char* name)
{
    if(node!=NULL)
    {
        SearchName(node->left_child, name);
        if(strcmp(node->student_info.name, name)==0)
        {
            printf("%s %s %s %d\n", node->student_info.id, node->student_info.name, node->student_info.course, node->student_info.score);
        }
        SearchName(node->right_child, name);
    }
    
    return;
}

int SearchID(TreeNode* node, char* id)
{
    while(node!=NULL)
    {
        if(strcmp(id, node->student_info.id)==0)
        {
            printf("%s %s %s %d\n", node->student_info.id, node->student_info.name, node->student_info.course, node->student_info.score);
            
            return 1;
        }
        
        else if(atoi(id)<atoi(node->student_info.id))
        {
            node = node->left_child;
        }
        
        else
        {
            node = node->right_child;
        }
    }
    
    return 0;
}

void MakeTree(TreeNode** root)
{
    //data가 preorder or not을 알 수 있는 방법 존재?
    STUDENT input_student;
    FILE* datafile = fopen("input.txt", "r");
    
    while(fscanf(datafile,"%s %s %s %d\n", input_student.id, input_student.name, input_student.course, &(input_student.score))!=EOF)
    {
        if(*root==NULL) // 빈 tree 인 경우에(input의 첫번째 줄)
        {
            TreeNode* newnode = (TreeNode*)malloc(sizeof(TreeNode));
            if(newnode==NULL)
            {
                printf("we can't make tree(malloc issue!)\n");
                exit(1);
            }
            newnode->student_info = input_student;
            newnode->left_child = NULL;
            newnode->right_child = NULL;
            *root = newnode;
        }
        else
        {
            if(!InsertNode(*root, input_student))
            {
                fclose(datafile);
                exit(1);
            }
        }
    }
    fclose(datafile);
    
    return;
}

void SaveTree(TreeNode* root, FILE* savefile)
{
    if(root!=NULL)
    {
        fprintf(savefile, "%s %s %s %d\n", root->student_info.id, root->student_info.name, root->student_info.course, root->student_info.score);
        SaveTree(root->left_child, savefile);
        SaveTree(root->right_child, savefile);
        free(root);
    }
    
    return;
}
