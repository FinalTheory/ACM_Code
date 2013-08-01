/**
 * @file HDU_1642.cpp
 * @brief   拓扑排序水题，为了保证答案不唯一时输出按照升序，使用优先队列。
 * 注意这个里面是怎么建立一个从小到大排序的优先队列的。
 * 输入数据有重边，WA了一发。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-07-30
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
#include <functional>

#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

char map[510][510];
int in[510];
bool visited[510];
int main()
{
	std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int N, M, u, v, cur;
	priority_queue<int, vector<int>, greater<int> > result;
	while ( cin >> N >> M )
	{
		while ( !result.empty() ) result.pop();
		CLR(map, 0); CLR(in, 0); CLR(visited, 0);
		for ( int i = 0; i < M; ++i )
		{
			cin >> u >> v;
			if ( !map[u][v] )
			{
				map[u][v] = 1;
				++in[v];
			}
		}
		for ( int i = 1; i <= N; ++i )
			if ( !in[i] )
			{
				result.push(i);
				visited[i] = 1;
			}
		bool outed = false;
		while ( !result.empty() )
		{
			cur = result.top();
			result.pop();
			if ( outed ) cout << ' ';
			else outed = true;
			cout << cur;
			for ( int i = 1; i <= N; ++i ) if ( !visited[i] )
			{
				if ( map[cur][i] )
					--in[i];
				if ( !in[i] )
				{
					result.push(i);
					visited[i] = 1;
				}
			}
		}
		cout << endl;
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
