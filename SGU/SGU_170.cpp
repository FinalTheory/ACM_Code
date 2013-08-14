/**
 * @file SGU_170.cpp
 * @brief   贪心问题，注意到每匹配一个加号需要翻转两者之间的距离次，所以直接相加即可。
 * 如果加号个数都不相等，或者字符串长度都不相等，显然没有答案。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-13
 */
#if defined(__GNUC__)
#pragma GCC optimize ("O2")
#endif
#if defined(_MSC_VER)
#pragma comment(linker, "/STACK:36777216")
#endif

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
char buffer1[5010], buffer2[5010];
int main()
{
	std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	vector<int> plus_pos1, plus_pos2;
	while ( scanf("%s %s", buffer1, buffer2) != EOF )
	{
		plus_pos1.clear(); plus_pos2.clear();
		int ans = 0, len1 = strlen(buffer1), len2 = strlen(buffer2);
		if ( !strcmp( buffer1, buffer2 ) )
		{
			printf("0\n");
			continue;
		}
		if ( len1 != len2 )
		{
			puts("-1");
			continue;
		}
		for ( int i = 0; i < len1; ++i )
		{
			if ( buffer1[i] == '+' )
				plus_pos1.push_back(i);
			if ( buffer2[i] == '+' )
				plus_pos2.push_back(i);
		}
		if ( plus_pos1.size() != plus_pos2.size() )
		{
			puts("-1\n");
			continue;
		}
		for ( int i = 0; i < plus_pos1.size(); ++i )
			ans += abs( plus_pos1[i] - plus_pos2[i] );
		printf("%d\n", ans);
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
