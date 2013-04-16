#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cctype>
#include <climits>
#include <ctime>
#include <vector>
#define MAX(x, y) (x) > (y) ? (x) : (y)
#define MIN(x, y) (x) < (y) ? (x) : (y)

using namespace std;
char intree[101], flag[10001];
struct TMD
{
	int a, b;
	double distance;
} islands[101];

struct TMD2
{
	int u, v;
	double w;
} bridges[10001];

bool fuck( TMD2 & A, TMD2 & B )
{
	return A.w < B.w;
}

int main()
{
	//std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int T, C, i, j, k;
	double sum;
	char changed;
	scanf("%d", &T);
	while ( T-- )
	{
		sum = 0;
		memset( islands, 0, sizeof(islands) );
		memset( bridges, 0, sizeof(bridges) );
		memset( flag, 0, sizeof(flag) );
		memset( intree, 0, sizeof(intree) );
		scanf("%d", &C);
		for ( i = 0; i < C; ++i )
			scanf("%d %d", &islands[i].a, &islands[i].b);
		k = 0;
		for ( i = 0; i < C - 1; ++i )
			for ( j = i + 1; j < C; ++j )
			{
				bridges[k].u = i;
				bridges[k].v = j;
				bridges[k].w = sqrt(double((islands[i].a-islands[j].a)*(islands[i].a-islands[j].a) + (islands[i].b-islands[j].b)*(islands[i].b-islands[j].b)));
				if ( bridges[k].w >= 10.0 && bridges[k].w <= 1000.0 )
					++k;
			}
		sort( bridges, bridges + k, fuck );
		intree[0] = changed = 1;
		while ( changed )
		{
			changed = 0;
			for ( j = 0; j < k; ++j )
			{
				if ( flag[j] )
					continue;
				if ( intree[bridges[j].u] && !intree[bridges[j].v] || !intree[bridges[j].u] && intree[bridges[j].v] )
				{
					intree[bridges[j].u] = intree[bridges[j].v] = 1;
					sum += bridges[j].w;
					flag[j] = 1;
					changed = 1;
					break;	
				}
			}
		}
		char fail = 0;
		for ( i = 0; i < C; ++i )
			if ( !intree[i] )
			{
				fail = 1;
				break;
			}
		if ( fail )
			printf( "oh!\n");
		else
			printf( "%.1lf\n", sum * 100. );
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cout << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}