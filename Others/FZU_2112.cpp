/**
 * @file FZU_2112.cpp
 * @brief   图论水题，计算度为奇数的节点再除二就可以了。
 * 不该让错误的人读题啊尼玛……
 * @author FinalTheory
 * @version 0.1
 * @date 2013-06-03
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
#define MAX 100010
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

int in[MAX];

int main()
{
	//std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int T, n, m, i, u, v, ans;
	scanf("%d", &T);
	while ( T-- )
	{
		scanf("%d %d", &n, &m);
		CLR( in, 0 );
		ans = 0;
		for ( i = 0; i < m; ++i )
		{
			scanf("%d %d", &u, &v);
			in[u]++;
			in[v]++;
		}
		for ( i = 1; i <= n; ++i )
		{
			if ( in[i] & 0x1 )
				ans++;
		}
		if ( ans > 2 )
			ans -= 2;
		else
			ans = 0;
		printf("%d\n", ans / 2);
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
