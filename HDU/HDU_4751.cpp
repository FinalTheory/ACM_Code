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
bool _map[110][110];
int c[110];               //颜色，0表示还没有访问，1表示黑色，-1表示白色
int n, flag;
void dfs(int i,int color)  // 染色法判断G是否为二分图
{
	int j;
	for(j=1;j<=n;j++)
	{
		if(_map[i][j])
		{
			if(c[j]==0)
			{
				c[j]=-color;
				dfs(j,-color);
			}
			else if(c[j]==color)
			{
				flag=0;
				return;
			}
			if(flag==0)
				return;
		}
	}
}
int check()
{
	flag = 1;
	CLR(c, 0);
	for ( int i = 1; i <= n; ++i )
		if ( c[i] == 0 )
		{
			c[i] = 1;
			dfs(i, 1);
			if ( flag == 0 )
				return false;
		}
	return flag;
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
	int tmp;
	while ( scanf("%d", &n) != EOF )
	{
		CLR(_map, 0);
		for ( int i = 1; i <= n; ++i )
			while ( 1 )
			{
				scanf("%d", &tmp);
				if ( tmp == 0 ) break;
				_map[i][tmp] = true;
			}
			for ( int i = 1; i <= n; ++i )
				for ( int j = 1; j <= n; ++j )
					_map[i][j] = _map[i][j] && _map[j][i];
		for ( int i = 1; i <= n; ++i )
			for ( int j = 1; j <= n; ++j )
				_map[i][j] = !_map[i][j];
		for ( int i = 1; i <= n; ++i )
			_map[i][i] = false;
		if ( !check() )
			puts("NO");
		else
			puts("YES");
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
