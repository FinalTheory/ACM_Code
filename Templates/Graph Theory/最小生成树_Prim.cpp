/**
 * @file 最小生成树_Kruskal.cpp
 * @brief  标准模版。 
 * @author FinalTheory
 * @version 0.1
 * @date 2013-06-04
 */
#define MAX(x, y) (x) > (y) ? (x) : (y)
#define MIN(x, y) (x) < (y) ? (x) : (y)

using namespace std;

struct TMD
{
	int u, v, w;
} roads[10001];

bool fuck( TMD & A, TMD & B )
{
	return A.w < B.w;
}

char intree[101], flag[10001];

int main()
{
	std::ios::sync_with_stdio(false);
	int N, i, j, sum;
	char changed;
	while ( cin >> N )
	{
		if ( !N )
			break;
		if ( N == 1 )
		{
			cout << "0\n";
			continue;
		}
		memset(roads, 0, sizeof(roads));
		memset( intree, 0, sizeof(intree) );
		memset( flag, 0, sizeof(flag) );
		sum = 0;
		for ( i = 0; i < N*(N-1)/2; ++i )
			cin >> roads[i].u >> roads[i].v >> roads[i].w;
		sort( roads, roads + i, fuck );
		intree[1] = changed = 1;
		while ( changed )
		{
			changed = 0;
			for ( j = 0; j < i; ++j )
			{
				if ( flag[j] )
					continue;
				if ( intree[roads[j].u] && !intree[roads[j].v] || !intree[roads[j].u] && intree[roads[j].v] )
				{
					intree[roads[j].u] = intree[roads[j].v] = 1;
					sum += roads[j].w;
					flag[j] = 1;
					changed = 1;
					break;	
				}
			}
		}
		cout << sum << '\n';
	}
}
