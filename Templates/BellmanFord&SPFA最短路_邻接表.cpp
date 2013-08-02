/**
 * @file BellmanFord���·_�ڽӱ�.cpp
 * @brief   Bellman_Ford�㷨ģ�棬�ο����顣
 *	    ʹ����FIFO�����Ż�������νSPFA��
 * @author FinalTheory
 * @version 1.0
 * @date 2013-08-02
 */
#define MAX 10000
#define MAX_p 100
#define INF 0x3f3f3f3f
#define CLR(arr,val) memset(arr,val,sizeof(arr))
using namespace std;
typedef pair<int, int> TMD;
int u[MAX+10], v[MAX+10], w[MAX+10], head[MAX_p+10], next_e[MAX+10], d[MAX_p+10];
bool in_queue[MAX_p+10];
queue<int> q;
int N, M, S, T;

void Bellman_Ford()
{
	int x, y;
	CLR( d, 0x3f );
	d[S] = 0;
	for ( int k = 0; k < N - 1; ++k )			//ѭ��N - 1��
		for ( int e = 0; e < M * 2; ++e )	//���ÿ����
		{
			x = u[e], y = v[e];
			if ( d[x] < INF && d[y] > d[x] + w[e] )
				d[y] = d[x] + w[e];
		}
}
//�������SPFA
void Bellman_Ford_With_FIFO()
{
	CLR( d, 0x3f ); d[S] = 0;
	CLR( in_queue, 0 );
	q.push(S); in_queue[S] = true;
	while ( !q.empty() )
	{
		int p = q.front(); q.pop();
		in_queue[p] = false;
		for ( int e = head[p]; e != -1; e = next_e[e] ) if ( d[v[e]] > d[p] + w[e] )
		{
			d[v[e]] = d[p] + w[e];
			//������ɳڹ��ĵ㲻�ڶ����У��ͼ������
			if ( !in_queue[v[e]] )
			{
				in_queue[v[e]] = true;
				q.push(v[e]);
			}
		}
	}
}

int main()
{
	std::ios::sync_with_stdio(false);
	while ( cin >> N >> M && M + N )
	{
		CLR( head, -1 );
		CLR( next_e, -1 );
		//��ͼ���֣�ע�⣡
		for ( int i = 0; i < 2 * M; i += 2 )
		{
			cin >> u[i] >> v[i] >> w[i];
			next_e[i] = head[u[i]];
			head[u[i]] = i;
			u[i+1] = v[i]; v[i+1] = u[i]; w[i+1] = w[i];
			next_e[i+1] = head[u[i+1]];
			head[u[i+1]] = i + 1;
		}
		//cin >> S >> T;
		S = 1; T = N;
		//Bellman_Ford();
		Bellman_Ford_With_FIFO();
		cout << ( d[T] < INF ? d[T] : -1 ) << endl;
	}
}
