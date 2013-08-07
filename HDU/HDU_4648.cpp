/**
 * @file HDU_4648.cpp
 * @brief   求一个序列的连续子序列，使得去掉这个子列后的剩余元素和与原本的序列元素和对M同余。
 * 哈希思想，记录同一个模数出现的起始位置和结束位置，遍历一遍所有可能的模数，取差的最大值即可。
 * 第一次多校就这么爆零了啊，这题坑死了！
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-06
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
#define MAX 100010
#define CLR(arr,val) memset(arr,val,sizeof(arr))
typedef __int64 LL;
using namespace std;
#define INF 100000000
int nums[MAX];
int _hash[10010][2];
int N, M;

int get( int num )
{
	if ( num < 0 )
		num = ( num +  (INF / M + 1) * M ) % M;
	return num;
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
	int k;
	LL sum;
	while ( scanf("%d %d", &N, &M) != EOF )
	{
		sum = 0;
		for ( int i = 1; i <= N; ++i )
		{
			scanf("%d", &nums[i]);
			nums[i] = get(nums[i]);
		}
		CLR( _hash, -1 );
		sum = 0;
		_hash[0][0] = _hash[0][1] = 0;
		for ( int i = 1; i <= N; ++i )
		{
			sum = sum + nums[i];
			int tmp = sum % M;
			if ( _hash[tmp][0] == -1 )
				_hash[tmp][0] = _hash[tmp][1] = i;
			else
				_hash[tmp][1] = i;
		}
		int res = 0;
		for ( int i = 0; i < M; ++i )
			if ( _hash[i][0] != -1 )
				res = max( res, _hash[i][1] - _hash[i][0] );
		printf("%d\n", res);
	}
#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
