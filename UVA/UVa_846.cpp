/*
	贪心问题，策略很简单。
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
#define MAX(x, y) (x) > (y) ? (x) : (y)
#define MIN(x, y) (x) < (y) ? (x) : (y)
#define SWAP(x, y) (x) ^= (y) ^= (x) ^= (y)
#define SIZE 65536
using namespace std;
unsigned square[SIZE];
struct TMD
{
	unsigned num, index, steps;
};
bool fuck( TMD A, TMD B )
{
	return A.num < B.num;
}
bool __fuck( TMD A, TMD B )
{
	return A.index < B.index;
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
	unsigned n, x, y, i, j;
	cin >> n;
	TMD * nums = new TMD [n];
	for ( i = 1; i < SIZE; i++ )
		square[i] = i * i;
	for ( i = 0; i < n; i++ )
	{
		cin >> x >> y;
		nums[i].index = i;
		nums[i].num = y - x;
	}
	sort(nums, nums + n, fuck);
	i = 1; j = 0;
	while ( i < SIZE )
	{
		if ( nums[j].num == 0 )
		{
			nums[j].steps = 0;
			++j;
			if ( j == n )
				break;
			else
				continue;
		}
		if ( nums[j].num >= square[i] && nums[j].num < square[i+1] )
		{
			nums[j].steps = 2 * i - 1;
			nums[j].num -= square[i];
			if ( nums[j].num > 0 )
			{
				if ( ( nums[j].num < i ) )
					++nums[j].steps;
				else 
				{
					nums[j].steps += nums[j].num / i;
					if ( nums[j].num % i )
						++nums[j].steps;
				}
			}
			++j;
			if ( j == n )
				break;
		}
		else
			++i;
	}
	sort(nums, nums + n, __fuck);
	for ( i = 0; i < n; i++ )
		cout << nums[i].steps << '\n';
#ifndef ONLINE_JUDGE
	program_end = clock();
	cout << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}