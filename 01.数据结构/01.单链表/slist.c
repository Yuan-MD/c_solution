#include <slist.h>

//创建节点
Node* CreatNode(const int data)
{
	//给每个节点分配和结构体一样的空间大小
	Node* p = (Node*)malloc(sizeof(Node));
	assert(NULL != p);
	//清理数据
	memset(p, 0, sizeof(Node));
	//初始化第一个节点
	p->data = data;
	//将节点的后继指针设置为NULL
	p->next = NULL;
	return p;
}

//销毁节点
void destroyNode(Node* node)
{
    free((Node*)node);
}

//带头节点的单链表
void sInit(Slist* list)
{
    list->head = CreatNode(INI_MIN);
}

//按顺序插入
bool sInsert(Slist* list, const int data)
{
    Node* ptem = list->head;
    Node* current;
    Node* node;
    node = CreatNode(data);
    if (ptem->data > data)
    {
        list->head = node;
        node->next = ptem;
    }
    else {
        while ((current = ptem->next) != NULL && current->data < data)
            ptem = ptem->next;
        if (NULL != current && current->data >= data)
            node->next = current;
        ptem->next = node;
    }
    return true;
}

//移除节点
bool sRemove(Slist* list, const int key)
{
    Node* previous = list->head;
    Node* current;
    //找到删除节点
    while ((current = previous->next) != NULL && current->data != key)
        previous = previous->next;
    if (NULL == current)
        return false;
    previous->next = current->next;
    free(current);
    return true;
}

//修改,先删后插入，因为这是有序链表
bool sModify(Slist* list, const int key, const int data)
{
    if (sRemove(list, key))
        sInsert(list, data);
    else
        return false;
    return true;
}

//找到返回关键字的节点，否则返回null指针
Node* sFind(Slist* list, const int key)
{
    Node* current = list->head;
    while ((current = current->next) != NULL && current->data != key)
        if (current->data > key)
            return NULL;
    return current;
}

//遍历
void sTreaverse(Slist* slist, void (*func) (Node* p))
{
    Node* current = slist->head;
    func(current);
    while ((current = current->next) != NULL)
        func(current);
}

//销毁链表
void sDestrory(Slist* list)
{
    sTreaverse(list, destroyNode);
    free(list->head);
}

//print 打印节点数据
void printData(Node* p)
{
    printf("%d ", p->data);
}

void slist_sample(void)
{
    printf("单链表测试:\n");
    Slist nlist;
    int num;
    sInit(&nlist); //初始化
    for (num = 10; num > 0; num--)
    {
        sInsert(&nlist, num);  //插入
    }
    sTreaverse(&nlist, printData);//遍历打印data
    sRemove(&nlist, 3); //移除
    printf("\n");
    sTreaverse(&nlist, printData);
    sModify(&nlist, 8, 40);//修改
    printf("\n");
    sTreaverse(&nlist, printData);
}
