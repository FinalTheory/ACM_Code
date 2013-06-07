/**
 * @file POJ_3096.cpp
 * @brief   水题，模拟。1A。主要是试试新的机械键盘。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-06-05
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

char buffer[100];
char map[26][26];

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
	while ( 1 )
	{
		scanf("%s", buffer );
		if ( buffer[0] == '*' )
			break;
		int len = strlen( buffer );
		if ( len == 1 )
		{
			printf("%s is surprising.\n", buffer);
			continue;
		}
		bool found = false;
		for ( i = 1; i <= len - 1 && !found; ++i )
		{
			CLR( map, 0 );
			for ( j = 0; j + i < len; ++j )
			{
				int a = buffer[j] - 'A';
				int b = buffer[j + i] - 'A';
				if ( !map[a][b] )
					map[a][b] = 1;
				else
				{
					found = true;
					break;
				}
			}
		}
		if ( found )
			printf("%s is NOT surprising.\n", buffer);
		else
			printf("%s is surprising.\n", buffer);
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
