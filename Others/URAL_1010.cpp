/**
 * @file URAL_1010.cpp
 * @brief   贪心水题，题意不是很好理解。
 * 意思就是有这么一个离散函数f()，这个函数本身的输入是1~N的整数,而题目的输入数据则是函数在输入1~N的情况下的输出。
 * 核心在于要明白一个事实，就是这个函数上两点连线的最大角度，当且仅当两点相邻的时候。
 * 因为如果不相邻并且满足条件，那么两端与中间点的连线必然会产生更大的角度。
 * 假如将离散函数连续化的话，似乎可以用高数的函数凹凸性来证明这个结论。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-07-15
 */
#include <iostream>
#include <cstdint>
#define MAX 100000
#define eps 0.000001
using namespace std;
typedef long long LL;
LL height[MAX + 10];
int main()
{
	std::ios::sync_with_stdio(false);
	int N;
	while ( cin >> N )
	{
		for ( int i = 1; i <= N; ++i )
			cin >> height[i];
		LL max = INT64_MIN;
		int pos = -1;
		for ( int i = 1; i < N; ++i )
			if ( abs(height[i + 1] - height[i]) > max )
			{
				max = abs(height[i + 1] - height[i]);
				pos = i;
			}
		cout << pos << ' ' << pos + 1 << endl;
	}
}
