#include<stdio.h>
#include <stdlib.h>

//C����ʵ�ֵ�����Ĵ����Լ���������
//����֪ʶ���кöడ��ʱ���ȷ������

typedef struct SingleList    //�ṹ�嶨��
{
	int data;
	struct SingleList* next;
}LIST,*LPLIST;   
//LIST  �൱��  struct SingleList 
//*LPLIST  �൱��  struct SingleList*

LPLIST CreateList()   //����ͷ�ڵ㣨�������ʼ����
{
	LPLIST List = (LPLIST)malloc(sizeof(LIST));   //ͷ�ڵ������ڴ�
	List->next = NULL;       //ͷ�ڵ�ĺ�̽ڵ��ÿ�
	return List;      //���ؽ���ͷ�ڵ�Ŀ�����
}

void printlist(LPLIST list)   //��ӡ����
{
	printf("listHead->");       
	LPLIST p = list;           //����һ���α�ָ��
	while (p->next)
	{
		p = p->next;
		printf("%d->", p->data);
	}
	printf("NULL");
}

LPLIST CreateNode(int data)//�����ڵ�
{
	LPLIST Node = (LPLIST)malloc(sizeof(LIST));//�ڵ������ڴ�
	Node->data = data;//�ڵ�������ֵ
	Node->next = NULL;//�ڵ���ָ���ÿ�
	return Node;//���ؽڵ�
}

void InsertListByHead(LPLIST list, int data)//�ڽ�����ͷ�ڵ�������
{
	LPLIST newNode = CreateNode(data);//�����ڵ�
	newNode->next = list->next;//�½ڵ�ĺ��ָ��ͷ�ڵ�ĺ��
	list->next = newNode;//ͷ�ڵ�ĺ��ָ���½ڵ�
}

void InsertListByTail(LPLIST list, int data)//������ĩβ����
{
	LPLIST pTail = list;//����һ��ĩβָ��
	while (pTail->next)//ͨ��ѭ����λ����ĩλ
		pTail = pTail->next;
	LPLIST newNode = CreateNode(data);//�����ڵ�
	newNode->next = pTail->next;//�½ڵ�ĺ��ָ��ĩλpTail�ڵ�ĺ��
	pTail->next = newNode;//ĩλpTail�ڵ�ĺ��ָ���½ڵ�
}

void InsertListByNode(LPLIST list, int n, int data)//��ָ���ڵ㣨ͨ���ڵ�������λ��λ�ò���
{
	//if (list->next = NULL)//��ʹ�ü�����λӦ�þ�û������  //��ȫ����Ҫ�ⲽ���飬ֱ����֤pData->next->data���ɱ���ͷ�ڵ����Чdata��
	//{
		//printf("����Ϊ�գ���ʹ���������뷽����");
		//return(0);
	//}	
	LPLIST pData = list;//����һ���α�ָ��
	while (pData->next->data != n)//ͨ��ѭ����λ����ָ���ڵ㣨ͨ���ڵ�������λ��λ�ã���֤pData->next->data����ͷ�ڵ����Чdata��
		pData = pData->next;
	LPLIST newNode = CreateNode(data);//�����ڵ�
	newNode->next = pData->next;//�½ڵ�ĺ��ָ��ĩλpData�ڵ�ĺ��
	pData->next = newNode;//ĩλpData�ڵ�ĺ��ָ���½ڵ�
}

int main()
{
	LPLIST list = CreateList();     //��������
	printf("\n======CreateList======\n");
	printlist(list);   //��ӡ����
	//CreateNode(100);   //�����ڵ�
	InsertListByHead(list, 1);    //����ͷ�ڵ�������ڵ�
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
	InsertListByNode(list, 5, 8);//��8���뵽ԭ������5��λ��
	InsertListByNode(list, 7, 998);//��998���뵽ԭ������7��λ��
	printf("\n======InsertListByNode======\n");
	printlist(list);
	//���ϴ������ݲ�������ټ�һ��ѭ���ṹ����

	return(0);
}


