/**
 * @file URAL_1641.cpp
 * @brief   URAL上面的图论题，有一个小Trick略坑，比赛的时候没看出来，其实是题意都读错了。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-05
 */
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
#define MAX 110
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

bool _hash[MAX][MAX], vis[MAX];
int student[MAX];
int n, k, m;
bool is_full()
{
	int sum = 0;
	for ( int i = 1; i <= n; ++i )
		if ( vis[i] )
			sum++;
	return sum >= n - 1 ? true : false;
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
	while ( scanf("%d %d %d", &n ,&k, &m) != EOF )
	{
		CLR( _hash, 0 );
		CLR( vis, 0 );
		CLR( student, 0 );
		//分配学生
		int index = 1;
		for ( int i = 1; i <= n; ++i )
		{
			if( index <= k )
				student[i] = index;
			else
			{
				index = 1;
				student[i] = index;
			}
			index++;
			printf("%d\n", student[i]);
		}
		bool full = false;
		while ( m )
		{
			for ( int i = 1; i < n && m; ++i )
				for ( int j = i + 1; j <= n && m; ++j )
				{
					//注意Trick就在这里，如果没有满足所有学生都用过的话，就必须每次尽量用不同的学生
					if ( (full || (!vis[i] && !vis[j])) && student[i] != student[j] && !_hash[i][j] )
					{
						m--;
						printf("%d %d\n", i, j);
						_hash[i][j] = true;
						vis[i] = vis[j] = true;
					}
					full = is_full();
				}
		}
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
