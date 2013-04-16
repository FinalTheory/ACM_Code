/*
	标准的并查集，首先输入所有道路信息并排序。
	遍历每一个道路的两端，如果它们的根相同则继续，否则连接两者的根。
	完成遍历后遍历所有村庄编号，如果它们的根不是1则说明没有全部连通，输出'?'。
	一次AC，耗时0MS，很爽！。
*/
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cctype>
#include <climits>
#include <ctime>
#define MAX(x, y) (x) > (y) ? (x) : (y)
#define MIN(x, y) (x) < (y) ? (x) : (y)
#define SWAP(x, y) (x) ^= (y) ^= (x) ^= (y)
#define SIZE 105
using namespace std;
int set[SIZE];
struct TMD
{
	int A, B, cost;
} roads[5000];
bool fuck( TMD A, TMD B )
{
	if ( A.cost != B.cost )
		return A.cost < B.cost;
	else if ( A.A != B.A )
		return A.A < B.A;
	else
		return A.B < B.B;
}
int find( int x )
{
	int r = x, i = x, j;
	while ( set[r] != r )
		r = set[r];
	while ( i != r )
	{
		j = set[i];
		set[i] = r;
		i = j;
	}
	return r;
}
void merge( int a, int b )
{
	if ( a < b )
		set[b] = a;
	else
		set[a] = b;
}
int main()
{
	std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int N, M, i, sum, root_a, root_b;
	char all_connected;
	while ( cin >> N >> M && N )
	{
		sum = 0;
		all_connected = 1;
		for ( i = 0; i <= M; i++ )
			set[i] = i;
		for ( i = 0; i < N; i++ )
			cin >> roads[i].A >> roads[i].B >> roads[i].cost;
		sort(roads, roads + N, fuck);
		for ( i = 0; i < N; i++ )
		{
			root_a = find( roads[i].A );
			root_b = find( roads[i].B );
			if ( root_a != root_b )
			{
				merge( root_a, root_b );
				sum += roads[i].cost;
			}
		}
		for ( i = 1; i <= M; i++ )
		{
			if ( find( i ) != 1 )
			{
				all_connected = 0;
				break;
			}
		}
		if ( all_connected )
			cout << sum << '\n';
		else
			cout << "?\n";
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cout << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}