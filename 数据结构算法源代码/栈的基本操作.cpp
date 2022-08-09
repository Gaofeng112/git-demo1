#include<iostream>
#include "ջ�Ļ�������.h"
using namespace std;
typedef int ElemType;

//����ջ
typedef struct linknode
{
    ElemType data;         //������
    struct linknode* next; //ָ����
    int length;            //����
}LinkStNode;//ָ��������

//��ʼ��ջ
void Init(LinkStNode*& s)
{
    s = (LinkStNode*)malloc(sizeof(LinkStNode));
    s->next = NULL;
    s->length = 0;
}

//����ջ
void DestroyStack(LinkStNode*& s)
{
    LinkStNode* pre = s, * p = s->next;//preָ��ͷ�ڵ㣬pָ���׽ڵ�
    while (p!=NULL)                    //֪��pΪ��
    {
        free(pre);                     //�ͷ�pre�ڵ�
        pre = p;                       //pre��pͬ������
        p = pre->next;
    }
    free(pre);                         //��ʱpreָ���β�ڵ㣬�ͷ���ռ�
    cout << "�ɹ�����ջ" << endl;
}

//�ж��Ƿ�Ϊ��ջ
bool StackEmpty(LinkStNode* s)
{
    if (s->next == NULL)
    {
        cout << "ջΪ��" << endl;
        return true;
    }
    else
    { 
        cout << "ջ��Ϊ��" << endl;
        return false;
    } 
}

//��ջ
void Push(LinkStNode*& s)
{
    cout << "���������������" << endl;
    ElemType e;
    cin >> e;
    LinkStNode* p;
    p = (LinkStNode*)malloc(sizeof(LinkStNode));  //�½����p
    p->data = e;                                  //���Ԫ��e
    p->next = s->next;                            //��p�ڵ������Ϊ�׽ڵ�
    s->next = p;
    s->length++;
}

//��ջ
bool Pop(LinkStNode*& s)
{
    LinkStNode* p;
    if (s->next == NULL)    //�ж�Ϊ�յ����
    {
        cout << "ջΪ��,�����ջ" << endl;
        return false;
    }
    p = s->next;            //pָ���׽ڵ�
    s->next = p->next;      //ɾ���׽ڵ�
    s->length--;
    free(p);                //�ͷű�ɾ���ڵ�Ĵ洢�ռ�
    return true;
}

//ȡջ��Ԫ��
bool GetTop(LinkStNode* s)
{
    ElemType e;
    if (s->next == NULL) //ջ�����
    {
        cout << "��ջΪ�գ��޶�Ԫ��" << endl;
        return false;
    }
    e = s->next->data;   //��ȡ�׽ڵ�
    cout << "�׽ڵ��ֵΪ" << e << endl;
    return true;
}

// ����ջ
void Travers(LinkStNode *&s) {
    LinkStNode* m = s;
    int p = s->length;
    for(int i =0;i<p;i++)
    {
        cout << m->next->data << endl;
        m = m->next;
    }
}

//���ջԪ��
void CreateNode(LinkStNode *&s)
{
    cout << "������ݣ�����-1Ϊ����" << endl;
    ElemType e=0;
    while (true)
    {
        cin >> e;
        if (e == -1)
            break;
        LinkStNode* p;
        p = (LinkStNode*)malloc(sizeof(LinkStNode));  //�½����p
        p->data = e;                                  //���Ԫ��e
        p->next = s->next;                            //��p�ڵ������Ϊ�׽ڵ�
        s->next = p;
        s->length++;
    }
}

void Menu()
{
    cout << "************************************************************************" << endl;
    cout << "*********************  1�����ջԪ��             ***********************" << endl;
    cout << "*********************  2������ջ                 ***********************" << endl;
    cout << "*********************  3���ж��Ƿ�Ϊ��ջ         ***********************" << endl;
    cout << "*********************  4����ջһ��Ԫ��           ***********************" << endl;
    cout << "*********************  5����ջһ��Ԫ��           ***********************" << endl;
    cout << "*********************  6��ȡջ��Ԫ��             ***********************" << endl;
    cout << "*********************  7������ջԪ��             ***********************" << endl;
    cout << "*********************  0���˳�����ϵͳ           ***********************" << endl;
    cout << "************************************************************************" << endl;
}

int main()
{
    LinkStNode * s;
    Init(s);    //��ʼ��
    while (true)
    {
        Menu();
        cout << "��������Ĳ�����\n";
        int select = 0;
        cin >> select;
        switch (select)
        {
        case 1:
            CreateNode(s);       //���
            break;
        case 2:
            DestroyStack(s);    //����
            break;
        case 3:
            StackEmpty(s);      //�ж�
            break;
        case 4:
            Push(s);     //��ջ
            break;
        case 5:
            Pop(s);     //��ջ         
            break;
        case 6:
            GetTop(s);     //ȡ��
            break;
        case 7:
            Travers(s);     //����
            break;
        case 0:
            return 0;
            break;
        default:
            cout << "��Ч���룬���������룺\n";
            break;
        }
    }
    system("pause");
    return 0;
}