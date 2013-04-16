/*
	递推问题，公式为：
	f( n + f(f(n)) ) = f(n) + 1
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
#define SIZE 700000
using namespace std;
unsigned int num[SIZE] = {0, 1};
int prev = 1;
int F( unsigned int number )
{
	for ( int i = prev; i < SIZE - 1; i++ )
		if ( number >= num[i] && number < num[i+1] )
		{
			prev = i;
			return i;
		}
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
	int i;
	unsigned int n;
	for ( i = 2; i < SIZE; i++ )
		num[i] = INT_MAX;
	prev = 1;
	for ( i = 2; i < 700000; i++ )
		num[i] = num[i - 1] + F(i - 1);
	while ( cin >> n && n )
	{
		prev = 1;
		cout << F(n) << endl;
	}
#ifndef ONLINE_JUDGE
	program_end = clock();
	cout << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}