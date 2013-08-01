/**
 * @file POJ_1273.cpp
 * @brief   最大流Edmonds-Karp算法模版
 * @author FinalTheory
 * @version 0.1
 * @date 2013-07-31
 */
#define MAX 200
#define INF 0x7fffffff
#define CLR(arr,val) memset(arr,val,sizeof(arr))
using namespace std;
int cap[MAX+10][MAX+10], flow[MAX+10][MAX+10], a[MAX+10];
int parent[MAX+10];
int main()
{
	std::ios::sync_with_stdio(false);
	int N, M, uu, vv, c, start, end;
	queue<int> q;
	while ( cin >> N >> M )
	{
		//注意此题中M代表节点数。
		while ( !q.empty() ) q.pop();
		CLR( cap, 0 ); CLR( flow, 0 );
		start = 1; end = M;
		for ( int i = 0; i < N; ++i )
		{
			cin >> uu >> vv >> c;
			cap[uu][vv] += c;
		}
		unsigned long long max_flow = 0;
		for (;;)
		{
			//a记录从出发点到每个点之间的最小残量
			CLR( a, 0 );
			//到自己的最大残量是无限的，然后将其加入队列
			a[start] = INF;
			q.push(start);
			while ( !q.empty() )
			{
				//出队一个元素
				int u = q.front(); q.pop();
				//枚举所有节点，如果没有进行处理并且容量大于当前流量
				for ( int v = 1; v <= M; ++v ) if ( !a[v] && cap[u][v] > flow[u][v] )
				{
					//记录这个节点的父亲，并加入队列
					parent[v] = u; q.push(v);
					//到达这个节点的残量是其父亲节点的残量和父亲节点到这个节点残量的最小值
					a[v] = min( a[u], cap[u][v] - flow[u][v] );
				}
			}
			if ( a[end] == 0 ) break;
			//然后将残量更新到现有流量上面去，注意是如何更新反向边的
			for ( int u = end; u != start; u = parent[u] )
			{
				flow[parent[u]][u] += a[end];
				flow[u][parent[u]] -= a[end];
			}
			max_flow += a[end];
		}
		cout << max_flow << endl;
	}
}
