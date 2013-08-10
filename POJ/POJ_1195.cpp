/**
 * @file POJ_1195.cpp
 * @brief   二维树状数组模版题
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-09
 */
#if defined(__GNUC__)
#pragma GCC optimize ("O2")
#endif
#if defined(_MSC_VER)
#pragma comment(linker, "/STACK:36777216")
#endif

#include <iostream>
#include <algorithm>
#include <functional>
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
#include <queue>
#include <iomanip>
#define MAX 1100
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

int Mat[MAX][MAX];
inline int Lowbit( int x )
{
	return x & (-x);
}
int S;
void Add( int x, int y, int num )
{
	for ( int i = x ; i <= S; i += Lowbit(i) )
		for ( int j = y ; j <= S; j += Lowbit(j) )
			Mat[i][j] += num;
}

long long Query( int x, int y )
{
	long long res = 0;
	for ( int i = x ; i > 0; i -= Lowbit(i) )
		for ( int j = y ; j > 0; j -= Lowbit(j) )
			res += Mat[i][j];
	return res;
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
	int order, X, Y, A, L, B, R, T;
	while (true)
	{
		scanf("%d", &order);
		switch ( order )
		{
		case 0:
			scanf("%d", &S);
			for ( int i = 1; i <= S; ++i )
				for ( int j = 1; j <= S; ++j )
					Mat[i][j] = 0;
			break;
		case 1:
			scanf("%d %d %d", &X, &Y, &A);
			Add( X + 1, Y + 1, A );
			break;
		case 2:
			scanf("%d %d %d %d", &L, &B, &R, &T);
			printf( "%lld\n", Query( R + 1, T + 1 ) - Query( L, T + 1 ) - Query( R + 1, B ) + Query( L, B ) );
			break;
		case 3:
			goto end;
			break;
		}
	}
	end:;
#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
