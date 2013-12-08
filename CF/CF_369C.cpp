/**
 * @file main.cpp
 * @brief   记忆化DFS
 *	    首先是对所有bad边的两端染色；
 *	    然后本质上是在求一些节点的集合，它们的子树只含有一个染色节点。
 *	    这样就保证了这些节点是最后被选取的。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-12-08
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
#define MAX 100010
vector<int> Adja[MAX];
bool color[MAX];
int dp[MAX];

void DFS( int u, int prev )
{
	int v;
	if ( color[u] ) dp[u] = 1;
	else dp[u] = 0;
	for ( int i = 0; i < Adja[u].size(); ++i )
	{
		v = Adja[u][i];
		if ( v == prev ) continue;
		DFS(v, u);
		dp[u] += dp[v];
	}
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
	int k, a, b, t;
	vector<int> ans;
	cin >> k;
	for ( int i = 0; i < k - 1; ++i )
	{
		scanf("%d %d %d", &a, &b, &t);
		Adja[a].push_back(b);
		Adja[b].push_back(a);
		if ( t == 2 )
			color[a] = color[b] = true;
	}
	DFS(1, -1);
	for ( int i = 1; i <= k; ++i ) if ( dp[i] == 1 )
		ans.push_back(i);
	printf("%d\n", ans.size());
	for ( int i = 0; i < ans.size(); ++i )
	{
		if ( i ) putchar(' ');
		printf("%d", ans[i]);
	}
	puts("");
#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
