/*
	水题不解释，还WA了两次尼玛……
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
char spec[10] = "~!@#$%^";
bool check( char * str )
{
	int len = strlen( str ), i, j, k;
	char mask = 0;
	char have_upper = 0, have_lower = 0, have_num = 0, have_spec = 0, found = 1;
	if ( len < 8 || len > 16 )
		return 0;
	for ( i = 0; i < len; ++i )
	{
		if ( !have_upper && str[i] >= 'A' && str[i] <= 'Z' )
			have_upper = 1;
		if ( !have_lower && str[i] >= 'a' && str[i] <= 'z' )
			have_lower = 1;
		if ( !have_num && str[i] >= '0' && str[i] <= '9' )
			have_num = 1;
		if ( !have_spec )
			for ( j = 0; j < 7; ++j )
				if ( str[i] == spec[j] )
				{
					have_spec = 1;
					break;
				}
	}
	mask = have_lower + have_upper + have_num + have_spec;
	if ( mask < 3 )
		return 0;

// 	for ( i = 0; i < len - 1; ++i )
// 		if ( str[i] == str[i + 1] )
// 			return 0;
// 
// 	for ( i = 0; i < len - 1; ++i )
// 		for ( j = i + 1; j < len; ++j )
// 			if ( str[i] == str[j] && j - i > 1 )
// 			{
// 				if ( str[i + 1] == str[j + 1] )
// 					return 0;
// 			}
	return 1;
}

using namespace std;
int main()
{
	//std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int M;
	char str[100];
	cin >> M; getchar();
	while ( M-- )
	{
		memset( str, 0, sizeof(str) );
		gets( str );
		if ( check( str ) )
			printf( "YES\n" );
		else
			printf( "NO\n" );
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cout << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}