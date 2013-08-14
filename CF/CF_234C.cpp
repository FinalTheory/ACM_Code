/**
 * @file CF_234C.cpp
 * @brief   记录每个点的左右各有多少个负数，然后枚举一遍所有点；
 * 这时考虑如果从这个点分割序列，需要有多少次修改。O(n)时间可以完成，但是要注意边界处理。
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
#include <sstream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <bitset>
#include <stack>
#include <queue>
#include <deque>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cctype>
#include <climits>
#include <ctime>
#define MAX 100010
#define CLR(arr,val) memset(arr,val,sizeof(arr))
using namespace std;
const int INF = 0x3f3f3f3f;
int temp[MAX], nega[MAX][2];

int main()
{
	std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#else
	freopen( "input.txt", "r", stdin );
	freopen( "output.txt", "w", stdout );
#endif
	int n;
	while ( scanf("%d", &n) != EOF )
	{
		for ( int i = 1; i <= n; ++i )
			scanf("%d", &temp[i]);
		nega[n + 1][1] = 0;
		for ( int i = 1, j = n; i <= n; ++i, --j )
		{
			nega[i][0] = nega[i - 1][0];
			nega[j][1] = nega[j + 1][1];
			if ( temp[i] < 0 )
				++nega[i][0];
			if ( temp[j] <= 0 )
				++nega[j][1];
		}
		int ans = INF;
		for ( int i = 2; i <= n; ++i )
			ans = min( ans, i - 1 - nega[i - 1][0] + nega[i][1] );
		printf("%d\n", ans);
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
