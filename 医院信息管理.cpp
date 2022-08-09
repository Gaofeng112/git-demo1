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

RETCODE retcode;  //������ؼ�
SQLHDBC hdbc;     //�������Ӿ��

void SQL(char*);  //ִ��SQL����ӳ���
void ShowMainMenu();   //��ʾ���˵�

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
	unsigned char SY[] = "ҽԺ��Ϣ����ϵͳ";   
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
			cout << "��������Ҫ��ѯ���ı�ţ�";
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
				cout << "��������������������������������������������������ӭ�´�ʹ�ã�����������������������������������������������������" << endl;
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

//���˵�
void ShowMainMenu()//���˵�
{
	cout << "*****************************************************************" << endl;
	cout << "*********************  1��������Ϣ����    ***********************" << endl;
	cout << "*********************  2��ҽ����Ϣ����    ***********************" << endl;
	cout << "*********************  3��������Ϣ����    ***********************" << endl;
	cout << "*********************  4��������Ϣ����    ***********************" << endl;
	cout << "*********************  5�������������    ***********************" << endl;
	cout << "*********************  0���˳�����ϵͳ    ***********************" << endl;
	cout << "*****************************************************************" << endl;
}
int DepartManage()
{
	while (1)
	{
		DepartMenu(); 
		cout << "��������Ҫ��ѯ���ı�ţ�";
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
			cout << "��Ч���룬���������룺\n";
			break;
		}
	}
}


void DepartMenu()
{
	cout << "*****************************************************" << endl;
	cout << "***************  1�����������Ϣ    *****************" << endl;
	cout << "***************  2����ѯ������Ϣ    *****************" << endl;
	cout << "***************  3�����ӿ�����Ϣ    *****************" << endl;
	cout << "***************  4���޸Ŀ�����Ϣ    *****************" << endl;
	cout << "***************  0���˳����ҹ���    *****************" << endl;
	cout << "*****************************************************" << endl;
}
void DepartPrint()
{
	string str1 = "use ҽԺ��Ϣ����ϵͳ";
	string str2 = "select * from ����";
	SQLHSTMT hstmt;  
	int i = 1;

	char L1[10], L2[10], L3[20], L4[20], L5[10];
	long lenOut1=0, lenOut2=0, lenOut3=0, lenOut4=0, lenOut5=0;

	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	if (retcode == SQL_SUCCESS)
	{
		retcode = SQLExecDirect(hstmt, (SQLCHAR*)str1.c_str(), SQL_NTS);
		retcode = SQLExecDirect(hstmt, (SQLCHAR*)str2.c_str(), SQL_NTS);
		printf("���  ���ұ��  ������   �Ƶ�ַ         ��ϵ�绰     �������α��\n");
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
	string str1 = "use ҽԺ��Ϣ����ϵͳ";
	string str2 = "SELECT * FROM ���� WHERE ������ = '";

	cout << "������Ҫ��ѯ�Ŀ�����:" ;
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
		printf("���  ���ұ��  ������   �Ƶ�ַ         ��ϵ�绰     �������α��\n");
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
	string str1 = "use ҽԺ��Ϣ����ϵͳ";
	string str2 = "insert into ���� values ('";
	string l1, l2, l3, l4, l5;
	cout << "�������µĿ��ұ�ţ�" << endl;
	cin >> l1;
	cout << "�������µĿ�������" << endl;
	cin >> l2;
	cout << "�������µĿƵ�ַ��" << endl;
	cin >> l3;
	cout << "�������µ���ϵ�绰��" << endl;
	cin >> l4;
	cout << "�������µĿ������α�ţ�" << endl;
	cin >> l5;
	string str3 = str2 + l1 + "','" + l2 + "','" + l3 + "','" + l4 + "','" + l5 + "'" + ")";
	retcode = SQLExecDirect(hstmt, (SQLCHAR*)str1.c_str(), SQL_NTS);
	retcode = SQLExecDirect(hstmt, (SQLCHAR*)str3.c_str(), SQL_NTS);
	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
		cout << "�������ӳɹ���" << endl;
	}
	else {
		cout << "��������ʧ�ܣ�" << endl;
	}

	SQLFreeStmt(hstmt, SQL_DROP);
	system("pause");
	system("cls");
}
void ChangeDepart()
{
	SQLHSTMT hstmt;
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);//������
	string str1 = "use ҽԺ��Ϣ����ϵͳ";
	string Array[] = { "���ұ��","������","�Ƶ�ַ","��ϵ�绰","�������α��"};

	while (1)
	{
		cout << "  **********************������Ҫ�޸ĵ����ԣ�*******************  " << endl;
		cout << "      0�����ұ�š�      1����������         2���Ƶ�ַ��         " << endl;
		cout << "      3����ϵ�绰��      4���������α�š�   5���˳��޸�         " << endl;
		cout << "  *************************************************************  " << endl;
		int select = 0;
		cin >> select;
		if (select == 5)
		{
			cout << "���˳��޸Ĳ˵�\n";
			break;
		}
		else if (select >= 0 || select <= 4)
		{
			cout << "������ԭ�ȵĿ�������\n";
			string str2; cin >> str2;
			cout << "�������µ�" << Array[select] << "��\n";
			string str4; cin >> str4;
			string str6 = "update ���� set " + Array[select] + " = '" + str4 + "'" + "where ������='" + str2 + "'";
			retcode = SQLExecDirect(hstmt, (SQLCHAR*)str1.c_str(), SQL_NTS);
			retcode = SQLExecDirect(hstmt, (SQLCHAR*)str6.c_str(), SQL_NTS);
			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
				cout << Array[select] << "�޸ĳɹ���\n" << endl;
			}
			else {
				cout << Array[select] << "�޸ĳɹ���\n" << endl;
			}
			cout << "�Ƿ�Ҫ�����޸� 1-�����޸ģ�0-�˳��޸�\n";
			cin >> select;
			if (select == 0)break;
		}
		else
		{
			cout << "������Ч������������" << endl;
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
		cout << "��������Ҫ��ѯ���ı�ţ�";
		int select = 0;
		cin >> select;     //�û�ѡ��
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
			cout << "��Ч���룬���������룺\n";
			break;
		}
	}
}


void PatientMenu()
{
	cout << "*****************************************************" << endl;
	cout << "***************  1�����������Ϣ    *****************" << endl;
	cout << "***************  2����ѯ������Ϣ    *****************" << endl;
	cout << "***************  3�����Ӳ�����Ϣ    *****************" << endl;
	cout << "***************  4���޸Ĳ�����Ϣ    *****************" << endl;
	cout << "***************  0���˳����˹���    *****************" << endl;
	cout << "*****************************************************" << endl;
}
void PatientPrint()
{
	string str1 = "use ҽԺ��Ϣ����ϵͳ";
	string str2 = "select * from ����";
	SQLHSTMT hstmt;
	int i = 1;
	char L1[20], L2[10], L3[10], L4[10], L5[10], L6[20], L7[200], L8[20], L9[10];
	long lenOut1 = 0, lenOut2 = 0, lenOut3 = 0, lenOut4 = 0, lenOut5 = 0, lenOut6 = 0, lenOut7 = 0,lenOut8 = 0, lenOut9 = 0;
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	if (retcode == SQL_SUCCESS)
	{
		retcode = SQLExecDirect(hstmt, (SQLCHAR*)str1.c_str(), SQL_NTS);
		retcode = SQLExecDirect(hstmt, (SQLCHAR*)str2.c_str(), SQL_NTS);
		printf("���     ���֤��     ����֤��   ������     ����     �Ա�    ����      ������Ϣ      ��Ժ����     ��Ժ����\n");
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
	string str1 = "use ҽԺ��Ϣ����ϵͳ";
	string str2 = "SELECT * FROM ���� WHERE ���� = '";
	cout << "������Ҫ��ѯ�Ĳ�������:";
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
		printf("���     ���֤��     ����֤��   ������     ����     �Ա�       ����      ������Ϣ      ��Ժ����     ��Ժ����\n");
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
	string str1 = "use ҽԺ��Ϣ����ϵͳ";
	string str2 = "insert into ���� values ('";
	string l1, l2, l3, l4, l5, l6, l7, l8, l9;
	cout << "�������µ����֤�ţ�" << endl;
	cin >> l1;
	cout << "�������µĹ���֤�ţ�" << endl;
	cin >> l2;
	cout << "�������µĲ����ţ�" << endl;
	cin >> l3;
	cout << "�������µ�������" << endl;
	cin >> l4;
	cout << "�������µ��Ա�" << endl;
	cin >> l5;
	cout << "�������µ����䣺" << endl;
	cin >> l6;
	cout << "�������µĲ�����Ϣ��" << endl;
	cin >> l7;
	cout << "�������µ���Ժ���ڣ�" << endl;
	cin >> l8;
	cout << "�������µĳ�Ժ���ڣ�" << endl;
	cin >> l9;
	string str3 = str2 + l1 + "','" + l2 + "','" + l3 + "','" + l4 + "','" + l5 + "','" + l6 + "','" + l7 + "','" + l8 + "','" + l9 + "'" + ")";
	retcode = SQLExecDirect(hstmt, (SQLCHAR*)str1.c_str(), SQL_NTS);
	retcode = SQLExecDirect(hstmt, (SQLCHAR*)str3.c_str(), SQL_NTS);
	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
		cout << "�������ӳɹ���" << endl;
	}
	else {
		cout << "��������ʧ�ܣ�" << endl;
	}

	SQLFreeStmt(hstmt, SQL_DROP);
	system("pause");
	system("cls");
}

void ChangePatient()
{
	SQLHSTMT hstmt;
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);//������
	string str1 = "use ҽԺ��Ϣ����ϵͳ";
	string Array[] = { "���֤��","����֤��","������","����","�Ա�","����","������Ϣ","��Ժ����","��Ժ����"};

	while (1)
	{
		cout << "  **********************������Ҫ�޸ĵ����ԣ�*******************  " << endl;
		cout << "      0�����֤�š�      1������֤�š�         2�������š�       " << endl;
		cout << "      3��������          4���Ա�             5������           " << endl;
		cout << "      6��������Ϣ��      7����Ժ���ڣ�         8����Ժ����       " << endl;
		cout << "                         9���˳��޸�                             " << endl;
		cout << "  *************************************************************  " << endl;
		int select = 0;
		cin >> select;
		if (select == 9)
		{
			cout << "���˳��޸Ĳ˵�\n";
			break;
		}
		else if (select >= 0 || select <= 8)
		{
			cout << "������ԭ�ȵĲ���������\n";
			string str2; cin >> str2;
			cout << "�������µ�" << Array[select] << "��\n";
			string str4; cin >> str4;
			string str6 = "update ���� set " + Array[select] + " = '" + str4 + "'" + "where ����='" + str2 + "'";
			retcode = SQLExecDirect(hstmt, (SQLCHAR*)str1.c_str(), SQL_NTS);
			retcode = SQLExecDirect(hstmt, (SQLCHAR*)str6.c_str(), SQL_NTS);
			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
				cout << Array[select] << "�޸ĳɹ���\n" << endl;
			}
			else {
				cout << Array[select] << "�޸ĳɹ���\n" << endl;
			}
			cout << "�Ƿ�Ҫ�����޸� 1-�����޸ģ�0-�˳��޸�\n";
			cin >> select;
			if (select == 0)break;
		}
		else
		{
			cout << "������Ч������������" << endl;
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
		cout << "��������Ҫ��ѯ���ı�ţ�";
		int select = 0;
		cin >> select;     //�û�ѡ��
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
			cout << "��Ч���룬���������룺\n";
			break;
		}
	}
}


void DoctorMenu()
{
	cout << "*****************************************************" << endl;
	cout << "***************  1�����ҽ����Ϣ    *****************" << endl;
	cout << "***************  2����ѯҽ����Ϣ    *****************" << endl;
	cout << "***************  3������ҽ����Ϣ    *****************" << endl;
	cout << "***************  4��ɾ��ҽ����Ϣ    *****************" << endl;
	cout << "***************  5���޸�ҽ����Ϣ    *****************" << endl;
	cout << "***************  0���˳�ҽ������    *****************" << endl;
	cout << "*****************************************************" << endl;
}
void DoctorPrint()
{
	string str1 = "use ҽԺ��Ϣ����ϵͳ";
	string str2 = "select * from ҽ��";
	SQLHSTMT hstmt;
	int i = 1;

	char L1[10], L2[10], L3[20], L4[20], L5[10], L6[20], L7[10];
	long lenOut1 = 0, lenOut2 = 0, lenOut3 = 0, lenOut4 = 0, lenOut5 = 0, lenOut6 = 0, lenOut7 = 0;

	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	if (retcode == SQL_SUCCESS)
	{
		retcode = SQLExecDirect(hstmt, (SQLCHAR*)str1.c_str(), SQL_NTS);
		retcode = SQLExecDirect(hstmt, (SQLCHAR*)str2.c_str(), SQL_NTS);
		printf("���    ����֤��    ���ұ��   ����    ����    �Ա�    ְ��     ������Ϣ\n");
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
	string str1 = "use ҽԺ��Ϣ����ϵͳ";
	string str2 = "SELECT * FROM ҽ�� WHERE ���� = '";

	cout << "������Ҫ��ѯ��ҽ������:";
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
		printf("���    ����֤��    ���ұ��   ����    ����    �Ա�    ְ��     ������Ϣ\n");
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
	string str1 = "use ҽԺ��Ϣ����ϵͳ";
	string str2 = "insert into ҽ�� values ('";
	string l1, l2, l3, l4, l5, l6, l7;
	cout << "�������µĹ���֤�ţ�" << endl;
	cin >> l1;
	cout << "�������µĿ��ұ�ţ�" << endl;
	cin >> l2;
	cout << "�������µ�������" << endl;
	cin >> l3;
	cout << "�������µ����䣺" << endl;
	cin >> l4;
	cout << "�������µ��Ա�" << endl;
	cin >> l5;
	cout << "�������µ�ְ�ƣ�" << endl;
	cin >> l6;
	cout << "�������µĹ�����Ϣ��" << endl;
	cin >> l7;
	string str3 = str2 + l1 + "','" + l2 + "','" + l3 + "','" + l4 + "','" + l5 + "','" + l6 + "','" + l7 +  "'" + ")";
	retcode = SQLExecDirect(hstmt, (SQLCHAR*)str1.c_str(), SQL_NTS);
	retcode = SQLExecDirect(hstmt, (SQLCHAR*)str3.c_str(), SQL_NTS);
	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
		cout << "ҽ�����ӳɹ���" << endl;
	}
	else {
		cout << "ҽ������ʧ�ܣ�" << endl;
	}

	SQLFreeStmt(hstmt, SQL_DROP);
	system("pause");
	system("cls");
}
void DeleteDoctor()
{
		SQLHSTMT hstmt;
		retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
		string str1 = "use ҽԺ��Ϣ����ϵͳ";
		string str2 = "delete from ҽ�� where ����='";
		cout << "������Ҫɾ����ҽ��������" << endl;
		string Bname;
		cin >> Bname;
		string str3 = str2 + Bname + "'";
		retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
		retcode = SQLExecDirect(hstmt, (SQLCHAR*)str1.c_str(), SQL_NTS);
		retcode = SQLExecDirect(hstmt, (SQLCHAR*)str3.c_str(), SQL_NTS);
		if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
			cout << "ɾ��ҽ�������ɹ���" << endl;
		}
		else {
			cout << "ɾ��ҽ������ʧ�ܣ�" << endl;
		}
		SQLFreeStmt(hstmt, SQL_DROP);
		system("pause");
		system("cls");
}
void ChangeDoctor()
{
	SQLHSTMT hstmt;
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);//������
	string str1 = "use ҽԺ��Ϣ����ϵͳ";
	string Array[] = { "����֤��","���ұ��","����","����","�Ա�","ְ��","������Ϣ" };

	while (1)
	{
		cout << "  **********************������Ҫ�޸ĵ����ԣ�*******************  " << endl;
		cout << "      0������֤�š�      1�����ұ�š�         2��������         " << endl;
		cout << "      3�����䡢          4���Ա�             5��ְ��           " << endl;
		cout << "      6��������Ϣ��      7���˳��޸�                             " << endl;
		cout << "  *************************************************************  " << endl;
		int select = 0;
		cin >> select;
		if (select == 7)
		{
			cout << "���˳��޸Ĳ˵�\n";
			break;
		}
		else if (select >= 0 || select <= 6)
		{
			cout << "������ԭ�ȵ�ҽ��������\n";
			string str2; cin >> str2;
			cout << "�������µ�" << Array[select] << "��\n";
			string str4; cin >> str4;
			string str6 = "update ҽ�� set " + Array[select] + " = '" + str4 + "'" + "where ����='" + str2 + "'";
			retcode = SQLExecDirect(hstmt, (SQLCHAR*)str1.c_str(), SQL_NTS);
			retcode = SQLExecDirect(hstmt, (SQLCHAR*)str6.c_str(), SQL_NTS);
			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
				cout << Array[select] << "�޸ĳɹ���\n" << endl;
			}
			else {
				cout << Array[select] << "�޸ĳɹ���\n" << endl;
			}
			cout << "�Ƿ�Ҫ�����޸� 1-�����޸ģ�0-�˳��޸�\n";
			cin >> select;
			if (select == 0)break;
		}
		else
		{
			cout << "������Ч������������" << endl;
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
		cout << "��������Ҫ��ѯ���ı�ţ�";
		int select = 0;
		cin >> select;     //�û�ѡ��
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
			cout << "��Ч���룬���������룺\n";
			break;
		}
	}
}


void RoomMenu()
{
	cout << "*****************************************************" << endl;
	cout << "***************  1�����������Ϣ    *****************" << endl;
	cout << "***************  2����ѯ������Ϣ    *****************" << endl;
	cout << "***************  3�����Ӳ�����Ϣ    *****************" << endl;
	cout << "***************  4���޸Ĳ�����Ϣ    *****************" << endl;
	cout << "***************  0���˳���������    *****************" << endl;
	cout << "*****************************************************" << endl;
}
void RoomPrint()
{
	string str1 = "use ҽԺ��Ϣ����ϵͳ";
	string str2 = "select * from ����";
	SQLHSTMT hstmt;
	int i = 1;

	char L1[10], L2[10], L3[20];
	long lenOut1 = 0, lenOut2 = 0, lenOut3 = 0;

	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	if (retcode == SQL_SUCCESS)
	{
		retcode = SQLExecDirect(hstmt, (SQLCHAR*)str1.c_str(), SQL_NTS);
		retcode = SQLExecDirect(hstmt, (SQLCHAR*)str2.c_str(), SQL_NTS);
		printf("���  ������   ���ұ��   ������ַ\n");
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
	string str1 = "use ҽԺ��Ϣ����ϵͳ";
	string str2 = "SELECT * FROM ���� WHERE ������ = '";
	cout << "������Ҫ��ѯ�Ĳ�����:";
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
		printf("���  ������   ���ұ��   ������ַ\n");
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
	string str1 = "use ҽԺ��Ϣ����ϵͳ";
	string str2 = "insert into ���� values ('";
	string l1, l2, l3;
	cout << "�������µĲ����źţ�" << endl;
	cin >> l1;
	cout << "�������µĿ��ұ�ţ�" << endl;
	cin >> l2;
	cout << "�������µĲ�����ַ��" << endl;
	cin >> l3;
	string str3 = str2 + l1 + "','" + l2 + "','" + l3 + "'" + ")";
	retcode = SQLExecDirect(hstmt, (SQLCHAR*)str1.c_str(), SQL_NTS);
	retcode = SQLExecDirect(hstmt, (SQLCHAR*)str3.c_str(), SQL_NTS);
	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
		cout << "�������ӳɹ���" << endl;
	}
	else {
		cout << "��������ʧ�ܣ�" << endl;
	}

	SQLFreeStmt(hstmt, SQL_DROP);
	system("pause");
	system("cls");
}

void ChangeRoom()
{
	SQLHSTMT hstmt;
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);//������
	string str1 = "use ҽԺ��Ϣ����ϵͳ";
	string Array[] = { "������","���ұ��","������ַ" };

	while (1)
	{
		cout << "  **********************������Ҫ�޸ĵ����ԣ�*******************  " << endl;
		cout << "      0�������š�      1�����ұ�š�         2��������ַ��       " << endl;
		cout << "                       3���˳��޸�                               " << endl;
		cout << "  *************************************************************  " << endl;
		int select = 0;
		cin >> select;
		if (select == 3)
		{
			cout << "���˳��޸Ĳ˵�\n";
			break;
		}
		else if (select >= 0 || select <= 2)
		{
			cout << "������ԭ�ȵĲ����ţ�\n";
			string str2; cin >> str2;
			cout << "�������µ�" << Array[select] << "��\n";
			string str4; cin >> str4;
			string str6 = "update ���� set " + Array[select] + " = '" + str4 + "'" + "where ������='" + str2 + "'";
			retcode = SQLExecDirect(hstmt, (SQLCHAR*)str1.c_str(), SQL_NTS);
			retcode = SQLExecDirect(hstmt, (SQLCHAR*)str6.c_str(), SQL_NTS);
			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
				cout << Array[select] << "�޸ĳɹ���\n" << endl;
			}
			else {
				cout << Array[select] << "�޸ĳɹ���\n" << endl;
			}
			cout << "�Ƿ�Ҫ�����޸� 1-�����޸ģ�0-�˳��޸�\n";
			cin >> select;
			if (select == 0)break;
		}
		else
		{
			cout << "������Ч������������" << endl;
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
		cout << "��������Ҫ��ѯ���ı�ţ�";
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
			cout << "��Ч���룬���������룺\n";
			break;
		}
	}
}
void ElseMenu()
{
	cout << "*****************************************************" << endl;
	cout << "***************  1��ҽ������ͳ��    *****************" << endl;
	cout << "***************  2�����˲�����д    *****************" << endl;
	cout << "***************  3�������Ժ����    *****************" << endl;
	cout << "***************  0���˳��������    *****************" << endl;
	cout << "*****************************************************" << endl;
}
void DoctorClassify()
{
	string str1 = "use ҽԺ��Ϣ����ϵͳ";
	SQLHSTMT hstmt;
	cout << "  **********************�������������ԣ�*******************  " << endl;
	cout << "                  1���Ա�         2,ְ�ơ�                   " << endl;
	cout << "  ************************************************************ " << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		string str2 = "select ���ұ��,count(���ұ��),sum(case when �Ա�='��' then 1 else 0 end ),sum(case when �Ա�='Ů' then 1 else 0 end) from ҽ�� group by ���ұ��;";
		char L1[10], L2[10], L3[20], L4[20];
		long lenOut1 = 0, lenOut2 = 0, lenOut3 = 0, lenOut4 = 0;

		retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
		if (retcode == SQL_SUCCESS)
		{
			retcode = SQLExecDirect(hstmt, (SQLCHAR*)str1.c_str(), SQL_NTS);
			retcode = SQLExecDirect(hstmt, (SQLCHAR*)str2.c_str(), SQL_NTS);
			printf("���ұ��  ��ҽ������  ��ҽ������   Ůҽ������ \n");
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
		string str2 = "select ���ұ��,count(���ұ��),sum(case when ְ��='����ҽʦ' then 1 else 0 end ),sum(case when ְ��='������ҽʦ' then 1 else 0 end) from ҽ�� group by ���ұ��;";
		char L1[10], L2[10], L3[20], L4[20];
		long lenOut1 = 0, lenOut2 = 0, lenOut3 = 0, lenOut4 = 0;

		retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
		if (retcode == SQL_SUCCESS)
		{
			retcode = SQLExecDirect(hstmt, (SQLCHAR*)str1.c_str(), SQL_NTS);
			retcode = SQLExecDirect(hstmt, (SQLCHAR*)str2.c_str(), SQL_NTS);
			printf("���ұ��  ��ҽ������  ����ҽʦ����   ������ҽʦ���� \n");
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
	string str1 = "use ҽԺ��Ϣ����ϵͳ";
	string b = "������Ϣ";
	cout << "����ĿΪҽ��ר�ã�����ҽ����(������ Y or N)" << endl;
	string a;
	cin >> a;
	if (a == "Y") {
		string password = "123456"; //ԭʼ����
		cout << "����6λִ�����룺";
		string c;
		cin >> c;
		if (c == "123456") {
			cout << "��������Ҫ��д�����Ĳ��˵�������\n";
			string str2;
			cin >> str2;
			cout << "�����벡�˵�" << b << "��\n";
			string str4;
			cin >> str4;
			string str6 = "update ���� set " + b + " = '" + str4 + "'" + "where ����='" + str2 + "'";
			retcode = SQLExecDirect(hstmt, (SQLCHAR*)str1.c_str(), SQL_NTS);
			retcode = SQLExecDirect(hstmt, (SQLCHAR*)str6.c_str(), SQL_NTS);
			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
				cout << b << "��д�ɹ���\n" << endl;
			}
			else {
				cout << b << "��дʧ�ܣ�\n" << endl;
			}
		}
		else {
			cout << "��û��Ȩ�ޣ�" << endl;
		}
	}
	else {
		cout << "��û��Ȩ�ޣ�" << endl;
	}

	SQLFreeStmt(hstmt, SQL_DROP);
	system("pause");
	system("cls");
}
void LeaveHospital()
{
	SQLHSTMT hstmt;
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	string str1 = "use ҽԺ��Ϣ����ϵͳ";
	string str2 = "delete from ���� where ����='";
	cout << "ȷ�ϰ����Ժ������(������ Y or N)" << endl;
	string a;
	cin >> a;
	if (a == "Y") {
		cout << "�������������ҽ���Ĺ���֤�ţ�" << endl;
		string b;
		cin >> b;
		cout << "������������֣�" << endl;
		string c;
		cin >> c;
		string str3 = str2 + c + "'";
		retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
		retcode = SQLExecDirect(hstmt, (SQLCHAR*)str1.c_str(), SQL_NTS);
		retcode = SQLExecDirect(hstmt, (SQLCHAR*)str3.c_str(), SQL_NTS);
		if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
			cout << "�����Ժ�����ɹ���" << endl;
		}
		else {
			cout << "�����Ժ����ʧ�ܣ�" << endl;
		}
	}
	else {
		cout << "��ӭ�´�ʹ��" << endl;
	}

	SQLFreeStmt(hstmt, SQL_DROP);
	system("pause");
	system("cls");
}