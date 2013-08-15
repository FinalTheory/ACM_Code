/**
 * @file CF_244B.cpp
 * @brief   深度优先搜索，注意这种找规律的方法，在输入不是很规整的时候。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-15
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
#define CLR(arr,val) memset(arr,val,sizeof(arr))
using namespace std;
const int INF = 0x3f3f3f3f;
set<int> S;
int x, y, n;
typedef long long LL;
void DFS( LL a, int d )
{
	if ( a > n || d > 10 )
		return;
	S.insert(a);
	DFS( a * 10 + x, d + 1 );
	DFS( a * 10 + y, d + 1 );
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
	while ( cin >> n )
	{
		S.clear();
		for ( x = 0; x <= 9; ++x )
			for ( y = 0; y <= 9; ++y )
				DFS(0, 0);
		cout << S.size() - 1 << endl;
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
