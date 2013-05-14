/**
 * @file POJ_3671.cpp
 * @brief   DP问题，注意这里是怎样处理的。
 * 这题实际上是求一个最长非降子序列，但是由于元素只有1和2，所以存在O(1)的算法。
 * 用sum1和sum2分别记录1和2的数量。每次如果输入的是1（它是最小值），那么显然这是个存在于待求子序列中的元素，而且位置必须在最后；
 * 如果输入了2，那么这个元素在待求子序列中的实际位置就要尽量靠后，它取决于前面有多少个1，以及先前2的位置.
 * 如果前面的1的数量更多，那么这个2的位置就是sum1+1；如果是先前2的位置更大的话这个2的位置就是sum2+1.
 * @author FinalTheory
 * @version 1.0
 * @date 2013-05-13
 */
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
int main()
{
	int n, i, sum1, sum2, d;
	while ( scanf("%d", &n) != EOF )
	{
		sum1 = sum2 = 0;
		for ( i = 0; i < n; ++i )
		{
			scanf("%d", &d);
			if ( d == 1 )
				sum1++;
			else
			{
				if ( sum1 > sum2 )
					sum2 = sum1 + 1;
				else
					sum2 += 1;
			}
		}
		printf("%d\n", n - max(sum1, sum2));
	}
}
