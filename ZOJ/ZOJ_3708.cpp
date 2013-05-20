/**
 * @file ZOJ_3708.cpp
 * @brief   图论水题，1A！
 * @author FinalTheory
 * @version 0.1
 * @date 2013-05-18
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
#include <vector>
#include <set>
#include <stack>
#include <sstream>
#include <iomanip>
#define MAX 500
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

char map[MAX+10][MAX+10];
int u[MAX+10], v[MAX+10];

int main()
{
	//std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int T, i, N, M, j;
	scanf("%d", &T);
	while ( T-- )
	{
		CLR(map, 0);
		int sum = 0;
		scanf("%d %d", &N, &M);
		for ( i = 0; i < M; ++i )
			scanf("%d", &u[i]);
		for ( i = 0; i < M; ++i )
			scanf("%d", &v[i]);
		for ( i = 0; i < M; ++i )
			map[u[i]][v[i]] = map[v[i]][u[i]] = 1;
		for ( i = 1; i <= N; ++i )
			for ( j = 1; j <= N; ++j )
				if ( map[i][j] ) ++sum;
		printf("%.3lf\n", (double)sum / (2*N));
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}

