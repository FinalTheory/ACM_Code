/**
 * @file POJ_2777.cpp
 * @brief   线段树区间更新，注意使用一个整型变量，利用位运算记录染色情况。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-07
 */
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
#define L_son root << 1
#define R_son root << 1 | 1
#define Father root >> 1
#define MAX 100010
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

struct TMD
{
	int L, R, nBit, nNew;
	int len(){return R - L + 1;}
}Tree[MAX<<2];

void CreateTree( int root, int L, int R )
{
	Tree[root].L = L;
	Tree[root].R = R;
	Tree[root].nBit = 1;
	Tree[root].nNew = 0;
	if ( L == R )
		return;
	int M = ( L + R ) >> 1;
	CreateTree( L_son, L, M );
	CreateTree( R_son, M + 1, R );
}

void PushUp( int root )
{
	Tree[root].nBit = Tree[L_son].nBit | Tree[R_son].nBit;
}

inline void Replace_Color( int & bit, int color )
{
	bit = ( 1 << ( color - 1 ) );
}

void PushDown( int root )
{
	if ( Tree[root].nNew )
	{
		Tree[L_son].nNew = Tree[R_son].nNew = Tree[root].nNew;
		Tree[root].nNew = 0;
		Replace_Color( Tree[L_son].nBit, Tree[L_son].nNew );
		Replace_Color( Tree[R_son].nBit, Tree[R_son].nNew );
		
	}
}
void Update( int root, int L, int R, int color )
{
	if ( L == Tree[root].L && R == Tree[root].R )
	{
		Tree[root].nNew = color;
		Replace_Color( Tree[root].nBit, color );
		return;
	}
	PushDown( root );
	int M = ( Tree[root].L + Tree[root].R ) >> 1;
	if ( R <= M )
		Update( L_son, L, R, color );
	else if ( L > M )
		Update( R_son, L, R, color );
	else
	{
		Update( L_son, L, M, color );
		Update( R_son, M + 1, R, color );
	}
	PushUp(root);
}

int Query( int root, int L, int R )
{
	if ( Tree[root].L == L && Tree[root].R == R )
		return Tree[root].nBit;
	PushDown( root );
	int M = ( Tree[root].L + Tree[root].R ) >> 1;
	if ( R <= M )
		return Query( L_son, L, R );
	else if ( L > M )
		return Query( R_son, L, R );
	else
		return Query( L_son, L, M ) | Query( R_son, M + 1, R );
	PushUp(root);
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
	int L, T, O, x, y, color;
	char str[5];
	while ( scanf("%d %d %d", &L, &T, &O) != EOF )
	{
		CreateTree( 1, 1, L );
		while ( O-- )
		{
			scanf("%s", str);
			if ( str[0] == 'C' )
			{
				scanf("%d %d %d", &x, &y, &color);
				if ( x > y ) swap(x, y);
				Update( 1, x, y, color );
			}
			else
			{
				scanf("%d %d", &x, &y);
				if ( x > y ) swap(x, y);
				int bit = Query( 1, x, y ), ans = 0;
				for ( int i = 0; i < 32; ++i )
					if ( bit & ( 1 << i ) ) ans++;
				printf("%d\n", ans);
			}
		}
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
