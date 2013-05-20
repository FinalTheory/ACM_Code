/**
 * @file ZOJ_3713.cpp
 * @brief   模拟题，笔误WA了三次，郁闷！
 * 注意输入如果是空行的话要输出00
 * @author FinalTheory
 * @version 0.1
 * @date 2013-05-18
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

char buffer[3000100];

int main()
{
	//std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int T, len, i;
	char c;
	unsigned num, mark1 = 0xffu, mark2 = 0x80u;
	scanf("%d", &T);
	getchar();
	while ( T-- )
	{
		gets(buffer);
		len = strlen(buffer);
		num = len;
		while ( num > 127 )
		{
			unsigned tmp = num & mark1;
			printf("%02X", tmp | mark2);
			num >>= 7;
		}
		printf("%02X", num);
		for ( i = 0; i < len; ++i )
			printf("%02X", buffer[i]);
		printf("\n");
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}

