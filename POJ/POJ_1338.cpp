/**
 * @file POJ_1338.cpp
 * @brief   输入最大到1k4的范围，所以上来就直接枚举2、3、5的幂次，乘积之后排序可得。
 * 一开始以为都枚举到11次就可以了，后来发现会WA，因为指数增长的速度是不同的，最后的乘积大小会发生变化。
 * 但是如果枚举的多了的话，还要注意溢出的情况，需要把溢出的都给去掉。
 * 没注意pow的调用参数，居然CE了一发。最后3A。但是耗时实在是太难看了。
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

#define CLR(arr,val) memset(arr,val,sizeof(arr))
typedef unsigned long long ULL;
using namespace std;
ULL ans[100010];
int main()
{
	std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int n, p = 0;
	for ( int i = 0; i < 80; ++i )
		for ( int j = 0; j < 80; ++j )
			for ( int k = 0; k < 80; ++k )
			{
				ULL tmp = (ULL)pow( 2., i ) * (ULL)pow( 3., j ) * (ULL)pow( 5., k );
				if ( tmp != 0 )
					ans[p++] = tmp;
			}
	sort(ans, ans + p);
// 	for ( int i = 1; i < p; ++i )
// 		if ( ans[i] == ans[i-1] )
// 			cout << "fuck" << endl;
	while ( cin >> n && n )
		cout << ans[n - 1] << endl;
#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
