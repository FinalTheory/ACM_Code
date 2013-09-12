/**
 * @file POJ_1273.cpp
 * @brief   最大流ISAP算法模版
 * @author FinalTheory
 * @version 0.1
 * @date 2013-09-06
 */
#define MAX_v 210
#define MAX_e 410
#define CLR(arr,val) memset(arr,val,sizeof(arr))
typedef long long LL;
using namespace std;
const int INF = 0x3f3f3f3f;

//邻接表存储图
int from[MAX_e], to[MAX_e], cap[MAX_e], flow[MAX_e], head[MAX_v], next_e[MAX_e];
//到汇点的距离，某个点的前驱、间隙优化时记录到汇点距离为n的节点个数，对于某个节点已经处理到的邻接边
int dist[MAX_v], pre[MAX_v], gap[MAX_v], cur[MAX_v];
bool vis[MAX_v];
int p_edges;
void Add_Edge( int _u, int _v, int _cap )
{
	from[p_edges] = _u; to[p_edges] = _v;
	cap[p_edges] = _cap; flow[p_edges] = 0;
	next_e[p_edges] = head[_u];
	head[_u] = p_edges++;
	from[p_edges] = _v;to[p_edges] = _u;
	cap[p_edges] = 0; flow[p_edges] = 0;
	next_e[p_edges] = head[_v];
	head[_v] = p_edges++;
}

//定义源点、汇点
int Src, Dst;
bool BFS()
{
	CLR(vis, 0);
	queue<int> Q;
	Q.push(Dst);
	vis[Dst] = true;
	dist[Dst] = 0;
	int u, v, e;
	while ( !Q.empty() )
	{
		u = Q.front(); Q.pop();
		for ( e = head[u]; e != -1; e = next_e[e] ) if ( !vis[to[e]] )
		{
			vis[to[e]] = true;
			dist[to[e]] = dist[u] + 1;
			Q.push(to[e]);
		}
	}
	return vis[Src];
}
//增广
int Augment()
{
	int u = Dst, cur_flow = INF, e;
	while ( u != Src )
	{
		e = pre[u];
		cur_flow = min( cur_flow, cap[e] - flow[e] );
		u = from[e];
	}
	u = Dst;
	while ( u != Src )
	{
		e = pre[u];
		flow[e] += cur_flow;
		flow[e^1] -= cur_flow;
		u = from[e];
	}
	return cur_flow;
}

int ISAP( int num_nodes )
{
	int max_flow = 0;
	BFS();
	CLR( gap, 0 );
	memcpy( cur, head, sizeof(head) );
	for ( int i = 1; i <= num_nodes; ++gap[dist[i++]] );
	int u = Src, e;
	bool Advanced = false;
	while ( dist[Src] < num_nodes )
	{
		if ( u == Dst )
		{
			max_flow += Augment();
			u = Src;
		}
		Advanced = false;
		for ( e = cur[u]; e != -1; e = next_e[e] ) if ( cap[e] > flow[e] && dist[u] == dist[to[e]] + 1 )
		{
			Advanced = true;
			cur[u] = e;
			pre[to[e]] = e;
			u = to[e];
			break;
		}
		//Retreat操作
		if ( !Advanced )
		{
			int _min = num_nodes - 1;
			for ( e = head[u]; e != -1; e = next_e[e] ) if ( cap[e] > flow[e] )
				_min = min( _min, dist[to[e]] );
			if ( --gap[dist[u]] == 0 ) break;	//GAP优化
			gap[dist[u] = _min + 1]++;
			cur[u] = head[u];
			if ( u != Src )
				u = from[pre[u]];
		}
	}
	return max_flow;
}
