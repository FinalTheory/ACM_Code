/**
 * @file ZOJ_3710.cpp
 * @brief   还是图论水题
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
#define MAX 100
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

char map[MAX+10][MAX+10];

int main()
{
	std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int T, n, m, i, u, v, j, k, c, res;
	scanf("%d", &T);
	while ( T-- )
	{
		res = 0;
		CLR(map, 0);
		scanf("%d %d %d", &n, &m, &c);
		for ( i = 0; i < m; ++i )
		{
			scanf("%d %d", &u, &v);
			map[u][v] = map[v][u] = 1;
		}
		char flag = 1;
		while (flag)
		{
			flag = 0;
			for ( i = 0; i < n - 1; ++i )
				for ( j = i + 1; j < n; ++j )
					if ( !map[i][j] )
					{
						int sum = 0;
						for ( k = 0; k < n; ++k )
							if ( k != i && k != j && map[i][k] && map[k][j] )
								sum++;
						if ( sum >= c )
						{
							res++;
							map[i][j] = map[j][i] = 1;
							flag = 1;
						}
					}
		}
		printf("%d\n", res);
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}

