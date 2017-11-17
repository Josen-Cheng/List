#include <stdio.h>
#include <malloc.h>

/******节点结构体******/
struct node
{
    int data;
    struct node *next;
}Node, *sList;

/*****实现单向链*******/
//功能：创建链表
//参数：**pList:指向节点指针的指针. size:链表的大小，mode：0:头插法 1：尾插法
//创建方式：头插法
//返回：0成功 1：失败
int Creat_List(struct node **pList,int size, char mode)
{
    struct node *p=NULL;
    sList = NULL;
	sList=(struct node*)malloc(sizeof(Node));
	if(sList==NULL)
	{
		printf("List Creat failed!\n");
	}

	sList->data=0;
	sList->next=NULL;
	*pList=sList;

	if(0==mode)  //头插法
    {
        while(size--)
        {
            sList=(struct node*)malloc(sizeof(Node));
            if(sList==NULL)
            {
                printf("List Creat failed!\n");
            }
            sList->data=0;
            sList->next=*pList;
            *pList=sList;

        }
    }
    else if(1==mode)  //尾插法
    {
        p=*pList;
        while(size--)
        {
            sList=(struct node*)malloc(sizeof(Node));
            p->next = sList;
            sList->data = 0;
            sList->next = NULL;
            p=sList;
        }
    }else
    {
        printf("mode is 0 or 1\n");
        return 1;
    }

    printf("List Creat success!\n");
	return 0;
}
//函数功能：节点的遍历
//入口参数：链表头指针
//返回值：指定位置的指针
struct node* node_iterate(struct node *pList,int position)
{
    int cnt=0;

    while(cnt != position)
    {
        cnt++;
        pList=pList->next;
    }

    return pList;
}
//函数功能：节点的遍历
//入口参数：链表头指针
//返回值：节点数
int node_scan(struct node *pList)
{
	struct node *p;
	int cnt=0;
	p=pList;

	while(p->next !=NULL)
	{
		cnt++;
		printf("节点%d:值：%d\n",cnt,p->data);
		p=p->next;
	}
	return cnt;
}
//功能：插入一个节点
//参数：*pList头节点 position：插入的节点位置
//返回值 0成功 1：失败
int node_insert(struct node **pList,int position,int value)
{
	struct node *p1=NULL,*p2=NULL,*insert;
	int cnt=0;

	p2=*pList;
	while(p2->next !=NULL) //遍历节点
	{
		cnt++;
		p2=p2->next;
	}
	p2=*pList;
	if((position > ++cnt)|| (position < 1)){
		printf("Insert node %d position error!\n",cnt);
		return 1;
	}
	insert = (struct node*)malloc(sizeof(Node));

	if(position==1)   //插入到头节点
	{
		insert->data = value;
		insert->next = p2;
		*pList = insert;
	}
	else if(position == cnt) //插入尾节点,前面cnt自增1
	{
		while(p2->next !=NULL){
			p2=p2->next;
		}
		insert->next = NULL;
		p2->next = insert;
		p2->data = value;
	}
	else  //插入中间节点
	{
	    p2 = node_iterate(*pList,position-2);
		p1 = p2->next; //

		insert->data = value;
		insert->next = p1;
		p2->next = insert;
	}

	return 0;
}
//功能：插入一个节点
//参数：*pList头节点 position：插入的节点位置
//返回值 0成功 1：失败
int node_delete(struct node **pList,int position)
{
	struct node *p1=NULL,*p2=NULL,*insert;
	int cnt=0;

	p2=*pList;
	while(p2->next !=NULL) //遍历节点
	{
		cnt++;
		p2=p2->next;
	}
	if((position > cnt)|| (position < 1)){
		printf("Delete node %d position error!\n",cnt);
		return 1;
	}

	if(1 == position)     //删除头节点
	{
	    p2=*pList;
		*pList = p2->next;
		free(p2);
	}else if(position==cnt) //删除尾节点
	{
	    p2 = node_iterate(*pList,position-1);
		p1 = p2->next;
		p2->next = NULL;
		free(p1);

	}else  //删除中间节点
	{
		p2 = node_iterate(*pList,position-2);
		p1 = p2->next;
		p2->next = p1->next;
		free(p1);
	}
	printf("Delete node %d success\n",position);

	return 0;
}
//函数功能：向节点写入数据
//入口参数：*pList:链表指针，position：节点位置， value:写入值
//返回值0：成功，其它：失败
int write_data(struct node *pList,int position, int value)
{
    struct node *p=NULL;

    p = node_iterate(pList,position-1);
    p->data = value;

    return 0;
}
int main()
{
	struct node *head;
	int position, value=10,num=10,node=5;

	if(Creat_List(&head,num,1)==0){
        for(position=1;position<=num;position++,value++)
            write_data(head,position, value);
	}
    if(node_insert(&head,4,100)==0)
    {
        printf("插入节点%d成功\n",node);
    }
    if(node_delete(&head,10)==0)
    {
        printf("删除节点10成功\n");
    }

	node_scan(head);


	return 0;
}
