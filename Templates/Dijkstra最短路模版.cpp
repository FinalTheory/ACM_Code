/**
 * @file HDU_1874_2.cpp
 * @brief   Dijkstra标准模版（参考白书）
 * @author FinalTheory
 * @version 1.0
 * @date 2013-04-06
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
#include <sstream>
#include <iomanip>
#define MAX 200
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
	int N, M, A, B, X, i, S, T, j;
	while ( cin >> N >> M )
	{
		CLR(map, 0x3f);
		for ( i = 0; i < M; ++i )
		{
			cin >> A >> B >> X;
			//这蛋疼题有重边！
			if ( X < map[A][B] )
				map[A][B] = map[B][A] = X;
		}
		cin >> S >> T;
		//初始化距离数组
		for ( i = 0; i < N; ++i )
			len[i] = map[S][i];
		len[S] = 0;
		CLR(visited, 0);
		for ( i = 0; i < N; ++i )
		{
			int index = INF, min = INF;
			//找到最小的节点
			for ( j = 0; j < N; ++j )
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
			for ( j = 0; j < N; ++j )
				if ( len[j] > len[index] + map[index][j] )
					len[j] = len[index] + map[index][j];
		}
		if ( len[T] < INF )
			cout << len[T] << endl;
		else
			cout << "-1\n";
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
