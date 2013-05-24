/**
 * @file HDU_1087.cpp
 * @brief   DP问题，跟最长上升子列有点像，这个是求最大上升子列和。
 * 首先注意初始化的问题，DP数组应该初始化为原本那个输入的数组；
 * 这个里面的DP并没有非常明显的含义，对于后面比前面大的地方更新了最大和，但是不满足条件的就没有进行处理。
 * 这样的话不满足的情况就记录了原值，满足的话更新为max(DP[i], DP[j]+num[i])
 * 这样设计的状态导致了最后求答案的时候是遍历一遍DP数组找出其中的最大值。
 * 一开始初始化部分没想明白，郁闷~~
 * @author FinalTheory
 * @version 0.1
 * @date 2013-05-22
 */
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#define CLR(arr,val) memset(arr,val,sizeof(arr))
using namespace std;
long long DP[1010], num[1010];
int main()
{
	int N, i, j;
	while ( scanf("%d", &N) && N )
	{
		CLR(DP, 0);
		for ( i = 1; i <= N; ++i )
		{
			scanf("%lld", &num[i]);
			DP[i] = num[i];
		}
		for ( i = 1; i <= N; ++i )
			for ( j = 1; j < i; ++j )
			{
				if ( num[i] > num[j] )
					DP[i] = max( DP[i], DP[j] + num[i] );
			}
		int ans = -1000000;
		for ( i = 1; i <= N; ++i )
			if ( DP[i] > ans ) ans = DP[i];
		printf("%lld\n", ans);
	}
}
