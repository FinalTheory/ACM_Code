/**
 * @file POJ_1936.cpp
 * @brief   水题，判断一个序列是否为另外一个序列的子列。
 * 思想就是，如果是子列的话，相同元素出现的位置相同，所以遍历一遍就可以了。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-07-16
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
#define MAX 100010
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

char s[MAX], t[MAX];

int main()
{
	std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int i, j;
	while ( scanf("%s %s", s, t) != EOF )
	{
		int lens = strlen(s);
		int lent = strlen(t);
		for ( i = 0, j = 0; i < lent && j < lens; ++i )
		{
			if ( t[i] == s[j] )
				j++;
		}
		if ( j == lens )
			printf("Yes\n");
		else
			printf("No\n");
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
