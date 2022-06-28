#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void split(char *src, const char *separator, char **dest, int *num)
{
	char *pNext;
	int count = 0;
	if (src == NULL || strlen(src) == 0) return;
	if (separator == NULL || strlen(separator) == 0) return;
	pNext = strtok(src,separator);
	while(pNext != NULL) {
		*dest++ = pNext;
		++count;
		pNext = strtok(NULL,separator);
	}
	*num = count;
}

int main()
{
	char src[] = "10,20,30,40";
	char *dest[128];
	int num = 0, num2 = 0;
	split(src,",",dest,&num);
	for (int i=0; i<num; i++) {
		printf("|%s|\n",dest[i]);
	}
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct node {
	char* data;
	struct node* next;
};
struct node* split(char *src, const char *del) {
	char *pNext;
	struct node* p=(struct node*)malloc(sizeof(struct node));
	struct node *head=p,*newnode;
	int count = 0;
	
	pNext = strtok(src,del);
	while(pNext != NULL) {
		newnode=(struct node*)malloc(sizeof(struct node));
		newnode->next=NULL;
		p->next=newnode;
		p->data=(char*)malloc(sizeof(char)*(strlen(pNext)+1));
		memcpy(p->data,pNext,strlen(pNext)+1);
		p=p->next;
		pNext = strtok(NULL,del);
	}
	return head;
}
void print(struct node* head){
	while(head->next){
	puts(head->data);
	head=head->next;
	}
}
int main()
{
	char src[] = "10,20,30,40";
	struct node* head;
	head=split(src,",");
	print(head);
	return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//
typedef struct Node {
	char* data;
	struct Node* next;
} node,*pnode;
//
pnode split(char *src, const char *del)
{
	pnode p=(pnode)malloc(sizeof(node));
	pnode head=p,newnode;
	//
	char *pNext = strtok(src,del);
	while(pNext != NULL) {
		newnode=(pnode)malloc(sizeof(node));
		newnode->next=NULL;
		p->next=newnode;
		p->data=(char*)malloc(strlen(pNext)+1);
		memcpy(p->data,pNext,strlen(pNext)+1);
		p=p->next;
		pNext = strtok(NULL,del);
	}
	return head;
}
void print(pnode head)
{
	while(head->next) {
		puts(head->data);
		head=head->next;
	}
}
int main()
{
	char src[] = "10,20,30,40";
	pnode head=split(src,",");
	print(head);
	return 0;
}