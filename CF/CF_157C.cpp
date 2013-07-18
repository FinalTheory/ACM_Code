/**
 * @file CF_157C.cpp
 * @brief   字符串问题，由于添加与删除操作只允许在两端进行，因此直接从每个位置枚举，看失匹多少次即可。
 * 注意也允许从左边添加的，也就是如下面注释所述，要把目标串滑动到最开始的位置。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-07-17
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

using namespace std;

char s[2010], u[2010];

int main()
{
	std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	while ( cin >> s >> u )
	{
		int lens = strlen(s);
		int lenu = strlen(u);
		int min_res = lenu;
		//枚举起始位置
		//注意是允许从两边添加，因此要将目标串滑动到尾部与原始串开头对齐的程度。
		for ( int i = -lenu; i < lens; ++i )
		{
			int count = 0;
			for ( int j = i, k = 0; k < lenu; ++j, ++k )
			{
				if ( j < 0 || j >= lens || s[j] != u[k] )
					count++;
			}
			min_res = min( count, min_res );
		}
		cout << min_res << endl;
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
