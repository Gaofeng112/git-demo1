#include<iostream>
#include "栈的基本操作.h"
using namespace std;
typedef int ElemType;

//声明栈
typedef struct linknode
{
    ElemType data;         //数据域
    struct linknode* next; //指针域
    int length;            //长度
}LinkStNode;//指针域类型

//初始化栈
void Init(LinkStNode*& s)
{
    s = (LinkStNode*)malloc(sizeof(LinkStNode));
    s->next = NULL;
    s->length = 0;
}

//销毁栈
void DestroyStack(LinkStNode*& s)
{
    LinkStNode* pre = s, * p = s->next;//pre指向头节点，p指向首节点
    while (p!=NULL)                    //知道p为空
    {
        free(pre);                     //释放pre节点
        pre = p;                       //pre和p同步后移
        p = pre->next;
    }
    free(pre);                         //此时pre指向的尾节点，释放其空间
    cout << "成功销毁栈" << endl;
}

//判断是否为空栈
bool StackEmpty(LinkStNode* s)
{
    if (s->next == NULL)
    {
        cout << "栈为空" << endl;
        return true;
    }
    else
    { 
        cout << "栈不为空" << endl;
        return false;
    } 
}

//进栈
void Push(LinkStNode*& s)
{
    cout << "请输入你添加数据" << endl;
    ElemType e;
    cin >> e;
    LinkStNode* p;
    p = (LinkStNode*)malloc(sizeof(LinkStNode));  //新建结点p
    p->data = e;                                  //存放元素e
    p->next = s->next;                            //将p节点插入作为首节点
    s->next = p;
    s->length++;
}

//出栈
bool Pop(LinkStNode*& s)
{
    LinkStNode* p;
    if (s->next == NULL)    //判断为空的情况
    {
        cout << "栈为空,无需出栈" << endl;
        return false;
    }
    p = s->next;            //p指向首节点
    s->next = p->next;      //删除首节点
    s->length--;
    free(p);                //释放被删除节点的存储空间
    return true;
}

//取栈顶元素
bool GetTop(LinkStNode* s)
{
    ElemType e;
    if (s->next == NULL) //栈空情况
    {
        cout << "该栈为空，无顶元素" << endl;
        return false;
    }
    e = s->next->data;   //提取首节点
    cout << "首节点的值为" << e << endl;
    return true;
}

// 遍历栈
void Travers(LinkStNode *&s) {
    LinkStNode* m = s;
    int p = s->length;
    for(int i =0;i<p;i++)
    {
        cout << m->next->data << endl;
        m = m->next;
    }
}

//添加栈元素
void CreateNode(LinkStNode *&s)
{
    cout << "添加数据，输入-1为结束" << endl;
    ElemType e=0;
    while (true)
    {
        cin >> e;
        if (e == -1)
            break;
        LinkStNode* p;
        p = (LinkStNode*)malloc(sizeof(LinkStNode));  //新建结点p
        p->data = e;                                  //存放元素e
        p->next = s->next;                            //将p节点插入作为首节点
        s->next = p;
        s->length++;
    }
}

void Menu()
{
    cout << "************************************************************************" << endl;
    cout << "*********************  1、添加栈元素             ***********************" << endl;
    cout << "*********************  2、销毁栈                 ***********************" << endl;
    cout << "*********************  3、判断是否为空栈         ***********************" << endl;
    cout << "*********************  4、进栈一个元素           ***********************" << endl;
    cout << "*********************  5、出栈一个元素           ***********************" << endl;
    cout << "*********************  6、取栈顶元素             ***********************" << endl;
    cout << "*********************  7、遍历栈元素             ***********************" << endl;
    cout << "*********************  0、退出管理系统           ***********************" << endl;
    cout << "************************************************************************" << endl;
}

int main()
{
    LinkStNode * s;
    Init(s);    //初始化
    while (true)
    {
        Menu();
        cout << "请输入你的操作：\n";
        int select = 0;
        cin >> select;
        switch (select)
        {
        case 1:
            CreateNode(s);       //添加
            break;
        case 2:
            DestroyStack(s);    //销毁
            break;
        case 3:
            StackEmpty(s);      //判断
            break;
        case 4:
            Push(s);     //进栈
            break;
        case 5:
            Pop(s);     //出栈         
            break;
        case 6:
            GetTop(s);     //取顶
            break;
        case 7:
            Travers(s);     //遍历
            break;
        case 0:
            return 0;
            break;
        default:
            cout << "无效输入，请重新输入：\n";
            break;
        }
    }
    system("pause");
    return 0;
}