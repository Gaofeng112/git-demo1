#include<iostream>
using namespace std;
#define MaxSize 1024
typedef int ElemType;


//�������Ա�
typedef struct
{
	ElemType data[MaxSize];
	int length;
}Sqlist;


//����˳���
void CreateList(Sqlist *L)
{
	int n = 0, k = 0;
	cout << "�������������ݵĸ���\n";
	cin >> k;
	for (int i =0; i < k; i++)
	{
		printf("list[%d]=", i);
		cin >> n;
		L->data[i] = n;
	}
	L->length = k;
	printf("\n");
}

//������Ա�
void Displist(Sqlist* L)
{
	int i = 0;
	for (; i < L->length; i++)
	{
		printf("data[%d]=", i);
		printf("%d\n", L->data[i]);
	}
	printf("\n");
}

//��ʼ�����Ա�
void Initlist(Sqlist* L)      //������ܿ���ֱ����main����ʵ�֣�����Ҫ�ú�����д
{
	L = (Sqlist*)malloc(sizeof(Sqlist));  //���������Ա�Ŀռ�
	L->length = 0;
}

//�������Ա�
void Destroylist(Sqlist* L)
{
	free(L);                 //�ͷ����Ա�
}

//�ж����Ա��Ƿ�Ϊ�ձ�
bool Listempty(Sqlist* L)
{
	if (L->length == 0)
		cout << "���Ա�Ϊ��" << endl;
	else
		cout << "���Ա�Ϊ��" << endl;
	return (L->length);
}

//�����Ա�ĳ���
int Listlength(Sqlist* L)
{
	cout << "���Ա���Ϊ" << L->length << endl;
	return(L->length);
}

//��Ԫ��ֵ������
int Locatelist(Sqlist* L, ElemType e)
{
	int i = 0;
	while (i <= L->length && L->data[i] != e)
		i++;
	if (i >= L->length)
	{
		cout << "û�и�Ԫ������" << endl;
		return 0;
	}
	else
	{
		cout << "Ԫ�ص�λ���ڵ�" << i + 1 << "��" << endl;
		return i + 1;
	}
}

//��������Ԫ��
bool Listinsert(Sqlist* L)
{
	int i = 0, e = 0;
	cout << "������Ҫ����Ԫ�ص�λ�ã�\n";
	cin >> i;
	cout << "���������Ԫ�ص�ֵ��\n";
	cin >> e;
	int j = 0;
	if (i<1 || i>L->length + 1)          //���������i�ķ�Χ�������Ա�ķ�Χ
		return false;
	i--;
	for (j = L->length; j > i; j--)      //����i�����Ա�������
		L->data[j] = L->data[j - 1];
	L->data[i] = e;                      //��i��ֵ��ֵ
	L->length++;                         //����+1
	cout << "����ɹ�\n";
	return true;
}

//ɾ������Ԫ��
bool Listdelete(Sqlist* L)
{
	int i = 0;
	cout << "������Ҫɾ��Ԫ�ص�λ�ã�\n";
	cin >> i;
	int j = 0;
	if (i<1 || i>L->length)
	{
		cout << "�������\n";
		return false;
	}
	i--;
	for (j = i; j < L->length - 1; j++)
	{
		L->data[j] = L->data[j + 1];
	}
	L->length--;
	cout << "ɾ���ɹ�\n";
	return true;
	system("cls");
}

//�˵�
void Menu()
{
	cout << "************************************************************************" << endl;
	cout << "*********************  1��������Ա�����         ***********************" << endl;
	cout << "*********************  2���������Ա�             ***********************" << endl;
	cout << "*********************  3���ж����Ա��Ƿ�Ϊ�ձ�   ***********************" << endl;
	cout << "*********************  4�����Ա���             ***********************" << endl;
	cout << "*********************  5����Ԫ�ز������Ա�       ***********************" << endl;
	cout << "*********************  7����������Ԫ��           ***********************" << endl;
	cout << "*********************  8��ɾ������Ԫ��           ***********************" << endl;
	cout << "*********************  0���˳�����ϵͳ           ***********************" << endl;
	cout << "************************************************************************" << endl;
}

int main()
{
	Sqlist* L;
	L = (Sqlist*)malloc(sizeof(Sqlist));  //���������Ա�Ŀռ�
	Initlist(L);               //��ʼ����
	CreateList(L);             //�������Ա�
	while (true)
	{
		Menu();
		cout << "��������Ĳ�����\n";
		int select = 0;
		cin >> select;
		switch (select)
		{
		case 1:
			Displist(L);       //���
			break;
		case 2:
			Destroylist(L);    //����
			break;
		case 3:
			Listempty(L);      //�ж�
			break;
		case 4:
			Listlength(L);     //����
			break;
		case 5:                
			Listinsert(L);     //����          
			break;
		case 6:                
			Listdelete(L);     //ɾ��
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