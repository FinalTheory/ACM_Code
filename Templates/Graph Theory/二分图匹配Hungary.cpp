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
		//枚举与点u相邻的所有点（邻接表存储）
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
	//以矩阵存储邻接表
	for ( int i = 1; i <= N; ++i )
	{
		cin >> Adja[i][0];
		for ( int j = 1; j <= Adja[i][0]; ++j )
		{
			cin >> Adja[i][j];
			//注意这里增加了点的编号，以使点不重复
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
