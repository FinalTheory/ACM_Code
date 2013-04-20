/**
 * @file 小强的Linux.cpp
 * @brief   拓扑排序更新后继节点的入度时，更新其最短开始时间。
 * 使用了白书上的数组模拟链表以邻接表存储图。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-04-20
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
#include <stack>
#define MAX 499500
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;
//完成每个节点的时间
int t[MAX+10];
//每个节点的最早开始时间
int start_time[1010];
//记录边的情况
int next_edge[MAX+10], v[MAX+10];
int head[1010];
int in[1010];


int main()
{
	std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int N, i, r1, r2, M, j, h;
	stack<int> res;
	while ( cin >> N )
	{
		CLR( t, 0 );
		CLR( in, 0 );
		CLR( start_time, 0 );
		//零表示空指针
		CLR( head, 0 );
		CLR( next_edge, 0 );
		while ( !res.empty() ) res.pop();

		for ( i = 1; i <= N; ++i )
			cin >> t[i];
		cin >> M;
		for ( i = 1; i <= M; ++i )
		{
			//这是一条r2->r1的边
			cin >> r1 >> r2;
			v[i] = r1;
			next_edge[i] = head[r2];
			head[r2] = i;
		}
		//计算入度，枚举所有点
		for ( i = 1; i <= N; ++i )
		{
			h = head[i];
			while ( h )
			{
				++in[v[h]];
				h = next_edge[h];
			}
		}
		//将所有入度为零的点压入栈
		for ( i = 1; i <= N; ++i )
			if ( !in[i] )
				res.push(i);
		int index;
		while ( !res.empty() )
		{
			index = res.top();
			res.pop();
			h = head[index];
			while ( h )
			{
				--in[v[h]];
				//更新后继节点的最早到达时间
				if ( start_time[index] + t[index] > start_time[v[h]] )
					start_time[v[h]] = start_time[index] + t[index];
				//入度减为零的话就入栈
				if ( !in[v[h]] )
					res.push(v[h]);
				h = next_edge[h];
			}
		}
		//选取最大的时间，记得要加上没有处理的这个节点。
		int max = -1;
		for ( i = 1; i <= N; ++i )
			if ( start_time[i] + t[i] > max )
				max = start_time[i] + t[i];
		cout << max << endl;
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
