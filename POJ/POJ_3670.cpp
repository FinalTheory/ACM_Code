/**
 * @file HDU_3670.cpp
 * @brief   跟下一道一样，同样是LCIS衍生出来的问题。
 * 这里的数字仅有1、2、3三种，因此分别记录一下就可以了。
 * 在输入的时候同时处理升序和降序。首先如果输入了1的话显然1应该在子序列中，它的前面只有先前输入的所有1；
 * 如果输入是2的话，它的位置是1的总数（也就是上一个1的位置）和上一个2的位置中的较大者；
 * 如果输入是3的话，它的位置是1的总数、上一个2的位置和上一个3的位置中的最大者。
 * 按照顺序比较就可以减少语句次数。最后出来的代码异常简洁。
 * @author FinalTheory
 * @version 1.0
 * @date 2013-05-13
 */
#include <algorithm>
#include <cstdio>
using namespace std;
int up[4], down[4];
int main()
{
	int N, i, D;
	scanf("%d", &N);
	for ( i = 0; i < N; ++i )
	{
		scanf("%d", &D);
		if ( up[2] < up[1] )
			up[2] = up[1];
		if ( up[3] < up[2] )
			up[3] = up[2];
		if ( down[2] < down[3] )
			down[2] = down[3];
		if ( down[1] < down[2] )
			down[1] = down[2];
		up[D]++;
		down[D]++;
	}
	int maxn = -1;
	for ( i = 1; i <= 3; ++i )
		maxn = max( maxn, max( up[i], down[i] ) );
	printf("%d\n", N - maxn);
}
