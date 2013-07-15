/**
 * @file URAL_1118.cpp
 * @brief   利用类似筛法的思想来求出范围内（1~10^6）的所有数的因子之和，然后遍历查询就可以了。
 * 题目如果没有特别强调查询次数的话，应该是数据规模不大的意思。
 * 这题的查询如果改用线段树的话，加上建树的开销说不定要多用几倍的时间……
 * @author FinalTheory
 * @version 0.1
 * @date 2013-07-15
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
#define MAX 1000000
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

int ans[MAX + 10];

int main()
{
	std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	//求所有数的因子之和，核心代码就是这三行！
	for ( int i = 1; i <= MAX; ++i )
		for ( int j = i * 2; j <= MAX; j += i )
			ans[j] += i;
	int I, J;
	while ( cin >> I >> J )
	{
		int pos = -1;
		double min = 1000.;
		for ( int i = I; i <= J; ++i )
			if ( (double)ans[i] / i < min )
			{
				min = (double)ans[i] / i;
				pos = i;
			}
		cout << pos << endl;
	}
#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
