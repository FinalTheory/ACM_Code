/*
	模板题，miiler_rabin素数测试和pollard_rho质因子分解；
	注意两数相乘取模时要用那个不会溢出的算法！
	另外pollard_rho有一些莫名其妙的问题，可能会超时之类的。
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cctype>
#include <climits>
#include <ctime>
#define TABLELEN 8
#define ULL unsigned long long
#define MAX ((ULL)1<<63)-1
#define c 1
using namespace std;

//素性检测数表
unsigned table[TABLELEN] = { 2, 3, 5, 7, 11, 13, 17, 23 };

//计算 a*b mod p 的不会溢出的算法
ULL MultiMod( ULL a, ULL b, ULL p )
{
	ULL sum = 0;
	while ( b )
	{
		if ( b & (ULL)1 )
			sum = ( sum + a ) % p;
		a <<= 1; b >>= 1;
		if ( a > p )
			a %= p;
	}
	return sum;
}

//计算 a^n mod p
ULL Mod( ULL a, ULL n, ULL p )
{
	if ( n == 0 )
		return 1;
	if ( n == 1 )
		return (a % p);
	if ( n & (unsigned)1 )
		return MultiMod( Mod( MultiMod( a, a, p ), n / 2, p ), a, p );
	else
		return ( Mod( MultiMod( a, a, p ), n / 2, p ) % p );
}

bool IsPrime( ULL N, unsigned a )
{
	ULL d = N - 1; 
	unsigned r = 0;
	while ( !( d & (ULL)1 ) )
	{
		d >>= 1;
		r++;
	}
	if ( Mod( a, d, N ) == 1 )
		return 1;
	for ( unsigned i = 0; i < r; ++i, d *= 2 )
		if ( Mod( a, d, N ) == N - 1 )
			return 1;
	return 0;
}
//求最大公约数
ULL gcd( ULL m, ULL n )
{
	return n ? gcd( n, m % n ) : m;
}

ULL pollard_rho( ULL n )
{
	ULL x, y, k, i, d;
	x = rand() % ( n - 1 ) + 1;
	y = x; d = k = 1; i = 2;
	do
	{
		++k;
		d = gcd( y - x, n );
		if ( d > 1 && d < n )
			return d;
		if ( i == k )
		{
			y = x;
			i <<= 1;
		}
		x = ( MultiMod( x, x, n ) + c ) % n;
	} while ( x != y );
	return n;
}

bool check( ULL N )
{
	char prime = 1;
	for ( int i = 0; i < TABLELEN; ++i )
		if ( table[i] < N )
		{
			if ( !IsPrime( N, table[i] ) )
				prime = 0;
		}
		else
			break;
	return prime;
}

ULL find_min( ULL n )
{
	if ( n == 1 )
		return (MAX);
	if ( check( n ) )
		return n;
	ULL p = pollard_rho( n ),\
		q = n / p,\
		a = find_min( p ),\
		b = find_min( q );
	return a < b ? a : b;
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
	ULL N;
	int T;
	cin >> T;
	while ( T-- )
	{
		cin >> N;
		if ( check(N) )
			cout << "Prime\n";
		else
			cout << find_min(N) << '\n';
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cout << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}