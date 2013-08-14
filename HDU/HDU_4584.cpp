/**
 * @file HDU_4584.cpp
 * @brief   水题，枚举1A！
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-13
 */
#if defined(__GNUC__)
#pragma GCC optimize ("O2")
#endif
#if defined(_MSC_VER)
#pragma comment(linker, "/STACK:36777216")
#endif

#include <iostream>
#include <algorithm>
#include <functional>
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
#include <queue>
#include <iomanip>

#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

char map[110][110];
const int INF = 0x3f3f3f3f;

int dist( int x1, int y1, int x2, int y2 )
{
	return abs( x1 - x2 ) + abs( y1 - y2 );
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
	int M, N, x1, y1, x2, y2, res_x1, res_y1, res_x2, res_y2;
	while ( scanf("%d %d", &M, &N) && M + N )
	{
		for ( int i = 0; i < M; ++i )
			scanf("%s", map[i]);
		int res = INF;
		for ( x1 = 0; x1 < M; ++x1 )
			for ( y1 = 0; y1 < N; ++y1 )
				for ( x2 = 0; x2 < M; ++x2 )
					for ( y2 = 0; y2 < N; ++y2 )
					{
						if ( map[x1][y1] == 'H' && map[x2][y2] == 'C' )
							if ( dist( x1, y1, x2, y2 ) < res )
							{
								res = dist( x1, y1, x2, y2 );
								res_x1 = x1;
								res_x2 = x2;
								res_y1 = y1;
								res_y2 = y2;
							}
					}
		printf("%d %d %d %d\n", res_x1, res_y1, res_x2, res_y2);
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
