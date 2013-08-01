/**
 * @file POJ_1847.cpp
 * @brief   Dijkstra模版题，虽然是有向图但是算法和代码都是一样的。
 * 注意建图时的初始化，每行的第二个输入数据是初始的指向位置，所以权值是零，剩下的权值是1。
 * 直接扒了模版，1A。
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
#define MAX 100
#define INF 0x3f3f3f3f
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

int map[MAX+10][MAX+10];
int len[MAX+10];
char visited[MAX+10];

int main()
{
	std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int N, A, B, K, node;
	while ( cin >> N >> A >> B )
	{
		CLR(map, 0x3f);
		for ( int i = 1; i <= N; ++i )
		{
			cin >> K;
			for ( int j = 0; j < K; ++j )
			{
				cin >> node;
				map[i][node] = j ? 1 : 0;
			}
		}
		//初始化距离数组
		for ( int i = 1; i <= N; ++i )
			len[i] = map[A][i];
		len[A] = 0;
		CLR(visited, 0);
		for ( int i = 1; i <= N; ++i )
		{
			int index = INF, min = INF;
			//找到最小的节点
			for ( int j = 1; j <= N; ++j )
				if ( !visited[j] && len[j] < min )
				{
					index = j;
					min = len[index];
				}
				//标记掉
				if ( index != INF )
					visited[index] = 1;
				else
					break;
				//利用这个节点，对所有边做松弛操作
				for ( int j = 1; j <= N; ++j )
					if ( len[j] > len[index] + map[index][j] )
						len[j] = len[index] + map[index][j];
		}
		if ( len[B] < INF )
			cout << len[B] << endl;
		else
			cout << "-1\n";
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
