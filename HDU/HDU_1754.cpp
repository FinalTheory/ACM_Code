/**
 * @file HDU_1754.cpp
 * @brief   线段树入门题，区间求最值问题。还是单点更新。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-04-24
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
#include <stack>
#define CLR(arr,val) memset(arr,val,sizeof(arr))
using namespace std;
inline int _max( int A, int B )
{
	return A > B ? A : B;
}
struct TMD
{
	int L, R;
	int nMax;
	TMD * p_left, * p_right;
	TMD()
	{
		p_left = p_right = NULL;
		nMax = -1;
	}
};
stack<TMD *> Pointers;
TMD * CreateTree( int L, int R )
{
	TMD * root = new TMD;
	Pointers.push(root);
	root->L = L;
	root->R = R;
	if ( L != R )
	{
		int M = ( L + R ) / 2;
		root->p_left  = CreateTree( L, M );
		root->p_right = CreateTree( M + 1, R );
	}
	return root;
}

void Insert( TMD * root, int num, int pos )
{
	if ( num > root->nMax )
		root->nMax = num;
	if ( root->L == pos && root->R == pos )
		return;
	int M = ( root->L + root->R ) / 2;
	if ( pos > M )
		Insert( root->p_right, num, pos );
	else
		Insert( root->p_left, num, pos );
}

int Query( TMD * root, int L, int R )
{
	if ( root->L == L && root->R == R )
		return root->nMax;
	int M = ( root->L + root->R ) / 2;
	if ( L > M )
		return Query( root->p_right, L, R );
	else if ( R <= M )
		return Query( root->p_left, L, R );
	else
		return _max( Query( root->p_left, L, M ) , Query( root->p_right, M + 1, R ) );
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
	int N, M, i, score, a, b;
	char com[5];
	TMD * root;
	while ( scanf("%d %d", &N, &M) != EOF )
	{
		while ( !Pointers.empty() )
		{
			delete Pointers.top();
			Pointers.pop();
		}
		root = CreateTree( 1, N );
		for ( i = 1; i <= N; ++i )
		{
			scanf("%d", &score);
			Insert( root, score, i );
		}
		for ( i = 1; i <= M; ++i )
		{
			scanf( "%s %d %d", com, &a, &b );
			if ( com[0] == 'Q' )
				printf("%d\n", Query( root, a, b ));
			else
				Insert( root, b, a );
		}
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
