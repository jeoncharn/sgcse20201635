/* made by 20201635 jeoncharn */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node* nodepointer;
typedef struct node{
	char name[20];
	nodepointer next;	
} Node;

void input(nodepointer head, char* name);
void delete(nodepointer head, char* name);

int main()
{
	int input_num;
	Node* head_node;
	Node* temp;
	char* leave = "leave";
	char name[20];
	char check[6];
	
	head_node = (Node*)malloc(sizeof(Node));
	head_node->next = NULL;

	scanf("%d", &input_num);

	for(int i=1; i<=input_num; i++)
	{
		scanf("%s %s", name, check);
		if(strcmp(check, leave)==0)
		{
			delete(head_node, name);
		}
		else
		{
			input(head_node, name);
		}
	}
	temp = head_node;
	head_node = head_node->next;
	free(temp);

	while(head_node!=NULL)
	{
		printf("%s\n", head_node->name);
		temp = head_node;
		head_node = head_node->next;
		free(temp);
	}

	return 0;
}

void input(nodepointer head, char* name)
{
	Node* newnode = (Node*)malloc(sizeof(Node));
	Node* temp;
	strcpy(newnode->name, name);

	while(1)
	{

		if(head->next == NULL)
		{
			head->next = newnode;
			newnode->next = NULL;
			break;
		}
		else if(strcmp((head->next)->name, name)<0)
		{
			head = head->next;
		}
		else
		{
			temp = head->next;
			head->next = newnode;
			newnode->next = temp;
			break;
		}
	}

	return;
}

void delete(nodepointer head, char* name)
{
	Node* temp;
	while(1)
	{
		if(strcmp((head->next)->name, name)<0)
		{
			head = head->next;
		}
		else
		{
			temp = head->next->next;
			free(head->next);
			head->next = temp;
			break;
		}
	}
	return;
}

