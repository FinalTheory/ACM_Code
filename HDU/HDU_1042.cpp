/**
 * @file HDU_1042.cpp
 * @brief   模拟问题
 * 直接先乘一遍，然后再处理进位就可以。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-04-05
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
#include <sstream>
#include <iomanip>
#define CLR(arr,val) memset(arr,val,sizeof(arr))
#define NUM 100000
#define MAX 100000

using namespace std;

int buffer[MAX];

int main()
{
	std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int N, i, res, num, seq, len;
	while ( cin >> N )
	{
		len = 1;
		if ( N == 0 || N == 1 )
		{
			cout << "1" << endl;
			continue;
		}
		CLR(buffer, 0);
		buffer[0] = 1;
		for ( num = 2; num <= N; ++num )
		{
			for ( i = 0; i < len; ++i )
				buffer[i] *= num;
			for ( i = 0; i < len; ++i )
			{
				buffer[i+1] += buffer[i] / NUM;
				buffer[i] %= NUM;
				while ( buffer[len] ) ++len;
			}
		}
		printf( "%d", buffer[len-1] );
		for ( i = len - 2; i >= 0; i-- )
			printf( "%05d", buffer[i] );
		putchar('\n');
// 		cout << buffer[len-1];
// 		for ( i = len - 2; i >= 0; i-- )
// 			cout << setw(5) << setfill('0') << buffer[i];
// 		cout << '\n';
	}
#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
