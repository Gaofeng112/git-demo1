#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<iostream>
#include "sql.h"
#include "sqltypes.h"
#include "sqlext.h"
#include<cstring>

using namespace std;

RETCODE retcode;  //结果返回集
SQLHDBC hdbc;     //定义连接句柄

void SQL(char*);  //执行SQL语句子程序
void ShowMainMenu();   //显示主菜单

int  DepartManage();   
void DepartMenu();      
void DepartPrint();     
void SelectDepart();     
void AddDepart();         
void ChangeDepart();     

int DoctorManage();  
void DoctorMenu();    
void DoctorPrint();      
void SelectDoctor();    
void AddDoctor();       
void DeleteDoctor();   
void ChangeDoctor();   

int PatientManage();  
void PatientMenu();
void PatientPrint();
void SelectPatient();
void AddPatient();
void ChangePatient();

int RoomManage();  
void RoomMenu();
void RoomPrint();
void SelectRoom();
void AddRoom();     
void ChangeRoom(); 


int ElseManage();
void ElseMenu();
void DoctorClassify();
void WritePatient();
void LeaveHospital();

int DepartManage1();    
int DoctorManage1();
int PatientManage1();
int RoomManage1(); 
int ElseManagel();

int main()
{
	char str[200], pstr[200];
	int dbchoice;
	int opchoice;
	SQLHANDLE henv;  
	unsigned char SY[] = "医院信息管理系统";   
	unsigned char db2[] = "sa"; 
	unsigned char pass[] = "xp772233";  
	retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
		retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);  
	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
		retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
		retcode = SQLConnect(hdbc, SY, SQL_NTS, db2, SQL_NTS, pass, SQL_NTS);  
	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
		while (1)
		{
			ShowMainMenu();    
			cout << "请输入你要查询板块的编号：";
			int select = 0;
			cin >> select;     
			switch (select)
			{
			case 1:
				DepartManage();
				break;
			case 2:
				DoctorManage();
				break;
			case 3:
				PatientManage();
				break;
			case 4:
				RoomManage();
				break;
			case 5:
				ElseManage();
				break;
			case 0:
				cout << "—————————————————————！！！欢迎下次使用！！！————————————————————————" << endl;
				system("pause");
				return 0;
				break;
			default:
				break;
			}
		}

	}
	SQLFreeConnect(hdbc);  
	SQLFreeEnv(henv);  

	system("pause");
	return 0;
}

//主菜单
void ShowMainMenu()//主菜单
{
	cout << "*****************************************************************" << endl;
	cout << "*********************  1、科室信息管理    ***********************" << endl;
	cout << "*********************  2、医生信息管理    ***********************" << endl;
	cout << "*********************  3、病人信息管理    ***********************" << endl;
	cout << "*********************  4、病房信息管理    ***********************" << endl;
	cout << "*********************  5、其他服务管理    ***********************" << endl;
	cout << "*********************  0、退出管理系统    ***********************" << endl;
	cout << "*****************************************************************" << endl;
}
int DepartManage()
{
	while (1)
	{
		DepartMenu(); 
		cout << "请输入你要查询板块的编号：";
		int select = 0;
		cin >> select;     
		switch (select)
		{
		case 1:
			DepartPrint();
			break;
		case 2:
			SelectDepart();
			break;
		case 3:
			AddDepart();
			break;
		case 4:
			ChangeDepart();
			break;
		case 0:
			return 0;
			break;
		default:
			cout << "无效输入，请重新输入：\n";
			break;
		}
	}
}


void DepartMenu()
{
	cout << "*****************************************************" << endl;
	cout << "***************  1、浏览科室信息    *****************" << endl;
	cout << "***************  2、查询科室信息    *****************" << endl;
	cout << "***************  3、增加科室信息    *****************" << endl;
	cout << "***************  4、修改科室信息    *****************" << endl;
	cout << "***************  0、退出科室管理    *****************" << endl;
	cout << "*****************************************************" << endl;
}
void DepartPrint()
{
	string str1 = "use 医院信息管理系统";
	string str2 = "select * from 科室";
	SQLHSTMT hstmt;  
	int i = 1;

	char L1[10], L2[10], L3[20], L4[20], L5[10];
	long lenOut1=0, lenOut2=0, lenOut3=0, lenOut4=0, lenOut5=0;

	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	if (retcode == SQL_SUCCESS)
	{
		retcode = SQLExecDirect(hstmt, (SQLCHAR*)str1.c_str(), SQL_NTS);
		retcode = SQLExecDirect(hstmt, (SQLCHAR*)str2.c_str(), SQL_NTS);
		printf("编号  科室编号  科室名   科地址         联系电话     科室主任编号\n");
		while (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
		{
			retcode = SQLBindCol(hstmt, 1, SQL_C_CHAR, L1, sizeof(L1), &lenOut1);
			retcode = SQLBindCol(hstmt, 2, SQL_C_CHAR, L2, sizeof(L2), &lenOut2);
			retcode = SQLBindCol(hstmt, 3, SQL_C_CHAR, L3, sizeof(L3), &lenOut3);
			retcode = SQLBindCol(hstmt, 4, SQL_C_CHAR, L4, sizeof(L4), &lenOut4);
			retcode = SQLBindCol(hstmt, 5, SQL_C_CHAR, L5, sizeof(L5), &lenOut5);
			retcode = SQLFetch(hstmt);
			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
				printf("%d\t%s\t%s\t%s\t%s\t%s\n", i, L1, L2, L3, L4, L5);
			i++;
		}
	}
}
void SelectDepart()
{
	string str1 = "use 医院信息管理系统";
	string str2 = "SELECT * FROM 科室 WHERE 科室名 = '";

	cout << "请输入要查询的科室名:" ;
	string Sno;
	cin >> Sno;
	string str3 = str2 + Sno + "'";
	SQLHSTMT hstmt;  
	int i = 1;
	char L1[10], L2[10], L3[20], L4[20], L5[10];
	long lenOut1 = 0, lenOut2 = 0, lenOut3 = 0, lenOut4 = 0, lenOut5 = 0;
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	if (retcode == SQL_SUCCESS)
	{
		retcode = SQLExecDirect(hstmt, (SQLCHAR*)str1.c_str(), SQL_NTS);
		retcode = SQLExecDirect(hstmt, (SQLCHAR*)str3.c_str(), SQL_NTS);
		printf("编号  科室编号  科室名   科地址         联系电话     科室主任编号\n");
		while (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
		{
			retcode = SQLBindCol(hstmt, 1, SQL_C_CHAR, L1, sizeof(L1), &lenOut1);
			retcode = SQLBindCol(hstmt, 2, SQL_C_CHAR, L2, sizeof(L2), &lenOut2);
			retcode = SQLBindCol(hstmt, 3, SQL_C_CHAR, L3, sizeof(L3), &lenOut3);
			retcode = SQLBindCol(hstmt, 4, SQL_C_CHAR, L4, sizeof(L4), &lenOut4);
			retcode = SQLBindCol(hstmt, 5, SQL_C_CHAR, L5, sizeof(L5), &lenOut5);
			retcode = SQLFetch(hstmt);
			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
				printf("%d\t%s\t%s\t%s\t%s\t%s\n", i, L1, L2, L3, L4, L5);
			i++;
		}
	}

}
void AddDepart()
{
	SQLHSTMT hstmt;
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	string str1 = "use 医院信息管理系统";
	string str2 = "insert into 科室 values ('";
	string l1, l2, l3, l4, l5;
	cout << "请输入新的科室编号：" << endl;
	cin >> l1;
	cout << "请输入新的科室名：" << endl;
	cin >> l2;
	cout << "请输入新的科地址：" << endl;
	cin >> l3;
	cout << "请输入新的联系电话：" << endl;
	cin >> l4;
	cout << "请输入新的科室主任编号：" << endl;
	cin >> l5;
	string str3 = str2 + l1 + "','" + l2 + "','" + l3 + "','" + l4 + "','" + l5 + "'" + ")";
	retcode = SQLExecDirect(hstmt, (SQLCHAR*)str1.c_str(), SQL_NTS);
	retcode = SQLExecDirect(hstmt, (SQLCHAR*)str3.c_str(), SQL_NTS);
	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
		cout << "科室增加成功！" << endl;
	}
	else {
		cout << "科室增加失败！" << endl;
	}

	SQLFreeStmt(hstmt, SQL_DROP);
	system("pause");
	system("cls");
}
void ChangeDepart()
{
	SQLHSTMT hstmt;
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);//申请句柄
	string str1 = "use 医院信息管理系统";
	string Array[] = { "科室编号","科室名","科地址","联系电话","科室主任编号"};

	while (1)
	{
		cout << "  **********************请输入要修改的属性：*******************  " << endl;
		cout << "      0，科室编号、      1，科室名、         2，科地址、         " << endl;
		cout << "      3，联系电话、      4，科室主任编号、   5，退出修改         " << endl;
		cout << "  *************************************************************  " << endl;
		int select = 0;
		cin >> select;
		if (select == 5)
		{
			cout << "已退出修改菜单\n";
			break;
		}
		else if (select >= 0 || select <= 4)
		{
			cout << "请输入原先的科室名：\n";
			string str2; cin >> str2;
			cout << "请输入新的" << Array[select] << "：\n";
			string str4; cin >> str4;
			string str6 = "update 科室 set " + Array[select] + " = '" + str4 + "'" + "where 科室名='" + str2 + "'";
			retcode = SQLExecDirect(hstmt, (SQLCHAR*)str1.c_str(), SQL_NTS);
			retcode = SQLExecDirect(hstmt, (SQLCHAR*)str6.c_str(), SQL_NTS);
			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
				cout << Array[select] << "修改成功！\n" << endl;
			}
			else {
				cout << Array[select] << "修改成功！\n" << endl;
			}
			cout << "是否还要继续修改 1-继续修改，0-退出修改\n";
			cin >> select;
			if (select == 0)break;
		}
		else
		{
			cout << "输入无效，请重新输入" << endl;
		}
	}
	SQLFreeStmt(hstmt, SQL_DROP);
	system("pause");
	system("cls");
}
int PatientManage()
{
	while (1)
	{
		PatientMenu();
		cout << "请输入你要查询板块的编号：";
		int select = 0;
		cin >> select;     //用户选择
		switch (select)
		{
		case 1:
			PatientPrint();
			break;
		case 2:
			SelectPatient();
			break;
		case 3:
			AddPatient();
			break;
		case 4:
			ChangePatient();
			break;
		case 0:
			return 0;
			break;
		default:
			cout << "无效输入，请重新输入：\n";
			break;
		}
	}
}


void PatientMenu()
{
	cout << "*****************************************************" << endl;
	cout << "***************  1、浏览病人信息    *****************" << endl;
	cout << "***************  2、查询病人信息    *****************" << endl;
	cout << "***************  3、增加病人信息    *****************" << endl;
	cout << "***************  4、修改病人信息    *****************" << endl;
	cout << "***************  0、退出病人管理    *****************" << endl;
	cout << "*****************************************************" << endl;
}
void PatientPrint()
{
	string str1 = "use 医院信息管理系统";
	string str2 = "select * from 病人";
	SQLHSTMT hstmt;
	int i = 1;
	char L1[20], L2[10], L3[10], L4[10], L5[10], L6[20], L7[200], L8[20], L9[10];
	long lenOut1 = 0, lenOut2 = 0, lenOut3 = 0, lenOut4 = 0, lenOut5 = 0, lenOut6 = 0, lenOut7 = 0,lenOut8 = 0, lenOut9 = 0;
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	if (retcode == SQL_SUCCESS)
	{
		retcode = SQLExecDirect(hstmt, (SQLCHAR*)str1.c_str(), SQL_NTS);
		retcode = SQLExecDirect(hstmt, (SQLCHAR*)str2.c_str(), SQL_NTS);
		printf("编号     身份证号     工作证号   病房号     姓名     性别    年龄      病例信息      入院日期     出院日期\n");
		while (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
		{
			retcode = SQLBindCol(hstmt, 1, SQL_C_CHAR, L1, sizeof(L1), &lenOut1);
			retcode = SQLBindCol(hstmt, 2, SQL_C_CHAR, L2, sizeof(L2), &lenOut2);
			retcode = SQLBindCol(hstmt, 3, SQL_C_CHAR, L3, sizeof(L3), &lenOut3);
			retcode = SQLBindCol(hstmt, 4, SQL_C_CHAR, L4, sizeof(L4), &lenOut4);
			retcode = SQLBindCol(hstmt, 5, SQL_C_CHAR, L5, sizeof(L5), &lenOut5);
			retcode = SQLBindCol(hstmt, 6, SQL_C_CHAR, L6, sizeof(L6), &lenOut6);
			retcode = SQLBindCol(hstmt, 7, SQL_C_CHAR, L7, sizeof(L7), &lenOut7);
			retcode = SQLBindCol(hstmt, 8, SQL_C_CHAR, L8, sizeof(L8), &lenOut8);
			retcode = SQLBindCol(hstmt, 9, SQL_C_CHAR, L9, sizeof(L9), &lenOut9);
			retcode = SQLFetch(hstmt);
			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
				printf("%d\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", i, L1, L2, L3, L4, L5, L6, L7, L8, L9);
			i++;
		}
	}
}
void SelectPatient()
{
	string str1 = "use 医院信息管理系统";
	string str2 = "SELECT * FROM 病人 WHERE 姓名 = '";
	cout << "请输入要查询的病人姓名:";
	string Sno;
	cin >> Sno;
	string str3 = str2 + Sno + "'";
	SQLHSTMT hstmt;
	int i = 1;
	char L1[20], L2[10], L3[10], L4[10], L5[10], L6[20], L7[200], L8[20], L9[10];
	long lenOut1 = 0, lenOut2 = 0, lenOut3 = 0, lenOut4 = 0, lenOut5 = 0, lenOut6 = 0, lenOut7 = 0, lenOut8 = 0, lenOut9 = 0;
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	if (retcode == SQL_SUCCESS)
	{
		retcode = SQLExecDirect(hstmt, (SQLCHAR*)str1.c_str(), SQL_NTS);
		retcode = SQLExecDirect(hstmt, (SQLCHAR*)str3.c_str(), SQL_NTS);
		printf("编号     身份证号     工作证号   病房号     姓名     性别       年龄      病例信息      入院日期     出院日期\n");
		while (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
		{
			retcode = SQLBindCol(hstmt, 1, SQL_C_CHAR, L1, sizeof(L1), &lenOut1);
			retcode = SQLBindCol(hstmt, 2, SQL_C_CHAR, L2, sizeof(L2), &lenOut2);
			retcode = SQLBindCol(hstmt, 3, SQL_C_CHAR, L3, sizeof(L3), &lenOut3);
			retcode = SQLBindCol(hstmt, 4, SQL_C_CHAR, L4, sizeof(L4), &lenOut4);
			retcode = SQLBindCol(hstmt, 5, SQL_C_CHAR, L5, sizeof(L5), &lenOut5);
			retcode = SQLBindCol(hstmt, 6, SQL_C_CHAR, L6, sizeof(L6), &lenOut6);
			retcode = SQLBindCol(hstmt, 7, SQL_C_CHAR, L7, sizeof(L7), &lenOut7);
			retcode = SQLBindCol(hstmt, 8, SQL_C_CHAR, L8, sizeof(L8), &lenOut8);
			retcode = SQLBindCol(hstmt, 9, SQL_C_CHAR, L9, sizeof(L9), &lenOut9);
			retcode = SQLFetch(hstmt);
			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
				printf("%d\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", i, L1, L2, L3, L4, L5, L6, L7, L8, L9);
			i++;
		}
	}

}
void AddPatient()
{
	SQLHSTMT hstmt;
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	string str1 = "use 医院信息管理系统";
	string str2 = "insert into 病人 values ('";
	string l1, l2, l3, l4, l5, l6, l7, l8, l9;
	cout << "请输入新的身份证号：" << endl;
	cin >> l1;
	cout << "请输入新的工作证号：" << endl;
	cin >> l2;
	cout << "请输入新的病房号：" << endl;
	cin >> l3;
	cout << "请输入新的姓名：" << endl;
	cin >> l4;
	cout << "请输入新的性别：" << endl;
	cin >> l5;
	cout << "请输入新的年龄：" << endl;
	cin >> l6;
	cout << "请输入新的病例信息：" << endl;
	cin >> l7;
	cout << "请输入新的入院日期：" << endl;
	cin >> l8;
	cout << "请输入新的出院日期：" << endl;
	cin >> l9;
	string str3 = str2 + l1 + "','" + l2 + "','" + l3 + "','" + l4 + "','" + l5 + "','" + l6 + "','" + l7 + "','" + l8 + "','" + l9 + "'" + ")";
	retcode = SQLExecDirect(hstmt, (SQLCHAR*)str1.c_str(), SQL_NTS);
	retcode = SQLExecDirect(hstmt, (SQLCHAR*)str3.c_str(), SQL_NTS);
	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
		cout << "病人增加成功！" << endl;
	}
	else {
		cout << "病人增加失败！" << endl;
	}

	SQLFreeStmt(hstmt, SQL_DROP);
	system("pause");
	system("cls");
}

void ChangePatient()
{
	SQLHSTMT hstmt;
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);//申请句柄
	string str1 = "use 医院信息管理系统";
	string Array[] = { "身份证号","工作证号","病房号","姓名","性别","年龄","病例信息","入院日期","出院日期"};

	while (1)
	{
		cout << "  **********************请输入要修改的属性：*******************  " << endl;
		cout << "      0，身份证号、      1，工作证号、         2，病房号、       " << endl;
		cout << "      3，姓名、          4，性别、             5，年龄           " << endl;
		cout << "      6，病例信息、      7，入院日期，         8，出院日期       " << endl;
		cout << "                         9，退出修改                             " << endl;
		cout << "  *************************************************************  " << endl;
		int select = 0;
		cin >> select;
		if (select == 9)
		{
			cout << "已退出修改菜单\n";
			break;
		}
		else if (select >= 0 || select <= 8)
		{
			cout << "请输入原先的病人姓名：\n";
			string str2; cin >> str2;
			cout << "请输入新的" << Array[select] << "：\n";
			string str4; cin >> str4;
			string str6 = "update 病人 set " + Array[select] + " = '" + str4 + "'" + "where 姓名='" + str2 + "'";
			retcode = SQLExecDirect(hstmt, (SQLCHAR*)str1.c_str(), SQL_NTS);
			retcode = SQLExecDirect(hstmt, (SQLCHAR*)str6.c_str(), SQL_NTS);
			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
				cout << Array[select] << "修改成功！\n" << endl;
			}
			else {
				cout << Array[select] << "修改成功！\n" << endl;
			}
			cout << "是否还要继续修改 1-继续修改，0-退出修改\n";
			cin >> select;
			if (select == 0)break;
		}
		else
		{
			cout << "输入无效，请重新输入" << endl;
		}
	}
	SQLFreeStmt(hstmt, SQL_DROP);
	system("pause");
	system("cls");
}
int DoctorManage()
{
	while (1)
	{
		DoctorMenu();
		cout << "请输入你要查询板块的编号：";
		int select = 0;
		cin >> select;     //用户选择
		switch (select)
		{
		case 1:
			DoctorPrint();
			break;
		case 2:
			SelectDoctor();
			break;
		case 3:
			AddDoctor();
			break;
		case 4:
			DeleteDoctor();
			break;
		case 5:
			ChangeDoctor();
			break;
		case 0:
			return 0;
			break;
		default:
			cout << "无效输入，请重新输入：\n";
			break;
		}
	}
}


void DoctorMenu()
{
	cout << "*****************************************************" << endl;
	cout << "***************  1、浏览医生信息    *****************" << endl;
	cout << "***************  2、查询医生信息    *****************" << endl;
	cout << "***************  3、增加医生信息    *****************" << endl;
	cout << "***************  4、删除医生信息    *****************" << endl;
	cout << "***************  5、修改医生信息    *****************" << endl;
	cout << "***************  0、退出医生管理    *****************" << endl;
	cout << "*****************************************************" << endl;
}
void DoctorPrint()
{
	string str1 = "use 医院信息管理系统";
	string str2 = "select * from 医生";
	SQLHSTMT hstmt;
	int i = 1;

	char L1[10], L2[10], L3[20], L4[20], L5[10], L6[20], L7[10];
	long lenOut1 = 0, lenOut2 = 0, lenOut3 = 0, lenOut4 = 0, lenOut5 = 0, lenOut6 = 0, lenOut7 = 0;

	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	if (retcode == SQL_SUCCESS)
	{
		retcode = SQLExecDirect(hstmt, (SQLCHAR*)str1.c_str(), SQL_NTS);
		retcode = SQLExecDirect(hstmt, (SQLCHAR*)str2.c_str(), SQL_NTS);
		printf("编号    工作证号    科室编号   姓名    年龄    性别    职称     工资信息\n");
		while (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
		{
			retcode = SQLBindCol(hstmt, 1, SQL_C_CHAR, L1, sizeof(L1), &lenOut1);
			retcode = SQLBindCol(hstmt, 2, SQL_C_CHAR, L2, sizeof(L2), &lenOut2);
			retcode = SQLBindCol(hstmt, 3, SQL_C_CHAR, L3, sizeof(L3), &lenOut3);
			retcode = SQLBindCol(hstmt, 4, SQL_C_CHAR, L4, sizeof(L4), &lenOut4);
			retcode = SQLBindCol(hstmt, 5, SQL_C_CHAR, L5, sizeof(L5), &lenOut5);
			retcode = SQLBindCol(hstmt, 6, SQL_C_CHAR, L6, sizeof(L6), &lenOut6);
			retcode = SQLBindCol(hstmt, 7, SQL_C_CHAR, L7, sizeof(L7), &lenOut7);
			retcode = SQLFetch(hstmt);
			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
				printf("%d\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", i, L1, L2, L3, L4, L5, L6, L7);
			i++;
		}
	}
}
void SelectDoctor()
{
	string str1 = "use 医院信息管理系统";
	string str2 = "SELECT * FROM 医生 WHERE 姓名 = '";

	cout << "请输入要查询的医生姓名:";
	string Sno;
	cin >> Sno;
	string str3 = str2 + Sno + "'";
	SQLHSTMT hstmt;
	int i = 1;

	char L1[10], L2[10], L3[20], L4[20], L5[10], L6[20], L7[10];
	long lenOut1 = 0, lenOut2 = 0, lenOut3 = 0, lenOut4 = 0, lenOut5 = 0, lenOut6 = 0, lenOut7 = 0;

	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	if (retcode == SQL_SUCCESS)
	{
		retcode = SQLExecDirect(hstmt, (SQLCHAR*)str1.c_str(), SQL_NTS);
		retcode = SQLExecDirect(hstmt, (SQLCHAR*)str3.c_str(), SQL_NTS);
		printf("编号    工作证号    科室编号   姓名    年龄    性别    职称     工资信息\n");
		while (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
		{
			retcode = SQLBindCol(hstmt, 1, SQL_C_CHAR, L1, sizeof(L1), &lenOut1);
			retcode = SQLBindCol(hstmt, 2, SQL_C_CHAR, L2, sizeof(L2), &lenOut2);
			retcode = SQLBindCol(hstmt, 3, SQL_C_CHAR, L3, sizeof(L3), &lenOut3);
			retcode = SQLBindCol(hstmt, 4, SQL_C_CHAR, L4, sizeof(L4), &lenOut4);
			retcode = SQLBindCol(hstmt, 5, SQL_C_CHAR, L5, sizeof(L5), &lenOut5);
			retcode = SQLBindCol(hstmt, 6, SQL_C_CHAR, L6, sizeof(L6), &lenOut6);
			retcode = SQLBindCol(hstmt, 7, SQL_C_CHAR, L7, sizeof(L7), &lenOut7);
			retcode = SQLFetch(hstmt);
			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
				printf("%d\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", i, L1, L2, L3, L4, L5, L6, L7);
			i++;
		}
	}

}
void AddDoctor()
{
	SQLHSTMT hstmt;
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	string str1 = "use 医院信息管理系统";
	string str2 = "insert into 医生 values ('";
	string l1, l2, l3, l4, l5, l6, l7;
	cout << "请输入新的工作证号：" << endl;
	cin >> l1;
	cout << "请输入新的科室编号：" << endl;
	cin >> l2;
	cout << "请输入新的姓名：" << endl;
	cin >> l3;
	cout << "请输入新的年龄：" << endl;
	cin >> l4;
	cout << "请输入新的性别：" << endl;
	cin >> l5;
	cout << "请输入新的职称：" << endl;
	cin >> l6;
	cout << "请输入新的工资信息：" << endl;
	cin >> l7;
	string str3 = str2 + l1 + "','" + l2 + "','" + l3 + "','" + l4 + "','" + l5 + "','" + l6 + "','" + l7 +  "'" + ")";
	retcode = SQLExecDirect(hstmt, (SQLCHAR*)str1.c_str(), SQL_NTS);
	retcode = SQLExecDirect(hstmt, (SQLCHAR*)str3.c_str(), SQL_NTS);
	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
		cout << "医生增加成功！" << endl;
	}
	else {
		cout << "医生增加失败！" << endl;
	}

	SQLFreeStmt(hstmt, SQL_DROP);
	system("pause");
	system("cls");
}
void DeleteDoctor()
{
		SQLHSTMT hstmt;
		retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
		string str1 = "use 医院信息管理系统";
		string str2 = "delete from 医生 where 姓名='";
		cout << "请输入要删除的医生姓名：" << endl;
		string Bname;
		cin >> Bname;
		string str3 = str2 + Bname + "'";
		retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
		retcode = SQLExecDirect(hstmt, (SQLCHAR*)str1.c_str(), SQL_NTS);
		retcode = SQLExecDirect(hstmt, (SQLCHAR*)str3.c_str(), SQL_NTS);
		if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
			cout << "删除医生操作成功！" << endl;
		}
		else {
			cout << "删除医生操作失败！" << endl;
		}
		SQLFreeStmt(hstmt, SQL_DROP);
		system("pause");
		system("cls");
}
void ChangeDoctor()
{
	SQLHSTMT hstmt;
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);//申请句柄
	string str1 = "use 医院信息管理系统";
	string Array[] = { "工作证号","科室编号","姓名","年龄","性别","职称","工资信息" };

	while (1)
	{
		cout << "  **********************请输入要修改的属性：*******************  " << endl;
		cout << "      0，工作证号、      1，科室编号、         2，姓名、         " << endl;
		cout << "      3，年龄、          4，性别、             5，职称           " << endl;
		cout << "      6，工资信息、      7，退出修改                             " << endl;
		cout << "  *************************************************************  " << endl;
		int select = 0;
		cin >> select;
		if (select == 7)
		{
			cout << "已退出修改菜单\n";
			break;
		}
		else if (select >= 0 || select <= 6)
		{
			cout << "请输入原先的医生姓名：\n";
			string str2; cin >> str2;
			cout << "请输入新的" << Array[select] << "：\n";
			string str4; cin >> str4;
			string str6 = "update 医生 set " + Array[select] + " = '" + str4 + "'" + "where 姓名='" + str2 + "'";
			retcode = SQLExecDirect(hstmt, (SQLCHAR*)str1.c_str(), SQL_NTS);
			retcode = SQLExecDirect(hstmt, (SQLCHAR*)str6.c_str(), SQL_NTS);
			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
				cout << Array[select] << "修改成功！\n" << endl;
			}
			else {
				cout << Array[select] << "修改成功！\n" << endl;
			}
			cout << "是否还要继续修改 1-继续修改，0-退出修改\n";
			cin >> select;
			if (select == 0)break;
		}
		else
		{
			cout << "输入无效，请重新输入" << endl;
		}
	}
	SQLFreeStmt(hstmt, SQL_DROP);
	system("pause");
	system("cls");
}

int RoomManage()
{
	while (1)
	{
		RoomMenu();
		cout << "请输入你要查询板块的编号：";
		int select = 0;
		cin >> select;     //用户选择
		switch (select)
		{
		case 1:
			RoomPrint();
			break;
		case 2:
			SelectRoom();
			break;
		case 3:
			AddRoom();
			break;
		case 4:
			ChangeRoom();
			break;
		case 0:
			return 0;
			break;
		default:
			cout << "无效输入，请重新输入：\n";
			break;
		}
	}
}


void RoomMenu()
{
	cout << "*****************************************************" << endl;
	cout << "***************  1、浏览病房信息    *****************" << endl;
	cout << "***************  2、查询病房信息    *****************" << endl;
	cout << "***************  3、增加病房信息    *****************" << endl;
	cout << "***************  4、修改病房信息    *****************" << endl;
	cout << "***************  0、退出病房管理    *****************" << endl;
	cout << "*****************************************************" << endl;
}
void RoomPrint()
{
	string str1 = "use 医院信息管理系统";
	string str2 = "select * from 病房";
	SQLHSTMT hstmt;
	int i = 1;

	char L1[10], L2[10], L3[20];
	long lenOut1 = 0, lenOut2 = 0, lenOut3 = 0;

	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	if (retcode == SQL_SUCCESS)
	{
		retcode = SQLExecDirect(hstmt, (SQLCHAR*)str1.c_str(), SQL_NTS);
		retcode = SQLExecDirect(hstmt, (SQLCHAR*)str2.c_str(), SQL_NTS);
		printf("编号  病房号   科室编号   病房地址\n");
		while (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
		{
			retcode = SQLBindCol(hstmt, 1, SQL_C_CHAR, L1, sizeof(L1), &lenOut1);
			retcode = SQLBindCol(hstmt, 2, SQL_C_CHAR, L2, sizeof(L2), &lenOut2);
			retcode = SQLBindCol(hstmt, 3, SQL_C_CHAR, L3, sizeof(L3), &lenOut3);
			retcode = SQLFetch(hstmt);
			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
				printf("%d\t%s\t%s\t%s\n", i, L1, L2, L3);
			i++;
		}
	}
}
void SelectRoom()
{
	string str1 = "use 医院信息管理系统";
	string str2 = "SELECT * FROM 病房 WHERE 病房号 = '";
	cout << "请输入要查询的病房号:";
	string Sno;
	cin >> Sno;
	string str3 = str2 + Sno + "'";
	SQLHSTMT hstmt;
	int i = 1;
	char L1[10], L2[10], L3[20];
	long lenOut1 = 0, lenOut2 = 0, lenOut3 = 0;
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	if (retcode == SQL_SUCCESS)
	{
		retcode = SQLExecDirect(hstmt, (SQLCHAR*)str1.c_str(), SQL_NTS);
		retcode = SQLExecDirect(hstmt, (SQLCHAR*)str3.c_str(), SQL_NTS);
		printf("编号  病房号   科室编号   病房地址\n");
		while (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
		{
			retcode = SQLBindCol(hstmt, 1, SQL_C_CHAR, L1, sizeof(L1), &lenOut1);
			retcode = SQLBindCol(hstmt, 2, SQL_C_CHAR, L2, sizeof(L2), &lenOut2);
			retcode = SQLBindCol(hstmt, 3, SQL_C_CHAR, L3, sizeof(L3), &lenOut3);
			retcode = SQLFetch(hstmt);
			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
				printf("%d\t%s\t%s\t%s\n", i, L1, L2, L3);
			i++;
		}
	}

}
void AddRoom()
{
	SQLHSTMT hstmt;
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	string str1 = "use 医院信息管理系统";
	string str2 = "insert into 病房 values ('";
	string l1, l2, l3;
	cout << "请输入新的病房号号：" << endl;
	cin >> l1;
	cout << "请输入新的科室编号：" << endl;
	cin >> l2;
	cout << "请输入新的病房地址：" << endl;
	cin >> l3;
	string str3 = str2 + l1 + "','" + l2 + "','" + l3 + "'" + ")";
	retcode = SQLExecDirect(hstmt, (SQLCHAR*)str1.c_str(), SQL_NTS);
	retcode = SQLExecDirect(hstmt, (SQLCHAR*)str3.c_str(), SQL_NTS);
	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
		cout << "病房增加成功！" << endl;
	}
	else {
		cout << "病房增加失败！" << endl;
	}

	SQLFreeStmt(hstmt, SQL_DROP);
	system("pause");
	system("cls");
}

void ChangeRoom()
{
	SQLHSTMT hstmt;
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);//申请句柄
	string str1 = "use 医院信息管理系统";
	string Array[] = { "病房号","科室编号","病房地址" };

	while (1)
	{
		cout << "  **********************请输入要修改的属性：*******************  " << endl;
		cout << "      0，病房号、      1，科室编号、         2，病房地址、       " << endl;
		cout << "                       3，退出修改                               " << endl;
		cout << "  *************************************************************  " << endl;
		int select = 0;
		cin >> select;
		if (select == 3)
		{
			cout << "已退出修改菜单\n";
			break;
		}
		else if (select >= 0 || select <= 2)
		{
			cout << "请输入原先的病房号：\n";
			string str2; cin >> str2;
			cout << "请输入新的" << Array[select] << "：\n";
			string str4; cin >> str4;
			string str6 = "update 病房 set " + Array[select] + " = '" + str4 + "'" + "where 病房号='" + str2 + "'";
			retcode = SQLExecDirect(hstmt, (SQLCHAR*)str1.c_str(), SQL_NTS);
			retcode = SQLExecDirect(hstmt, (SQLCHAR*)str6.c_str(), SQL_NTS);
			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
				cout << Array[select] << "修改成功！\n" << endl;
			}
			else {
				cout << Array[select] << "修改成功！\n" << endl;
			}
			cout << "是否还要继续修改 1-继续修改，0-退出修改\n";
			cin >> select;
			if (select == 0)break;
		}
		else
		{
			cout << "输入无效，请重新输入" << endl;
		}
	}
	SQLFreeStmt(hstmt, SQL_DROP);
	system("pause");
	system("cls");
}

int ElseManage()
{
	while (1)
	{
		ElseMenu();
		cout << "请输入你要查询板块的编号：";
		int select = 0;
		cin >> select;
		switch (select)
		{
		case 1:
			DoctorClassify();
			break;
		case 2:
			WritePatient();
			break;
		case 3:
			LeaveHospital();
			break;
		case 0:
			return 0;
			break;
		default:
			cout << "无效输入，请重新输入：\n";
			break;
		}
	}
}
void ElseMenu()
{
	cout << "*****************************************************" << endl;
	cout << "***************  1、医生分类统计    *****************" << endl;
	cout << "***************  2、病人病历填写    *****************" << endl;
	cout << "***************  3、办理出院手续    *****************" << endl;
	cout << "***************  0、退出服务管理    *****************" << endl;
	cout << "*****************************************************" << endl;
}
void DoctorClassify()
{
	string str1 = "use 医院信息管理系统";
	SQLHSTMT hstmt;
	cout << "  **********************请输入分类的属性：*******************  " << endl;
	cout << "                  1，性别、         2,职称、                   " << endl;
	cout << "  ************************************************************ " << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		string str2 = "select 科室编号,count(科室编号),sum(case when 性别='男' then 1 else 0 end ),sum(case when 性别='女' then 1 else 0 end) from 医生 group by 科室编号;";
		char L1[10], L2[10], L3[20], L4[20];
		long lenOut1 = 0, lenOut2 = 0, lenOut3 = 0, lenOut4 = 0;

		retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
		if (retcode == SQL_SUCCESS)
		{
			retcode = SQLExecDirect(hstmt, (SQLCHAR*)str1.c_str(), SQL_NTS);
			retcode = SQLExecDirect(hstmt, (SQLCHAR*)str2.c_str(), SQL_NTS);
			printf("科室编号  总医生个数  男医生个数   女医生个数 \n");
			while (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
			{
				retcode = SQLBindCol(hstmt, 1, SQL_C_CHAR, L1, sizeof(L1), &lenOut1);
				retcode = SQLBindCol(hstmt, 2, SQL_C_CHAR, L2, sizeof(L2), &lenOut2);
				retcode = SQLBindCol(hstmt, 3, SQL_C_CHAR, L3, sizeof(L3), &lenOut3);
				retcode = SQLBindCol(hstmt, 4, SQL_C_CHAR, L4, sizeof(L4), &lenOut4);
				retcode = SQLFetch(hstmt);
				if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
					printf("  %s         %s           %s            %s\n", L1, L2, L3, L4);
			}
		}
	}
	if (select == 2)
	{
		string str2 = "select 科室编号,count(科室编号),sum(case when 职称='主任医师' then 1 else 0 end ),sum(case when 职称='副主任医师' then 1 else 0 end) from 医生 group by 科室编号;";
		char L1[10], L2[10], L3[20], L4[20];
		long lenOut1 = 0, lenOut2 = 0, lenOut3 = 0, lenOut4 = 0;

		retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
		if (retcode == SQL_SUCCESS)
		{
			retcode = SQLExecDirect(hstmt, (SQLCHAR*)str1.c_str(), SQL_NTS);
			retcode = SQLExecDirect(hstmt, (SQLCHAR*)str2.c_str(), SQL_NTS);
			printf("科室编号  总医生个数  主任医师个数   副主任医师个数 \n");
			while (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
			{
				retcode = SQLBindCol(hstmt, 1, SQL_C_CHAR, L1, sizeof(L1), &lenOut1);
				retcode = SQLBindCol(hstmt, 2, SQL_C_CHAR, L2, sizeof(L2), &lenOut2);
				retcode = SQLBindCol(hstmt, 3, SQL_C_CHAR, L3, sizeof(L3), &lenOut3);
				retcode = SQLBindCol(hstmt, 4, SQL_C_CHAR, L4, sizeof(L4), &lenOut4);
				retcode = SQLFetch(hstmt);
				if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
					printf("  %s         %s           %s               %s\n", L1, L2, L3, L4);
			}
		}
	}
}

void WritePatient()
{
	SQLHSTMT hstmt;
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	string str1 = "use 医院信息管理系统";
	string b = "病例信息";
	cout << "此项目为医生专用，你是医生吗？(请输入 Y or N)" << endl;
	string a;
	cin >> a;
	if (a == "Y") {
		string password = "123456"; //原始密码
		cout << "输入6位执行密码：";
		string c;
		cin >> c;
		if (c == "123456") {
			cout << "请输入你要填写病例的病人的姓名：\n";
			string str2;
			cin >> str2;
			cout << "请输入病人的" << b << "：\n";
			string str4;
			cin >> str4;
			string str6 = "update 病人 set " + b + " = '" + str4 + "'" + "where 姓名='" + str2 + "'";
			retcode = SQLExecDirect(hstmt, (SQLCHAR*)str1.c_str(), SQL_NTS);
			retcode = SQLExecDirect(hstmt, (SQLCHAR*)str6.c_str(), SQL_NTS);
			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
				cout << b << "填写成功！\n" << endl;
			}
			else {
				cout << b << "填写失败！\n" << endl;
			}
		}
		else {
			cout << "你没有权限！" << endl;
		}
	}
	else {
		cout << "你没有权限！" << endl;
	}

	SQLFreeStmt(hstmt, SQL_DROP);
	system("pause");
	system("cls");
}
void LeaveHospital()
{
	SQLHSTMT hstmt;
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	string str1 = "use 医院信息管理系统";
	string str2 = "delete from 病人 where 姓名='";
	cout << "确认办理出院手续吗？(请输入 Y or N)" << endl;
	string a;
	cin >> a;
	if (a == "Y") {
		cout << "请输入你的主治医生的工作证号：" << endl;
		string b;
		cin >> b;
		cout << "请输入你的名字：" << endl;
		string c;
		cin >> c;
		string str3 = str2 + c + "'";
		retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
		retcode = SQLExecDirect(hstmt, (SQLCHAR*)str1.c_str(), SQL_NTS);
		retcode = SQLExecDirect(hstmt, (SQLCHAR*)str3.c_str(), SQL_NTS);
		if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
			cout << "办理出院手续成功！" << endl;
		}
		else {
			cout << "办理出院手续失败！" << endl;
		}
	}
	else {
		cout << "欢迎下次使用" << endl;
	}

	SQLFreeStmt(hstmt, SQL_DROP);
	system("pause");
	system("cls");
}