/**
 * @file POJ_1847.cpp
 * @brief   Dijkstraģ���⣬��Ȼ������ͼ�����㷨�ʹ��붼��һ���ġ�
 * ע�⽨ͼʱ�ĳ�ʼ����ÿ�еĵڶ������������ǳ�ʼ��ָ��λ�ã�����Ȩֵ���㣬ʣ�µ�Ȩֵ��1��
 * ֱ�Ӱ���ģ�棬1A��
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
		//��ʼ����������
		for ( int i = 1; i <= N; ++i )
			len[i] = map[A][i];
		len[A] = 0;
		CLR(visited, 0);
		for ( int i = 1; i <= N; ++i )
		{
			int index = INF, min = INF;
			//�ҵ���С�Ľڵ�
			for ( int j = 1; j <= N; ++j )
				if ( !visited[j] && len[j] < min )
				{
					index = j;
					min = len[index];
				}
				//��ǵ�
				if ( index != INF )
					visited[index] = 1;
				else
					break;
				//��������ڵ㣬�����б����ɳڲ���
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
