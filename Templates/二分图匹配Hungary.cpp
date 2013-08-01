#define MAX 500
#define CLR(arr,val) memset(arr,val,sizeof(arr))
using namespace std;

int N, M;
int Adja[MAX+10][MAX+10];
int match[MAX+10], visited[MAX+10];

bool DFS( int u )
{
	for ( int i = 1; i <= Adja[u][0]; ++i ) 
	{
		//ö�����u���ڵ����е㣨�ڽӱ�洢��
		int v = Adja[u][i];
		if ( !visited[v] )
		{
			visited[v] = true;
			if ( match[v] == -1 || DFS( match[v] ) )
			{
				match[v] = u;
				return true;
			}
		}
	}
	return false;
}

int Hungary()
{
	int res = 0;
	CLR( match, -1 );
	for ( int u = 1; u <= N; ++u )
	{
		CLR( visited, 0 );
		if ( DFS(u) ) res++;
	}
	return res;
}

void Input()
{
	CLR( Adja, 0 );
	//�Ծ���洢�ڽӱ�
	for ( int i = 1; i <= N; ++i )
	{
		cin >> Adja[i][0];
		for ( int j = 1; j <= Adja[i][0]; ++j )
		{
			cin >> Adja[i][j];
			//ע�����������˵�ı�ţ���ʹ�㲻�ظ�
			Adja[i][j] += N;
		}
	}
}

int main()
{
	std::ios::sync_with_stdio(false);
	while ( cin >> N >> M )
	{
		Input();
		cout << Hungary() << endl;
	}
}
