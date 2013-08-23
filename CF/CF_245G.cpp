/**
 * @file CF_245G.cpp
 * @brief   图论题目，本质上是水题，利用STL的一个函数枚举两人的共同好友数。
 * @feeling 一开始非要用set来写，但是查找的部分写出来貌似是错的。
 *	    后来按照网上的正确答案，把写法改为vector并使用STL函数计算交集就可以了。
 *	    注意姓名个数最大是一万个，因为没注意这里又RE了一发。
 *	    总而言之，这题真是……莫名其妙。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-22
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
#define MAX 10020
#define CLR(arr,val) memset(arr,val,sizeof(arr))
using namespace std;
const int INF = 0x3f3f3f3f;
vector<int> Adja[MAX];
int buffer[MAX];
char a[MAX][30], b[MAX][30], names[MAX][30];
bool vis[MAX];
int main()
{
	std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int m, n, u, v;
	map<string, int> _map;
	map<string, int> :: iterator iter;
	string str, uu, vv;
	while ( scanf("%d", &m) != EOF )
	{
		_map.clear();
		int idx = 1;
		for ( int i = 1; i <= m; i++ )
		{
			scanf("%s %s", a[i], b[i]);
			str = a[i];
			if ( ( iter = _map.find(str) ) == _map.end() )
			{
				strcpy(names[idx], str.c_str());
				_map[str] = idx++;
			}
			str = b[i];
			if ( ( iter = _map.find(str) ) == _map.end() )
			{
				strcpy(names[idx], str.c_str());
				_map[str] = idx++;
			}
		}
		n = _map.size();
		printf("%d\n", n);
		for ( int i = 1; i <= n; ++i )
			Adja[i].clear();
		for ( int i = 1; i <= m; i++ )
		{
			uu = a[i]; vv = b[i];
			u = _map[uu]; v = _map[vv];
			Adja[u].push_back(v);
			Adja[v].push_back(u);
		}
		for ( int i = 1; i <= n; ++i )
			sort( Adja[i].begin(), Adja[i].end() );
		int _max, _ans;
		for ( u = 1; u <= n; ++u )
		{
			CLR( vis, 0 );
			_max = _ans = 0;
			printf("%s ", names[u]);
			for ( int j = 0; j < Adja[u].size(); ++j )
				vis[Adja[u][j]] = true;
			for ( int v = 1; v <= n; ++v ) if ( u != v && !vis[v] )
			{
				int tmp = set_intersection( Adja[u].begin(), Adja[u].end(), Adja[v].begin(), Adja[v].end(), buffer ) - buffer;
				if ( tmp > _max )
				{
					_ans = 1;
					_max = tmp;
				}
				else if ( tmp == _max )
				{
					_ans++;
				}
			}
			printf("%d\n", _ans);
		}
	}
#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
