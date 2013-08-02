/**
 * @file POJ_3692.cpp
 * @brief   �����������⣬������NP���⣬�����������ͼ�Ƕ���ͼ�������й�ʽ��
 * ��������=������-���ƥ����
 * ���Խ�ͼʱ����ͼ��ֱ�������������㷨�����ͼ���ƥ��Ϳ����ˡ�
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-02
 */
#include <iostream>
#include <algorithm>
#include <functional>
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
#include <queue>
#include <iomanip>
#define MAX 200
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;
int G, B, M;
bool map[MAX+10][MAX+10];
int match[MAX+10], visited[MAX+10];
bool DFS( int u )
{
	for ( int v = 1; v <= B; ++v ) if ( map[u][v] ) 
	{
		//ö�����u���ڵ����е�
		if ( !visited[v] )
		{
			visited[v] = true;
			if ( match[v] == -1 || DFS( match[v] ) )
			{
				match[v] = u;
				return true;
			}
		}
	}
	return false;
}

int Hungary()
{
	int res = 0;
	CLR( match, -1 );
	for ( int u = 1; u <= G; ++u )
	{
		CLR( visited, 0 );
		if ( DFS(u) ) res++;
	}
	return res;
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
	int u, v, idx = 1;
	while ( cin >> G >> B >> M && G + B + M )
	{
		CLR( map, 1 );
		for ( int i = 0; i < M; ++i )
		{
			cin >> u >> v;
			map[u][v] = false;
		}
		int hun = Hungary();
		printf( "Case %d: %d\n", idx++, B + G - hun );
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
