/*
	01�������⣬�������ݹ�ģ�൱�󣬱�����пռ临�Ӷ��Ż�������MLE���Ż��汾��ע�͵��ˡ�
	ע��������ѭ������һ���Ǵӵ�һ����Ʒ�����һ����Ʒ�������ڿ�����������µ�����ֵ��
	�ڶ���ѭ������������������������Ż��ռ临�ӶȵĻ�˳��Ҳ���ԡ�����������Ҫ�ֶ�������һ���ȸ��Ƶ����档
	���Ǵӵ�i����Ʒ��������ϼӣ�Ȼ���ڵ�ǰ��Ӧ������µ�����ֵ��
	�������������Ʒ�����һ���Ӧ�����󣩼�Ϊ����ֵ��
*/
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <time.h>
#define MAX(x, y) (x) > (y) ? (x) : (y)
using namespace std;
int DP[3500][13000];
//int DP[13000];
int main()
{
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int N, M, W[3500], D[3500], i, v;
	while ( cin >> N >> M )
	{
		for ( i = 1; i <= N; i++ )
			cin >> W[i] >> D[i];
		for ( i = 1; i <= N; i++ )
		{
			for ( v = 0; v <= M; v++ )
				DP[i][v] = DP[i-1][v];
			for ( v = W[i] ; v <= M; v++ )
				//DP[v] = MAX( DP[v], DP[v-W[i]] + D[i] );
				DP[i][v] = MAX( DP[i-1][v], DP[i-1][v-W[i]] + D[i] );
		}
		cout << DP[N][M] << endl;
		//cout << DP[M] << endl;
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cout << ( program_end - program_start ) << " MS" << endl;
#endif
}