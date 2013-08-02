/**
 * @file ǿ��ͨ����_Tarjan.cpp
 * @brief   Tarjan��ǿ��ͨ����ģ�档
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-01
 */
#define MAX 10000
#define CLR(arr,val) memset(arr,val,sizeof(arr))
using namespace std;
//������ڵ������Լ�ʱ�������
int LOW[MAX+10], DFN[MAX+10];
//����Ƿ���ջ��
bool Instack[MAX+10];
//��¼������ǿ��ͨ����
int Belong[MAX+10];
//ʱ�������
int TimeStamp;
//Vector�洢�ڽӱ�
vector<int> Adja[MAX+10];
//DFS������ջ
stack<int> Stack;
//����ǿ��ͨ��������
int ans;
void Tarjan( int u )
{
	int v;
	DFN[u] = LOW[u] = ++TimeStamp;
	Stack.push(u); Instack[u] = true;
	for ( int i = 0; i < Adja[u].size(); ++i )
	{
		v = Adja[u][i];
		if ( !DFN[v] )
		{
			Tarjan(v);
			LOW[u] = min( LOW[u], LOW[v] );
		}
		else if ( Instack[v] )
		{
			LOW[u] = min( LOW[u], DFN[v] );
		}
	}
	if ( DFN[u] == LOW[u] )
	{
		++ans;
		do 
		{
			v = Stack.top();
			Stack.pop();
			Instack[v] = false;
			Belong[v] = ans;
		} while ( v != u );
	}
}

int main()
{
	std::ios::sync_with_stdio(false);
	int N, M;
	while ( cin >> N >> M && M + N )
	{
		int u, v;
		for ( int i = 0; i <= N; ++i )
			Adja[i].clear();
		for ( int i = 0; i < M; ++i )
		{
			cin >> u >> v;
			Adja[u].push_back(v);
		}
		//���ֳ�ʼ��
		while ( !Stack.empty() ) Stack.pop();
		CLR( DFN, 0 ); CLR( Instack, 0 );
		TimeStamp = 0; ans = 0;
		for ( int i = 1; i <= N; ++i )
			if ( !DFN[i] )
				Tarjan(i);
		if ( ans == 1 )
			cout << "Yes\n";
		else
			cout << "No\n";
	}
}
