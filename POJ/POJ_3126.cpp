/**
 * @file POJ_3126.cpp
 * @brief   BFS问题，本来偷懒用队列实现BFS，但是发现非常难以记录搜索深度。
 * 思路是每次扩展当前的所有素数，然后标记掉已经访问过的就可以了。
 * 迫不得已改用递归形式的BFS，事实证明非常有效，干净利落地1A。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-07-18
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
#include <queue>
#define MAX 10000
#define INF 0x3f3f3f3f
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

bool prime[MAX+10];
bool visited[10010];

int prev_num[MAX + 10], now[MAX + 10], p_prev, p_now;
int src, dst, ans;
char buffer[10], num[10];

void BFS( int depth )
{
	int new_num;
	p_now = 0;
	for ( int i = 0; i < p_prev; ++i )
	{
		sprintf(buffer, "%d", prev_num[i]);
		for ( int pos = 0; pos < 4; ++pos )
		{
			strcpy( num, buffer );
			for ( char c = '0'; c <= '9'; ++c )
			{
				num[pos] = c;
				sscanf( num, "%d", &new_num );
				if ( new_num == dst )
				{
					ans = depth + 1;
					return;
				}
				if ( new_num >= 1000 && prime[new_num] && !visited[new_num] )
				{
					visited[new_num] = 1;
					now[p_now++] = new_num;
				}
			}
		}
	}
	memcpy( prev_num, now, sizeof(now) );
	p_prev = p_now;
	if ( p_now )
		BFS(depth+1);
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
	int t;
	cin >> t;
	memset( prime, 1, sizeof(prime) );
	for ( int i = 2; i <= MAX; ++i )
		if ( prime[i] )
			for ( int j = 2 * i; j <= MAX; j += i )
				prime[j] = 0;
	while ( t-- )
	{
		CLR(visited, 0);
		cin >> src >> dst;
		if ( src == dst )
		{
			cout << "0" << endl;
			continue;
		}
		p_prev = 1;
		prev_num[0] = src;
		BFS(0);
		cout << ans << endl;
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
