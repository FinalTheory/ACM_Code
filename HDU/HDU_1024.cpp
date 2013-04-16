/*
	经典DP问题，状态转移比较恶心，几乎是扒下来别人的思路，囧了……
	首先，定义两个状态f[i][j]和g[i][j]，其中i、j表示将前j个元素分成i部分；
	f[i][j]表示一定取第j个元素时的最大值，g[i][j]表示不一定取第j个元素时的最大值。
	所以有:f[i][j]=max{f[i][j-1], g[i-1][j-1]}+data[j]。
	表示的意思是，如果分成i段并保证取第j个元素还要得到最大值，那么可以有两种策略，一种是
	将前j-1个元素分成i段并保证取第j-1元素，这样就可以把第j个元素接到第j-1个后面。
	另一种是将前j-1个元素分成i-1段，这时可以不要求一定取第j-1个元素，因为第j个元素单独拿出来成一段。
	g[i][j]的状态转移是：g[i][j]=max{g[i][j-1], f[i][j]}
	表示的意思是，将前j个元素分成i段，如果取第j个元素的话就是f[i][j];
	如果不取的话就是将前j-1个元素分成i段，由于不要求取第j个元素所以是g[i][j-1]而不是f
	有了这两个状态转移，用滚动数组递推即可，注意是逆序，因为要保留上一层的值没有被更新。
	初始状态，j=0，因此不存在任何合法分割方式，除非分成零段。因此边界初始化为负无穷。
*/
#include <cstdio>
#define MAX 1000010
using namespace std;
int data[MAX];
long long f[MAX], g[MAX];
long long max( long long a, long long b )
{
	return a > b ? a : b;
}
int main()
{
	int m, n, i, j;
	while ( scanf("%d %d", &m, &n) != EOF )
	{
		for ( i = 1; i <= n; ++i )
			scanf( "%d", data + i );
		for ( i = 1; i <= m; ++i )
			f[i] = g[i] = -100000000000000LL;
		for ( j = 1; j <= n; ++j )
			for ( i = m; i >= 1; --i )
			{
				f[i] = max( f[i], g[i-1] ) + data[j];
				g[i] = max( g[i], f[i] );
			}
		printf("%lld\n", g[m]);
	}
}