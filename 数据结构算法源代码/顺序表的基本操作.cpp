#include<iostream>
using namespace std;
#define MaxSize 1024
typedef int ElemType;


//声明线性表
typedef struct
{
	ElemType data[MaxSize];
	int length;
}Sqlist;


//建立顺序表
void CreateList(Sqlist *L)
{
	int n = 0, k = 0;
	cout << "请输入链表数据的个数\n";
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

//输出线性表
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

//初始化线性表
void Initlist(Sqlist* L)      //这个功能可以直接在main函数实现，不与要用函数来写
{
	L = (Sqlist*)malloc(sizeof(Sqlist));  //分配存放线性表的空间
	L->length = 0;
}

//销毁线性表
void Destroylist(Sqlist* L)
{
	free(L);                 //释放线性表
}

//判断线性表是否为空表
bool Listempty(Sqlist* L)
{
	if (L->length == 0)
		cout << "线性表为空" << endl;
	else
		cout << "线性表不为空" << endl;
	return (L->length);
}

//求线性表的长度
int Listlength(Sqlist* L)
{
	cout << "线性表长度为" << L->length << endl;
	return(L->length);
}

//按元素值来查找
int Locatelist(Sqlist* L, ElemType e)
{
	int i = 0;
	while (i <= L->length && L->data[i] != e)
		i++;
	if (i >= L->length)
	{
		cout << "没有该元素数据" << endl;
		return 0;
	}
	else
	{
		cout << "元素的位置在第" << i + 1 << "个" << endl;
		return i + 1;
	}
}

//插入数据元素
bool Listinsert(Sqlist* L)
{
	int i = 0, e = 0;
	cout << "输入你要插入元素的位置：\n";
	cin >> i;
	cout << "请输入插入元素的值：\n";
	cin >> e;
	int j = 0;
	if (i<1 || i>L->length + 1)          //插入的数据i的范围超过线性表的范围
		return false;
	i--;
	for (j = L->length; j > i; j--)      //大于i的线性表的向后移
		L->data[j] = L->data[j - 1];
	L->data[i] = e;                      //第i个值赋值
	L->length++;                         //长度+1
	cout << "插入成功\n";
	return true;
}

//删除数据元素
bool Listdelete(Sqlist* L)
{
	int i = 0;
	cout << "输入你要删除元素的位置：\n";
	cin >> i;
	int j = 0;
	if (i<1 || i>L->length)
	{
		cout << "输出错误\n";
		return false;
	}
	i--;
	for (j = i; j < L->length - 1; j++)
	{
		L->data[j] = L->data[j + 1];
	}
	L->length--;
	cout << "删除成功\n";
	return true;
	system("cls");
}

//菜单
void Menu()
{
	cout << "************************************************************************" << endl;
	cout << "*********************  1、输出线性表数据         ***********************" << endl;
	cout << "*********************  2、销毁线性表             ***********************" << endl;
	cout << "*********************  3、判断线性表是否为空表   ***********************" << endl;
	cout << "*********************  4、线性表长度             ***********************" << endl;
	cout << "*********************  5、按元素查找线性表       ***********************" << endl;
	cout << "*********************  7、插入数据元素           ***********************" << endl;
	cout << "*********************  8、删除数据元素           ***********************" << endl;
	cout << "*********************  0、退出管理系统           ***********************" << endl;
	cout << "************************************************************************" << endl;
}

int main()
{
	Sqlist* L;
	L = (Sqlist*)malloc(sizeof(Sqlist));  //分配存放线性表的空间
	Initlist(L);               //初始化表
	CreateList(L);             //建立线性表
	while (true)
	{
		Menu();
		cout << "请输入你的操作：\n";
		int select = 0;
		cin >> select;
		switch (select)
		{
		case 1:
			Displist(L);       //输出
			break;
		case 2:
			Destroylist(L);    //销毁
			break;
		case 3:
			Listempty(L);      //判断
			break;
		case 4:
			Listlength(L);     //长度
			break;
		case 5:                
			Listinsert(L);     //插入          
			break;
		case 6:                
			Listdelete(L);     //删除
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