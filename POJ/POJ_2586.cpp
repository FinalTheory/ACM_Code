/**
 * @file POJ_2586.cpp
 * @brief   这题本来是贪心，但是推不出公式，尼玛劳资是学计算机的不是学数学的！
 * 怒改暴力，DFS枚举，282MS没超时，尼玛！
 * @author FinalTheory
 * @version 0.1
 * @date 2013-06-01
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

int nums[13];
int s, d, _max;
bool check()
{
	int sum;
	for ( int i = 1; i <= 8; ++i )
	{
		sum = 0;
		for ( int j = 0; j <= 4; ++j )
			sum += nums[i+j];
		if ( sum >= 0 )
			return false;
	}
	return true;
}

void DFS( int num )
{
	if ( num == 13 )
	{
		if ( check() )
		{
			int sum = 0;
			for ( int i = 1; i <= 12; ++i )
				sum += nums[i];
			if ( sum > _max )
				_max = sum;
		}
		return;
	}
	nums[num] = s;
	DFS( num + 1 );
	nums[num] = -d;
	DFS( num + 1 );
}

int main()
{
	std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	while ( scanf("%d %d", &s, &d) != EOF )
	{
		_max = -1;
		DFS(1);
		if ( _max > 0 )
			printf("%d\n", _max);
		else
			printf("Deficit\n");
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
