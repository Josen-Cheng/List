#include <stdio.h>
#include <string.h>
#include <malloc.h>
/******************************************************************************
* File       : List.c
* Function   : One-way linked list
* Description: The basic operation of linked list.
* Author     : Taijizhch
* Date       : 18th November 2017
******************************************************************************/

#define OK           (0)              /*it is return value               */ 
#define ERROR        (1)    	      /*it is return value               */ 
#define HEAD_NODE    (1)              /*it is a flag of head_node        */
#define HEAD_WAY     OK		      /*it is a insert way of the node   */
#define TAIL_WAY     ERROR	      /*it is a insert way of the node   */
#define MAX_NUM      10               /*it is size of array              */

/*Define the structure*/
typedef struct node
{
 	int data[MAX_NUM];
    	struct node *next;
}Node;
/******************************************************************************
* Name       : int Array_Init(int *addr,int length,int value)
* Function   : Initialize the array of structures
******************************************************************************/
int Array_Init(int *addr,int length,int value)
{
	int cnt;
   	for(cnt=0;cnt<length;cnt++){
    		addr[cnt]=value;
    	}
    	return OK;
}
/******************************************************************************
* Name       : int Creat_List(Node **pList,int size, char mode)
* Function   : Creat a linked list.
******************************************************************************/
int Creat_List(Node **pList,int size, char mode)
{
	Node *p=NULL,*sList = NULL;

    	sList=(Node*)malloc(sizeof(struct node));
    	if(sList==NULL){
		printf("List creat failed!\n");
    	}

    	Array_Init(sList->data,MAX_NUM,0);
    	sList->next=NULL;
    	*pList=sList;

    	if(HEAD_WAY==mode)  
    	{
       		while(size--)
        	{
            		sList=(struct node*)malloc(sizeof(Node));
            		if(sList==NULL){
                	printf("List Creat failed!\n");
            		}
            	Array_Init(sList->data,MAX_NUM,0);
           	sList->next=*pList;
            	*pList=sList;
        	}
   	}
    	else if(TAIL_WAY==mode)  
    	{
        	p=*pList;
       	 	while(size--)
        	{
            		sList=(struct node*)malloc(sizeof(Node));
            		p->next = sList;
           	 	Array_Init(sList->data,MAX_NUM,0);
            		sList->next = NULL;
            		p=sList;
        	}
    	}
    	else{
       		printf("Mode is 0 or 1\n");
        	return ERROR;
    	}

    	printf("List Creat success!\n");
    	return OK;
}
/******************************************************************************
* Name       : Node* Node_Traverse(Node *pList,int position)
* Function   : Locate the node.
******************************************************************************/
Node* Node_Traverse(Node *pList,int position)
{
    	int cnt=0;

    	while(cnt != position)
    	{
        	cnt++;
        	pList=pList->next;
    	}
	/*Return node pointer*/
    	return pList;
}
/******************************************************************************
* Name       : int Node_Printf(Node *pList)
* Function   : Output structure array. 
******************************************************************************/
int Node_Printf(Node *pList)
{
	Node *p;
	int cnt=0,offset;
	
	p=pList;
	while(p->next !=NULL)
	{
	    cnt++;
	    printf("Node %d value: ",cnt);
	    for(offset=0;offset<MAX_NUM;offset++)
            printf("%d  ",p->data[offset]);
            printf("\n");
	    p=p->next;
	}
	return OK;
}
/******************************************************************************
* Name       : int Node_Insert(Node **pList,int position,int value)
* Function   : Insert a new node.
******************************************************************************/
int Node_Insert(Node **pList,int position,int value)
{
	Node *p1=NULL,*p2=NULL,*insert;
	int cnt=0;

	p2=*pList;
	while(p2->next !=NULL) 
	{
		cnt++;
		p2=p2->next;
	}
	p2=*pList;
	if((position > ++cnt)|| (position < HEAD_NODE)){
		printf("Insert node %d position error!\n",cnt);
		return ERROR;
	}
	insert = (struct node*)malloc(sizeof(Node));
	
	/*insert into the head*/
	if(position==HEAD_NODE) 
	{
		//insert->data = value;
		Array_Init(insert->data,MAX_NUM,value);
		insert->next = p2;
		*pList = insert;
	}
	/*insert into the tail*/
	else if(position == cnt) 
	{
		while(p2->next !=NULL){
			p2=p2->next;
		}
		insert->next = NULL;
		p2->next = insert;
		Array_Init(insert->data,MAX_NUM,value);
	}
	else    /*insert into the middle*/
	{
	    p2 = Node_Traverse(*pList,position-2);
		p1 = p2->next; 

		Array_Init(insert->data,MAX_NUM,value);
		insert->next = p1;
		p2->next = insert;
	}

	return OK;
}
/******************************************************************************
* Name       : int Node_Delete(Node **pList,int position)
* Function   : Delete a old node.
******************************************************************************/
int Node_Delete(Node **pList,int position)
{
	Node *p1=NULL,*p2=NULL,*insert;
	int cnt=0;

	p2=*pList;
	while(p2->next !=NULL) 
	{
		cnt++;
		p2=p2->next;
	}
	if((position > cnt)|| (position < HEAD_NODE)){
		printf("Delete node %d position error!\n",cnt);
		return 1;
	}
	/*Delete the head node*/
	if(1 == position)   
	{
	    p2=*pList;
		*pList = p2->next;
		free(p2);
	}else if(position==cnt)   /*Delete the tail node*/
	{
	    p2 = Node_Traverse(*pList,position-1);
		p1 = p2->next;
		p2->next = NULL;
		free(p1);

	}else   /*Delete the mid node*/
	{
		p2 = Node_Traverse(*pList,position-2);
		p1 = p2->next;
		p2->next = p1->next;
		free(p1);
	}
	printf("Delete node %d success\n",position);

	return OK;
}
/******************************************************************************
* Name       : int Write_Data(Node *pList,int position, int value,int offset)
* Function   : Write data into structure array.
******************************************************************************/
int Write_Data(Node *pList,int position, int value,int offset)
{
    	Node *p=NULL;

    	p = Node_Traverse(pList,position-1);
    	p->data[offset-1] = value;

    	return OK;
}
/******************************************************************************
* Name       : int main()
* Function   : Test function.
******************************************************************************/
int main()
{
	Node *head;
	int position, value=10,num=10,node=5;

	if(Creat_List(&head,num,0)==OK){
        for(position=1;position<=num;position++,value++)
            	Write_Data(head,position, value,3);
     	}
       if(Node_Insert(&head,node,5)==OK){
        	printf("Node %d insert success\n",node);
        }
   	 if(Node_Delete(&head,10)!=OK){
        printf("Delete node %d failed\n");
        }

	Node_Printf(head);      
	
	return OK;
}
