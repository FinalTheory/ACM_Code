/**
 * @file POJ_2623.cpp
 * @brief   数据结构，本身是要求自己实现一个堆，但是直接套用STL里面的优先队列了（以二叉堆实现）。
 * 不知道错在了哪里，可能是入队的时候没处理好，反正WA了无数次，只能说RP不行……
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-02
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

#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

priority_queue<unsigned> q;

int main()
{
	//std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int N;
	unsigned num;
	while ( scanf("%d", &N) != EOF )
	{
		int mid = N / 2 + 1;
		for ( int i = 0; i < mid; ++i )
		{
			scanf("%u", &num);
			q.push(num);
		}
		for ( int i = mid; i < N; ++i )
		{
			int tmp = q.top();
			scanf("%u", &num);
			if ( num < tmp )
			{q.pop(); q.push(num);}
		}
		double res = 0;
		res += q.top(); q.pop();
		if ( !( N % 2 ) )
		{
			res += q.top();
			res /= 2.;
			q.pop();
		}
		printf("%.1lf\n", res );
		while ( q.size() ) q.pop();
 	}
#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
