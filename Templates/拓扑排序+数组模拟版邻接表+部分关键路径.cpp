/**
 * @file Сǿ��Linux.cpp
 * @brief   ����������º�̽ڵ�����ʱ����������̿�ʼʱ�䡣
 * ʹ���˰����ϵ�����ģ���������ڽӱ�洢ͼ��
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
//���ÿ���ڵ��ʱ��
int t[MAX+10];
//ÿ���ڵ�����翪ʼʱ��
int start_time[1010];
//��¼�ߵ����
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
		//���ʾ��ָ��
		CLR( head, 0 );
		CLR( next_edge, 0 );
		while ( !res.empty() ) res.pop();

		for ( i = 1; i <= N; ++i )
			cin >> t[i];
		cin >> M;
		for ( i = 1; i <= M; ++i )
		{
			//����һ��r2->r1�ı�
			cin >> r1 >> r2;
			v[i] = r1;
			next_edge[i] = head[r2];
			head[r2] = i;
		}
		//������ȣ�ö�����е�
		for ( i = 1; i <= N; ++i )
		{
			h = head[i];
			while ( h )
			{
				++in[v[h]];
				h = next_edge[h];
			}
		}
		//���������Ϊ��ĵ�ѹ��ջ
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
				//���º�̽ڵ�����絽��ʱ��
				if ( start_time[index] + t[index] > start_time[v[h]] )
					start_time[v[h]] = start_time[index] + t[index];
				//��ȼ�Ϊ��Ļ�����ջ
				if ( !in[v[h]] )
					res.push(v[h]);
				h = next_edge[h];
			}
		}
		//ѡȡ����ʱ�䣬�ǵ�Ҫ����û�д��������ڵ㡣
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
