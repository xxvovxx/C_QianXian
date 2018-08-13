// 线性表的顺序表示和实现
// 算法看得懂，实现却很懵
// 实现了线性表顺序结构的创建，插入，删除，查找，合并及相关小点

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define List_init_size 100 // 线性表存储空间的初始分配量
#define List_increment 10  // 线性表存储空间的分配增量

typedef int ElemType;
typedef int Status;

typedef struct
{
    ElemType *elem; // 存储空间基址
    int length;     // 当前长度
    int listsize;   // 当前分配的存储容量（以sizeof（ElemType）为单位）
} SqList;

Status Memory_Judgment(SqList *L) // 存储空间判定
{
    ElemType *newbase;
    if (L->length >= L->listsize) // 若对当前存储空间已满则增加分配空间
    {
        newbase = (ElemType *)realloc(L->elem, (L->listsize + List_increment) * sizeof(ElemType)); // 增加分配新空间
        if (!newbase)
            return 0;                  // 检测成功与否
        L->elem = newbase;             // 新基址
        L->listsize += List_increment; // 增加存储容量
    }
    return 1;
}

Status InitList_Sq(SqList *L) // 构造一个空的线性表L
{
    L->elem = (ElemType *)malloc(List_init_size * sizeof(ElemType)); // 分配内存
    if (!L->elem)
        return 0;                 // 检测是否分配成功
    L->length = 0;                // 空表初始长度为0
    L->listsize = List_init_size; // 初始存储容量
    return 1;
}

Status ListInsert_Head_Sq(SqList *L, ElemType e) // 从表头插入
{
    ElemType  *q, *p;

    Memory_Judgment(L);  // 内存判定
    q = &L->elem[0]; // 令指针q指向要插入的位置，注意下标是从0开始以及取地址符
    for (p = &L->elem[L->length - 1]; p >= q; p--)
        *(p + 1) = *p; // 使要插入位置及其后所有的数据向后移一位
    *q = e;            // 将插入值赋给插入位置
    ++L->length;       // 表长加一
    return 1;
}

Status ListInsert_Tail_Sq(SqList *L, ElemType e) // 从表尾插入
{
    Memory_Judgment(L);     // 内存判定
    L->elem[L->length] = e; // 给末位元素赋值
    L->length += 1;         // 表长加一
    return 1;
}

Status ListInsert_Sq(SqList *L, int i, ElemType e) // 在顺序线性表中第i个元素之前插入新的元素e，既在下标为 i-1 的位置插入，数组下标从0开始
{
    ElemType *q, *p;

    if (i < 1 || i > L->length + 1)
        return 0;        // i值不合法，应大于等于1小于等于当前表中元素个数
    Memory_Judgment(L);  // 内存判定
    q = &L->elem[i - 1]; // 令指针q指向要插入的位置，注意下标是从0开始以及取地址符
    for (p = &L->elem[L->length - 1]; p >= q; p--)
        *(p + 1) = *p; // 使要插入位置及其后所有的数据向后移一位
    *q = e;            // 将插入值赋给插入位置
    ++L->length;       // 表长加一
    return 1;
}

void PrintList(SqList *L) //依次打印顺序表
{
    int i;

    printf("This sequence list is :\t");
    for (i = 0; i < L->length; i++) //依次输出表中元素，表长 length 既为元素个数，但元素位置下标从0开始！
    {
        printf("%d", L->elem[i]);
        printf("\t");
    }
    printf("\n");
}

Status ListDelete_Sq(SqList *L, int i)  //删除第i个元素并输出其值
{
    ElemType * p, * q, Delete_V;

    if(i < 1 || i > L->length) return 0;    //判断i合理性
    p = &L->elem[i-1];  //p指向i的地址，注意下标始于0
    Delete_V = *p; //将删除值赋予Delete_V
    q = &L->elem[L->length - 1];    //q指向末位元素
    for(++p; p <= q; ++p)   //将第i+1至末位的元素均向前移一位
        *(p-1) = *p;
    --L->length;    //表长减一
    printf("Deleted element is :\t%d\n",Delete_V);  //输出删除值
    return 1;
}

Status LocateElem_Sq(SqList *L, ElemType e) //在顺序表中寻找值为e的元素，若存在则返回其位序
{
    int i = 1;

    while (i <= L->length && L->elem[i - 1] != e) //比较判断是否满足
    {
        i++;
    }
    if (i <= L->length) //判断i是找到了还是说没找到而结束的
    {
        printf("True and i is %d\n", i); //找到了则返回位置
        return i;
    }
    else
    {
        printf("False and i is %d\n", i); //没找到则打印最后i的位置，应该都是length+1
        return 0;
    }
}

Status MergeList_Sq(SqList * La, SqList * Lb, SqList * Lc)  ////合并原升序的两表，使得合并后依旧升序 （传入三个顺序表的指针，在此函数中，其皆为指针形式）
{
    ElemType * pa, * pb, * pc, * pa_last, * pb_last, v;
    pa = La->elem;  //对应的指针指向对应的表头
    pb = Lb->elem;
    pc = Lc->elem;
    pa_last = &La->elem[La->length - 1];    //对应的指针指向对应的表尾
    pb_last = &Lb->elem[Lb->length - 1];

    while(pa <= pa_last && pb <= pb_last)   //循环比较大小并赋值压入Lc表
    {
        if(*pa <= *pb)
        {
            v = *pa;
            ListInsert_Tail_Sq(Lc, v);  //注意，此时的Lc为指针，不需要再加取地址符  &  ！！！
            pc++;
            pa++;
        }
        else
        {
            v = *pb;
            ListInsert_Tail_Sq(Lc, v);
            pc++;
            pb++;
        }
    }
    while(pa <= pa_last)    //将剩余元素依次加入Lc
    {
        v = *pa;
        ListInsert_Tail_Sq(Lc, v);
        pc++;
        pa++;
    }
    while(pb <= pb_last)    //将剩余元素依次加入Lc
    {
        v = *pb;
        ListInsert_Tail_Sq(Lc, v);
        pc++;
        pb++;
    }
}

int main(int argc, char const *argv[])
{
    // int Delet_V;    // 用于返回被删除的元素
    SqList L;    // 定义线性表L
    SqList Lb;
    SqList Lc;

    InitList_Sq(&L);    //初始化线性表，得到空表L
    ListInsert_Head_Sq(&L, 3);  //在表头插入数据
    ListInsert_Head_Sq(&L, 1);
    ListInsert_Tail_Sq(&L, 5);  //在表尾插入数据
    ListInsert_Tail_Sq(&L, 7);
    ListInsert_Tail_Sq(&L, 9);
    ListInsert_Sq(&L, 1, 99);    //在第1个元素之前插入元素9
    ListInsert_Sq(&L, 2, 66);    //在第2个元素之前插入元素9
    PrintList(&L);      //输出表中元素
    ListDelete_Sq(&L,2);   //删除第i个元素，并将其值返回给Delet_V
    ListDelete_Sq(&L,1);
    PrintList(&L);
    LocateElem_Sq(&L,3);    //在顺序表中寻找值为e的元素，若存在则返回其位序
    LocateElem_Sq(&L,7);

    InitList_Sq(&Lb);    //初始化线性表，得到空表L
    ListInsert_Head_Sq(&Lb, 4);  //在表头插入数据
    ListInsert_Head_Sq(&Lb, 2);
    ListInsert_Tail_Sq(&Lb, 6);  //在表尾插入数据
    ListInsert_Tail_Sq(&Lb, 8);
    ListInsert_Tail_Sq(&Lb, 10);
    PrintList(&Lb);

    InitList_Sq(&Lc);   //初始化表Lc
    MergeList_Sq(&L,&Lb,&Lc);   //合并原升序的两表，使得合并后依旧升序
    PrintList(&Lc);

    getchar();
    return 0;
}
