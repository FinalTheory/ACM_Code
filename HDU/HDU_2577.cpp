/**
 * @file HDU_2577.cpp
 * @brief   简单DP问题，注意状态转移方程的巧妙设计。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-05-21
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
int main()
{
	std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int T, len, i;
	char buffer[150];
	//ON、OFF分别表示在某一步完成后大写锁定开/关时所需要的敲击数
	int ON[150], OFF[150];
	scanf("%d", &T);
	while ( T-- )
	{
		CLR(ON, 0); CLR(OFF, 0);
		ON[0] = 1;
		scanf("%s", buffer + 1);
		len = strlen(buffer+1);
		for ( i = 1; i <= len; ++i )
		{
			//如果当前是大写字母
			if ( buffer[i] >= 'A' && buffer[i] <= 'Z' )
			{
				//如果先前大写锁定是关闭的，那么变动到当前打开的状态就需要加2；如果也是打开的加1就可以了。
				//当然是从两者中选取最小值，后面的步骤同理。
				ON[i] = min( OFF[i-1] + 2, ON[i-1] + 1 );
				OFF[i] = min( OFF[i-1] + 2, ON[i-1] + 2 );
			}
			else
			{
				ON[i] = min( OFF[i-1] + 2, ON[i-1] + 2 );
				OFF[i] = min( OFF[i-1] + 1, ON[i-1] + 2 );
			}
		}
		printf("%d\n", min(ON[i-1]+1, OFF[i-1]));
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
