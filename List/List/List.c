#include<stdio.h>
#include <stdlib.h>

//C语言实现单链表的创建以及插入数据
//链表知识还有好多啊，时间的确不多了

typedef struct SingleList    //结构体定义
{
	int data;
	struct SingleList* next;
}LIST,*LPLIST;   
//LIST  相当于  struct SingleList 
//*LPLIST  相当于  struct SingleList*

LPLIST CreateList()   //创建头节点（空链表初始化）
{
	LPLIST List = (LPLIST)malloc(sizeof(LIST));   //头节点申请内存
	List->next = NULL;       //头节点的后继节点置空
	return List;      //返回仅有头节点的空链表
}

void printlist(LPLIST list)   //打印链表
{
	printf("listHead->");       
	LPLIST p = list;           //定义一个游标指针
	while (p->next)
	{
		p = p->next;
		printf("%d->", p->data);
	}
	printf("NULL");
}

LPLIST CreateNode(int data)//创建节点
{
	LPLIST Node = (LPLIST)malloc(sizeof(LIST));//节点申请内存
	Node->data = data;//节点数据域赋值
	Node->next = NULL;//节点后继指针置空
	return Node;//返回节点
}

void InsertListByHead(LPLIST list, int data)//在紧跟着头节点后面插入
{
	LPLIST newNode = CreateNode(data);//创建节点
	newNode->next = list->next;//新节点的后继指向头节点的后继
	list->next = newNode;//头节点的后继指向新节点
}

void InsertListByTail(LPLIST list, int data)//在链表末尾插入
{
	LPLIST pTail = list;//定义一个末尾指针
	while (pTail->next)//通过循环定位链表末位
		pTail = pTail->next;
	LPLIST newNode = CreateNode(data);//创建节点
	newNode->next = pTail->next;//新节点的后继指向末位pTail节点的后继
	pTail->next = newNode;//末位pTail节点的后继指向新节点
}

void InsertListByNode(LPLIST list, int n, int data)//在指定节点（通过节点数据域定位）位置插入
{
	//if (list->next = NULL)//若使用计数定位应该就没问题了  //完全不需要这步检验，直接验证pData->next->data即可避免头节点的无效data域
	//{
		//printf("链表为空，请使用其他插入方法！");
		//return(0);
	//}	
	LPLIST pData = list;//定义一个游标指针
	while (pData->next->data != n)//通过循环定位链表指定节点（通过节点数据域定位）位置，验证pData->next->data避免头节点的无效data域
		pData = pData->next;
	LPLIST newNode = CreateNode(data);//创建节点
	newNode->next = pData->next;//新节点的后继指向末位pData节点的后继
	pData->next = newNode;//末位pData节点的后继指向新节点
}

int main()
{
	LPLIST list = CreateList();     //定义链表
	printf("\n======CreateList======\n");
	printlist(list);   //打印链表
	//CreateNode(100);   //创建节点
	InsertListByHead(list, 1);    //仅在头节点后面插入节点
	InsertListByHead(list, 2);
	InsertListByHead(list, 3);
	InsertListByHead(list, 4);
	InsertListByHead(list, 5);
	printf("\n======InsertListByHead======\n");
	printlist(list);
	InsertListByTail(list, 6);
	InsertListByTail(list, 7);
	InsertListByTail(list, 8);
	InsertListByTail(list, 9);
	InsertListByTail(list, 10);
	printf("\n======InsertListByTail======\n");
	printlist(list);
	InsertListByNode(list, 5, 8);//将8插入到原来表中5的位置
	InsertListByNode(list, 7, 998);//将998插入到原来表中7的位置
	printf("\n======InsertListByNode======\n");
	printlist(list);
	//不断大量数据插入仅需再加一个循环结构即可

	return(0);
}


