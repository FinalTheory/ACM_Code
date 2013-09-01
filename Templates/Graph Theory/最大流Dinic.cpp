/**
 * @file POJ_1273.cpp
 * @brief   最大流Dinic算法模版
 * @input   邻接表存储的有向图
 * @output  函数返回最大流的数值
 * @hint    注意是否存在重边，每次调用之前清空邻接表。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-30
 */
#define MAX 410
#define MAX_p 210
#define CLR(arr,val) memset(arr,val,sizeof(arr))
using namespace std;
typedef long long LL;
const int INF = 0x7fffffff;
//邻接矩阵，用于去重
int _map[MAX_p][MAX_p];
//邻接表存储图
int to[MAX], cap[MAX], head[MAX_p], next_e[MAX];
//记录分层图
int dist[MAX_p];
//源点、汇点
int Src, Dst;

int p_edges;
void Add_Edge( int _u, int _v, int _cap )
{
	to[p_edges] = _v; cap[p_edges] = _cap;
	next_e[p_edges] = head[_u];
	head[_u] = p_edges++;
	to[p_edges] = _u; cap[p_edges] = 0;
	next_e[p_edges] = head[_v];
	head[_v] = p_edges++;
}

//BFS构建分层图
bool BFS()
{
	int u, v;
	queue<int> q;
	while ( !q.empty() ) q.pop();
	CLR( dist, -1 ); dist[Src] = 0; q.push(Src);
	while ( !q.empty() )
	{
		u = q.front(); q.pop();
		for ( int i = head[u]; i != -1; i = next_e[i] )
		{
			v = to[i];
			if ( cap[i] > 0 && dist[v] == -1 )
			{
				dist[v] = dist[u] + 1;
				q.push(v);
			}
		}
	}
	return dist[Dst] != -1;
}
//按照分层图DFS找出一条增广路
int DFS( int u, int low )
{
	if ( u == Dst )
		return low;
	int tmp, v;
	for ( int i = head[u]; i != -1; i = next_e[i] )
	{
		v = to[i];
		if ( cap[i] > 0 && dist[v] == dist[u] + 1 && ( tmp = DFS( v, min( low, cap[i] ) ) ) )
		{
			cap[i] -= tmp;
			cap[i^1] += tmp;
			return tmp;
		}
	}
	dist[u] = -1;
	return 0;
}

LL Dinic()
{
	LL max_flow = 0, tmp;
	while ( BFS() )
	{
		while (true)
		{
			tmp = DFS( Src, INF );
			if ( tmp == 0 ) break;
			max_flow += tmp;
		}
	}
	return max_flow;
}

int main()
{
	int N, M, S, E, C;
	while ( scanf("%d %d", &M, &N) != EOF )
	{
		//初始化邻接表
		p_edges = 0;
		CLR( head, -1 ); CLR( next_e, -1 );
		//初始化邻接矩阵(用于去重)
		CLR( _map, 0 );
		for ( int i = 0; i < M; ++i )
		{
			scanf("%d %d %d", &S, &E, &C);
			_map[S][E] += C;
		}
		//建图部分
		for ( int i = 1; i <= N; ++i )
			for ( int j = 1; j <= N; ++j ) if ( _map[i][j] )
				Add_Edge( i, j, _map[i][j] );
		Src = 1; Dst = N;
		printf("%lld\n", Dinic());
		//cout << Dinic() << endl;
	}
}
