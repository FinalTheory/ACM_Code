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
inline void PushUp( int root )
{
	Tree[root].nSum = Tree[L_son].nSum + Tree[R_son].nSum;
}
void CreateTree( int root, int L, int R )  
{  
	Tree[root].L = L;
	Tree[root].R = R;
	Tree[root].nInc = 0;
	if (L == R)
	{
		scanf("%lld", &Tree[root].nSum);
		return;
	}
	int M = ( L + R ) >> 1;
	CreateTree( L_son, L, M );
	CreateTree( R_son, M + 1, R );
	PushUp(root);
}

inline void PushDown( int root )
{
	if ( Tree[root].nInc != 0 )
	{
		Tree[L_son].nInc += Tree[root].nInc;
		Tree[R_son].nInc += Tree[root].nInc;
		Tree[L_son].nSum += Tree[root].nInc * Tree[L_son].len();
		Tree[R_son].nSum += Tree[root].nInc * Tree[R_son].len();
		Tree[root].nInc = 0;
	}
}

void Add( int root, int L, int R, int num )
{
	if ( Tree[root].L == L && Tree[root].R == R )
	{
		Tree[root].nInc += num;
		Tree[root].nSum += (LL)num * Tree[root].len();
		return;
	}
	PushDown(root);
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
	PushUp(root);
}

LL Query( int root, int L, int R )
{
	if ( L == Tree[root].L && R == Tree[root].R )
		return Tree[root].nSum;
	PushDown( root );
	int M = ( Tree[root].L + Tree[root].R ) >> 1;
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
