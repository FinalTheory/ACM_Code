/**
 * @file POJ_1273.cpp
 * @brief   �����Edmonds-Karp�㷨ģ��
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
		//ע�������M����ڵ�����
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
			//a��¼�ӳ����㵽ÿ����֮�����С����
			CLR( a, 0 );
			//���Լ��������������޵ģ�Ȼ����������
			a[start] = INF;
			q.push(start);
			while ( !q.empty() )
			{
				//����һ��Ԫ��
				int u = q.front(); q.pop();
				//ö�����нڵ㣬���û�н��д������������ڵ�ǰ����
				for ( int v = 1; v <= M; ++v ) if ( !a[v] && cap[u][v] > flow[u][v] )
				{
					//��¼����ڵ�ĸ��ף����������
					parent[v] = u; q.push(v);
					//��������ڵ�Ĳ������丸�׽ڵ�Ĳ����͸��׽ڵ㵽����ڵ��������Сֵ
					a[v] = min( a[u], cap[u][v] - flow[u][v] );
				}
			}
			if ( a[end] == 0 ) break;
			//Ȼ�󽫲������µ�������������ȥ��ע������θ��·���ߵ�
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
