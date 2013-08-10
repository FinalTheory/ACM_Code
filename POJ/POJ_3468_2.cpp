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
#define MAX 100010
#define L_son root << 1
#define R_son root << 1 | 1
#define Father root >> 1
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;
typedef long long LL;

struct TMD
{
	int L, R;
	LL nSum, nInc;
	int len(){return R - L + 1;}
}Tree[MAX<<2];

void CreateTree( int root, int L, int R )  
{  
	Tree[root].L = L;
	Tree[root].R = R;
	Tree[root].nSum = 0;
	Tree[root].nInc = 0;
	if (L == R) return ;
	int M = ( L + R ) >> 1;
	CreateTree( L_son, L, M );
	CreateTree( R_son, M + 1, R );
}

void Insert( int root, int pos, int num )
{
	if ( pos >= Tree[root].L && pos <= Tree[root].R )
		Tree[root].nSum += num;
	if ( pos == Tree[root].L && pos == Tree[root].R )
		return;
	int M = ( Tree[root].L + Tree[root].R ) >> 1;
	if ( pos <= M )
		Insert( L_son, pos, num );
	else
		Insert( R_son, pos, num );
}

void Add( int root, int L, int R, int num )
{
	if ( Tree[root].L == L && Tree[root].R == R )
	{
		Tree[root].nInc += num;
		return;
	}
	Tree[root].nSum += ( R - L + 1 ) * num;
	int M = ( Tree[root].L + Tree[root].R ) >> 1;
	if ( R <= M )
		Add( L_son, L, R, num );
	else if ( L > M )
		Add( R_son, L, R, num );
	else
	{
		Add( L_son, L, M, num );
		Add( R_son, M + 1, R, num );
	}
}

LL Query( int root, int L, int R )
{
	if ( L == Tree[root].L && R == Tree[root].R )
		return Tree[root].nSum + Tree[root].len() * Tree[root].nInc;
	Tree[root].nSum += Tree[root].len() * Tree[root].nInc;
	int M = ( Tree[root].L + Tree[root].R ) >> 1;
	if ( Tree[root].nInc != 0 )
	{
		Add( L_son, Tree[root].L, M, Tree[root].nInc );
		Add( R_son, M + 1, Tree[root].R, Tree[root].nInc );
		Tree[root].nInc = 0;
	}
	if ( R <= M )
		return Query( L_son, L, R );
	else if ( L > M )
		return Query( R_son, L, R );
	else
		return Query( L_son, L, M ) + Query( R_son, M + 1, R );
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
	int N, Q, num;
	char str[5];
	while ( scanf("%d %d", &N, &Q) != EOF )
	{
		CreateTree( 1, 1, N );
		for ( int i = 1; i <= N; ++i )
		{
			scanf("%d", &num);
			Insert( 1, i, num );
		}
		int a, b, c;
		for ( int i = 0; i < Q; ++i )
		{
			scanf("%s %d %d", str, &a, &b);
			if ( str[0] == 'C' )
			{
				scanf("%d", &c);
				Add( 1, a, b, c );
			}
			else
				printf("%lld\n", Query( 1, a, b ));
		}
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
