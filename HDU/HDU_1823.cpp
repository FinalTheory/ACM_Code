/**
 * @file HDU_1823.cpp
 * @brief   二维线段树，基本的区间查询
 * @hint    不知道怎么在线查询的时候离散化，所以就直接乘以10转换为整数来进行建树和查询了。
 *	    类型转换的时候注意精度控制，否则在G++下面会WA！目测GCC系列编译器的浮点实现略囧。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-16
 */
#if defined(__GNUC__)
#pragma GCC optimize ("O2")
#endif
#if defined(_MSC_VER)
#pragma comment(linker, "/STACK:36777216")
#endif
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <bitset>
#include <stack>
#include <queue>
#include <deque>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cctype>
#include <climits>
#include <ctime>
#define L_son root << 1
#define R_son root << 1 | 1
#define Father root >> 1
#define MAX_LR 110
#define MAX_UD 1010
#define eps 0.000001
#define CLR(arr,val) memset(arr,val,sizeof(arr))
using namespace std;
const int INF = 0x3f3f3f3f;

struct SegmentTree
{
	int L, R, nMax;
	struct TMD
	{
		int U, D;
		double nMax;
	} Tree[MAX_UD<<2];
	void CreateTree( int root, int U, int D )
	{
		Tree[root].U = U;
		Tree[root].D = D;
		Tree[root].nMax = -1.;
		if ( U == D )
			return;
		int M = ( U + D ) >> 1;
		CreateTree( L_son, U, M );
		CreateTree( R_son, M + 1, D );
	}
	void Insert( int root, int pos_UD, double num )
	{
		if ( num > Tree[root].nMax )
			Tree[root].nMax = num;
		if ( Tree[root].U == pos_UD && Tree[root].D == pos_UD )
			return;
		int M = ( Tree[root].U + Tree[root].D ) >> 1;
		if ( pos_UD > M )
			Insert( R_son, pos_UD, num );
		else
			Insert( L_son, pos_UD, num );
	}
	double Query( int root, int U, int D )
	{
		if ( U == Tree[root].U && D == Tree[root].D )
			return Tree[root].nMax;
		int M = ( Tree[root].U + Tree[root].D ) >> 1;
		if ( D <= M ) {
			return Query( L_son, U, D );
		} else if ( U > M ) {
			return Query( R_son, U, D );
		} else {
			return max( Query( L_son, U, M ), Query( R_son, M + 1, D ) );
		}
	}
} Tree[MAX_LR<<2];
void CreateTree( int root, int L, int R, int U, int D )
{
	Tree[root].L = L;
	Tree[root].R = R;
	Tree[root].nMax = -1.;
	Tree[root].CreateTree(1, U, D );
	if ( L == R )
		return;
	int M = ( L + R ) >> 1;
	CreateTree( L_son, L, M, U, D );
	CreateTree( R_son, M + 1, R, U, D );
}

void Insert( int root, int pos_LR, int pos_UD, double num )
{
	Tree[root].Insert( 1, pos_UD, num );
	if ( Tree[root].L == pos_LR && Tree[root].R == pos_LR )
		return;
	int M = ( Tree[root].L + Tree[root].R ) >> 1;
	if ( pos_LR > M )
		Insert( R_son, pos_LR, pos_UD, num );
	else
		Insert( L_son, pos_LR, pos_UD, num );
}
double Query( int root, int L, int R, int U, int D )
{
	if ( Tree[root].L == R && Tree[root].R == R )
		return Tree[root].Query( 1, U, D );
	int M = ( Tree[root].L + Tree[root].R ) >> 1;
	if ( R <= M ) {
		return Query( L_son, L, R, U, D );
	} else if ( L > M ) {
		return Query( R_son, L, R, U, D );
	} else {
		return max( Query( L_son, L, M, U, D ), Query( R_son, M + 1, R, U, D ) );
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
	int M, h, h1, h2, a1, a2, l, a;
	double A, L, H1, H2, A1, A2;
	char str[5];
	while ( scanf("%d", &M) && M )
	{
		CreateTree( 1, 1, MAX_LR, 1, MAX_UD );
		while ( M-- )
		{
			scanf("%s", str);
			if ( str[0] == 'I' ) {
				scanf("%d %lf %lf", &h, &A, &L);
				//就是这里，注意控制精度
				a = A * 10 + 1 + eps; h -= 99;
				Insert( 1, h, a, L );
			} else {
				scanf("%lf %lf %lf %lf", &H1, &H2, &A1, &A2);
				h1 = H1 + eps; h2 = H2 + eps; h1 -= 99; h2 -= 99;
				if ( fabs(H1 - (int)H1) > eps ) ++h1;
				if ( h1 > h2 ) swap( h1, h2 );
				//还有这里
				a1 = A1 * 10 + 1 + eps; a2 = A2 * 10 + 1 + eps;
				if ( a1 > a2 ) swap( a1, a2 );
				double ans = Query( 1, h1, h2, a1, a2 );
				if ( ans >= 0. )
					printf("%.1lf\n", ans);
				else
					puts("-1");
			}
		}
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
