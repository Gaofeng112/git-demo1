#include<algorithm>
#include<iostream>
#define Status int
#define OK 1
#define MaxInt 32767
#define MVNum 100
using namespace std;

typedef char VerTexType;
typedef int ArcType;
typedef struct
{
	VerTexType vexs[MVNum];
	ArcType arcs[MVNum][MVNum];
	int vexnum, arcnum;
}AMGraph;
typedef struct ArcNode
{
	int adjvex;
	struct ArcNode* nextarc;
	//	OtherInfo info;
}ArcNode;
typedef struct VNode
{
	VerTexType data;
	ArcNode* firstarc;
}VNode, AdjList[MVNum];
typedef struct
{
	AdjList vertices;
	int vexnum, arcnum;
}ALGraph;

void Menu()
{
	cout << "ͼ�Ĳ���ʵ��" << endl;
	cout << "1.����ͼ�Ľ������ڽӾ���" << endl;
	cout << "2.����ͼ�Ľ������ڽӱ�" << endl;
	cout << "3.DFSͼ�ı������ڽӾ���" << endl;
	cout << "4.DFSͼ�ı������ڽӱ�" << endl;
	cout << "5.��С��������������ķ�㷨" << endl;
	cout << "6.��С������������³˹�����㷨" << endl;
	cout << "7.���·�������Ͻ�˹�����㷨" << endl;
	cout << "8.���·���������������㷨" << endl;
	cout << "0.�˳�" << endl;
	cout << "��ѡ�����";
}

int LocateVexAMG(AMGraph G, VerTexType v)
{
	for (int i = 0; i < G.vexnum; i++)
	{
		if (v == G.vexs[i])
			return i;
	}
}
int LocateVexALG(ALGraph G, VerTexType v)
{
	for (int i = 0; i < G.vexnum; i++)
	{
		if (G.vertices[i].data == v)
			return i;
	}
}

Status CreateUDN(AMGraph& G)
{
	cout << "\n�����붥�������";
	cin >> G.vexnum;
	cout << "������ߵĸ�����";
	cin >> G.arcnum;
	cout << "�����붥�����ƣ�" << endl;
	for (int i = 0; i < G.vexnum; i++)
		cin >> G.vexs[i];
	for (int i = 0; i < G.vexnum; i++)
	{
		for (int j = 0; j < G.vexnum; j++)
			G.arcs[i][j] = MaxInt;
	}
	cout << "�����붥�����Ȩ��" << endl;
	for (int k = 0; k < G.arcnum; k++)
	{
		VerTexType v1, v2;
		ArcType w;
		cin >> v1 >> v2 >> w;
		int i = LocateVexAMG(G, v1);
		int j = LocateVexAMG(G, v2);
		G.arcs[i][j] = w;
		G.arcs[j][i] = G.arcs[i][j];
	}
	return OK;
}

void PrintUDN(AMGraph G)
{
	for (int i = 0; i < G.vexnum; i++)
	{
		for (int j = 0; j < G.vexnum; j++)
			cout << G.arcs[i][j] << "\t";
		cout << endl;
	}
}

Status CreateUDG(ALGraph& G)
{
	cout << "\n�����붥�������";
	cin >> G.vexnum;
	cout << "������ߵĸ�����";
	cin >> G.arcnum;
	cout << "�����붥�����ƣ�" << endl;
	for (int i = 0; i < G.vexnum; i++)
	{
		cin >> G.vertices[i].data;
		G.vertices[i].firstarc = NULL;
	}
	cout << "����������ӵĶ��㣺" << endl;
	for (int k = 0; k < G.arcnum; k++)
	{
		VerTexType v1, v2;
		cin >> v1 >> v2;
		int i = LocateVexALG(G, v1);
		int j = LocateVexALG(G, v2);
		ArcNode* p1, * p2;
		p1 = new ArcNode;
		p1->adjvex = j;
		p1->nextarc = G.vertices[i].firstarc;
		G.vertices[i].firstarc = p1;
		p2 = new ArcNode;
		p2->adjvex = i;
		p2->nextarc = G.vertices[j].firstarc;
		G.vertices[j].firstarc = p2;
	}
	return OK;
}

void PrintUDG(ALGraph G)
{
	for (int i = 0; i < G.vexnum; i++)
	{
		ArcNode* p = G.vertices[i].firstarc;
		cout << G.vertices[i].data << "\t";
		while (p)
		{
			cout << p->adjvex << "\t";
			p = p->nextarc;
		}
		cout << endl;
	}
}

bool visited[MVNum];
void DFS_AM(AMGraph G, int v)
{
	cout << v;
	visited[v] = true;
	for (int w = 0; w < G.vexnum; w++)
	{
		if ((G.arcs[v][w] != 0) && (!visited[w]))
			DFS_AM(G, w);
	}
}

void DFS_AL(ALGraph G, int v)
{
	cout << v;
	visited[v] = true;
	ArcNode* p;
	p = G.vertices[v].firstarc;
	while (p != NULL)
	{
		int w = p->adjvex;
		if (!visited[w])
			DFS_AL(G, w);
		p = p->nextarc;
	}
}

struct
{
	VerTexType adjvex;
	ArcType lowcost;
}closeedge[MVNum];
void MiniSpanTree_Prim(AMGraph G, VerTexType u)
{
	int k = LocateVexAMG(G, u);
	for (int j = 0; j < G.vexnum; j++)
	{
		if (j != k)
			closeedge[j] = { u,G.arcs[k][j] };
	}
	closeedge[k].lowcost = 0;
	int wpl = 0;
	for (int i = 1; i < G.vexnum; i++)
	{
		int min = MaxInt;
		for (int j = 0; j < G.vexnum; j++)
		{
			if (closeedge[j].lowcost != 0 && closeedge[j].lowcost < min)
			{
				min = closeedge[j].lowcost;
				k = j;
			}
		}
		VerTexType u0, v0;
		u0 = closeedge[k].adjvex;
		v0 = G.vexs[k];
		cout << u0 << " " << v0 << " " << closeedge[k].lowcost << endl;
		wpl += closeedge[k].lowcost;
		closeedge[k].lowcost = 0;
		for (int j = 0; j < G.vexnum; j++)
		{
			if (G.arcs[k][j] < closeedge[j].lowcost)
				closeedge[j] = { G.vexs[k],G.arcs[k][j] };
		}
	}
	cout << "��С��������ȨֵΪ��" << wpl << endl;
}

struct node
{
	VerTexType Head;
	VerTexType Tail;
	ArcType lowcost;
}Edge[1000];
int Vexset[MVNum];
bool cmp(node a, node b)
{
	return a.lowcost < b.lowcost;
}
void MiniSpanTree_Kruskal(AMGraph G)
{
	int k = 0;
	for (int i = 0; i < G.vexnum; i++)
	{
		for (int j = 0; j < G.vexnum; j++)
		{
			if (G.arcs[i][j] != MaxInt)
			{
				Edge[k].Head = G.vexs[i];
				Edge[k].Tail = G.vexs[j];
				Edge[k].lowcost = G.arcs[i][j];
				k++;
			}
		}
	}
	sort(Edge, Edge + k, cmp);
	for (int i = 0; i < k; i++)
		Vexset[i] = i;
	int wpl = 0;
	for (int i = 0; i < k; i++)
	{
		int v1 = LocateVexAMG(G, Edge[i].Head);
		int v2 = LocateVexAMG(G, Edge[i].Tail);
		int vs1 = Vexset[v1];
		int vs2 = Vexset[v2];
		if (vs1 != vs2)
		{
			cout << Edge[i].Head << " " << Edge[i].Tail << " " << Edge[i].lowcost << endl;
			wpl += Edge[i].lowcost;
			for (int j = 0; j < G.vexnum; j++)
			{
				if (Vexset[j] == vs2)
					Vexset[j] = vs1;
			}
		}
	}
	cout << "��С��������ȨֵΪ��" << wpl << endl;
}

void ShortestPath_DIJ(AMGraph G, int v0)
{
	int n = G.vexnum;
	int ans = 0;
	int S[MVNum], D[MVNum], Path[MVNum];
	for (int v = 0; v < n; v++)
	{
		S[v] = false;
		D[v] = G.arcs[v0][v];
		if (D[v] < MaxInt)
			Path[v] = v0;
		else
			Path[v] = -1;
	}
	S[v0] = true;
	D[v0] = 0;
	int v, w;
	for (int i = 1; i < n; i++)
	{
		int min = MaxInt;
		for (w = 0; w < n; w++)
		{
			if (!S[w] && D[w] < min)
			{
				v = w;
				min = D[w];
			}
		}
		S[v] = true;
		for (w = 0; w < n; w++)
		{
			if (!S[w] && (D[v] + G.arcs[v][w] < D[w]))
			{
				D[w] = D[v] + G.arcs[v][w];
				Path[w] = v;
			}
		}
	}
	for (int i = 0; i < n; i++)
		cout << G.vexs[v0] << "---->" << G.vexs[i] << ":" << D[i] << endl;
}

void ShortestPath_Floyd(AMGraph G)
{
	int D[MVNum][MVNum], Path[MVNum][MVNum];
	for (int i = 0; i < G.vexnum; i++)
	{
		for (int j = 0; j < G.vexnum; j++)
		{
			D[i][j] = G.arcs[i][j];
			if (D[i][j] < MaxInt && i != j)
				Path[i][j] = i;
			else
				Path[i][j] = -1;
		}
	}
	for (int k = 0; k < G.vexnum; k++)
	{
		for (int i = 0; i < G.vexnum; i++)
		{
			for (int j = 0; j < G.vexnum; j++)
			{
				if (D[i][k] + D[k][j] < D[i][j])
				{
					D[i][j] = D[i][k] + D[k][j];
					Path[i][j] = Path[k][j];
				}
			}
		}
	}
	for (int i = 0; i < G.vexnum; i++)
	{
		for (int j = 0; j < G.vexnum; j++)
		{
			if (i != j)
				cout << G.vexs[i] << "---->" << G.vexs[j] << ":" << D[i][j] << endl;
		}
	}
}

int main()
{
	while (true)
	{
		system("cls");
		AMGraph G1;
		ALGraph G2;
		Menu();
		int x;
		cin >> x;
		switch (x)
		{
		case 1:
			if (CreateUDN(G1) == 1)
			{
				cout << "\n���ڽӾ��󴴽�����ͼ�ɹ���\n" << endl;
				cout << "\n�ڽӾ���Ϊ��\n" << endl;
				PrintUDN(G1);
			}
			else
				cout << "\n���ڽӾ��󴴽�����ͼʧ�ܣ�\n" << endl;
			break;
		case 2:
			if (CreateUDG(G2) == 1)
			{
				cout << "\n���ڽӱ�������ͼ�ɹ���\n" << endl;
				cout << "\n�ڽӱ�Ϊ��\n" << endl;
				PrintUDG(G2);
			}
			else
				cout << "\n���ڽӱ�������ͼʧ�ܣ�\n" << endl;
			break;
		case 3:
			memset(visited, false, sizeof(visited));
			int v1;
			cout << "\n��������ʼ���ţ�";
			cin >> v1;
			cout << "������ȱ����Ľ��Ϊ��\n" << endl;
			DFS_AM(G1, v1);
			cout << endl;
			break;
		case 4:
			memset(visited, false, sizeof(visited));
			int v2;
			cout << "\n��������ʼ���ţ�";
			cin >> v2;
			cout << "������ȱ����Ľ��Ϊ��\n" << endl;
			DFS_AL(G2, v2);
			cout << endl;
			break;
		case 5:
			cout << "\n��������ʼ�㣺";
			VerTexType u1;
			cin >> u1;
			cout << "�Ըõ���Ϊ��ʼ�����С������Ϊ�������һ��ΪȨֵ��" << endl;
			MiniSpanTree_Prim(G1, u1);
			break;
		case 6:
			cout << "\n��С������Ϊ�������һ��ΪȨֵ��" << endl;
			MiniSpanTree_Kruskal(G1);
			break;
		case 7:
			cout << "\n��ѡ����ʼ�㣺";
			VerTexType v0;
			cin >> v0;
			cout << "�Ӹõ����������������·��Ϊ��" << endl;
			ShortestPath_DIJ(G1, LocateVexAMG(G1, v0));
			break;
		case 8:
			cout << "\n�������㵽����������·��Ϊ��" << endl;
			ShortestPath_Floyd(G1);
			break;
		case 0:
			exit(0);
			break;
		}
		system("pause");
	}
	return 0;
}
