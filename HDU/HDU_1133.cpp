/*
	数学题。卡特兰数的应用+大数模拟。
	几乎都是copy的别人的思路和代码，惭愧了。
	数学不好推不出公式，另外阶乘的生成部分比较纠结。
	呆会试着自己写一下。
*/
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define MAX 100
#define BASE 100000
int fact[205][MAX];
int res[MAX];
void multiply(int a[],int Max,int b)
{
	int i,array=0;
	for (i=Max-1; i>=0; i--)
	{
		array+=b*a[i];
		a[i] = array%BASE;
		array /= BASE;
	}
}
void setFact ()
{
	fact[0][MAX-1] = fact[1][MAX-1] = 1;
	for ( int i = 2; i <= 200; ++ i )
	{
		memcpy ( fact[i] , fact[i-1] , MAX * sizeof ( int ) );
		multiply ( fact[i] , MAX , i );
	}
}
void divide(int a[], int Max, int b)
{
	int i,div=0;
	for (i=0;i<Max; i++)
	{
		div = div*BASE + a[i];
		a[i] = div / b;
		div %= b;
	}
}
void outPut ( int ctl[MAX] )
{
	int i = 0;
	while ( i < MAX && ctl[i] == 0 )i++;
	printf ( "%d", ctl[i++] );
	while ( i < MAX )
		printf ( "%04d", ctl[i++] );
	putchar ( '\n' );
}
int main()
{
	int m, n, i, j = 1;
	setFact();
	while ( cin >> m >> n, m + n )
	{
		printf("Test #%d:\n", j++);
		if ( m < n )
		{
			puts("0");
			continue;
		}
		memcpy ( res , fact[m+n] , MAX * sizeof ( int ) );
		multiply ( res, MAX, m - n + 1 );
		divide ( res, MAX, m + 1 );
		outPut ( res );
	}
}