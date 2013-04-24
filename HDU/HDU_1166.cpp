/**
 * @file HDU_1166.cpp
 * @brief   线段树入门题，单点更新，效率还是不怎么样，应该写写树状数组。
 * 输入的时候注意格式，RE了两次，尼玛……
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
struct TMD
{
	int L, R;
	int nSum;
	TMD * p_left, * p_right;
	TMD()
	{
		p_left = p_right = NULL;
		nSum = 0;
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
	root->nSum += num;
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
		return root->nSum;
	int M = ( root->L + root->R ) / 2;
	if ( L > M )
		return Query( root->p_right, L, R );
	else if ( R <= M )
		return Query( root->p_left, L, R );
	else
		return Query( root->p_left, L, M ) + Query( root->p_right, M + 1, R );
}

int main()
{
	//std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int N, T, i, a, b, num, index;
	char com[20];
	TMD * root;
	scanf( "%d", &T );
	for ( index = 1; index <= T; ++index )
	{
		printf("Case %d:\n", index);
		scanf("%d", &N);
		while ( !Pointers.empty() )
		{
			delete Pointers.top();
			Pointers.pop();
		}
		root = CreateTree( 1, N );
		for ( i = 1; i <= N; ++i )
		{
			scanf("%d", &num);
			Insert( root, num, i );
		}
		while ( 1 )
		{
			scanf( "%s", com );
			switch ( com[0] )
			{
			case 'A':
				scanf( "%d %d", &a, &b );
				Insert( root, b, a );
				break;
			case 'S':
				scanf( "%d %d", &a, &b );
				Insert( root, -b, a );
				break;
			case 'Q':
				scanf( "%d %d", &a, &b );
				printf( "%d\n", Query( root, a, b ) );
				break;
			case 'E':
				goto out;
			}
		}
out:
		;
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
