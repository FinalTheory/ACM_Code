/**
 * @file HDU_4585.cpp
 * @brief   线段树问题，注意是如何建树查询区间内离某个数最近的数的。
 * 初始化错了，WA了一发，改正后2A。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-13
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
#include <map>
#define MAX 100010
#define CLR(arr,val) memset(arr,val,sizeof(arr))
#define L_son root << 1
#define R_son root << 1 | 1
#define Father root >> 1
using namespace std;

int id[MAX], grade[MAX];

const int INF = 2000000000;

struct NND
{
	int grade, id;
} monks[MAX];

bool fuck( const NND & A, const NND & B )
{
	return A.grade < B.grade;
}

struct TMD
{
	int L, R, nMax, nMin;
} Tree[MAX<<2];

void CreateTree( int root, int L, int R )
{
	Tree[root].L = L;
	Tree[root].R = R;
	Tree[root].nMin = INF;
	Tree[root].nMax = -1;
	if ( L == R )
		return;
	int M = ( L + R ) >> 1;
	CreateTree( L_son, L, M );
	CreateTree( R_son, M + 1, R );
}

void Insert( int root, int pos, int num )
{
	Tree[root].nMax = max( Tree[root].nMax, num );
	Tree[root].nMin = min( Tree[root].nMin, num );
	if ( Tree[root].L == pos && Tree[root].R == pos )
		return;
	int M = ( Tree[root].L + Tree[root].R ) >> 1;
	if ( pos > M )
		Insert( R_son, pos, num );
	else
		Insert( L_son, pos, num );
}

int Query( int root, int L, int R, bool flag )
{
	if ( L > R )
		return -1;
	if ( L == Tree[root].L && R == Tree[root].R )
		return flag ? Tree[root].nMax : Tree[root].nMin;
	int M = ( Tree[root].L + Tree[root].R ) >> 1;
	if ( R <= M )
		return Query( L_son, L, R, flag );
	else if ( L > M )
		return Query( R_son, L, R, flag );
	else
	{
		if ( flag )
			return max(Query( L_son, L, M, flag ), Query( R_son, M + 1, R, flag ));
		else
			return min(Query( L_son, L, M, flag ), Query( R_son, M + 1, R, flag ));
	}
}

inline bool valid( int x )
{
	if ( x != INF && x != -1 )
		return true;
	return false;
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
	int n;
	map<int, int> RB_T;
	while ( scanf("%d", &n) && n )
	{
		RB_T.clear();
		CreateTree( 1, 1, n + 1 );
		monks[1].id = 1; monks[1].grade = 1000000000;
		for ( int i = 2; i <= n + 1; ++i )
		{
			scanf("%d %d", &monks[i].id, &monks[i].grade);
			id[i] = monks[i].id;
			grade[i] = monks[i].grade;
		}
		sort( monks + 1, monks + n + 2, fuck );
		int idx = 1;
		for ( int i = 1; i <= n + 1; ++i )
			RB_T[monks[i].grade] = idx++;
		Insert( 1, n + 1, n + 1 );
		for ( int i = 2; i <= n + 1; ++i )
		{
			int id_res;
			int pos = RB_T[grade[i]];
			int pos1 = Query( 1, 1, pos - 1, true );
			int pos2 = Query( 1, pos + 1, n + 1, false );
			if ( valid(pos1) && valid(pos2) )
			{
				if ( grade[i] - monks[pos1].grade <= monks[pos2].grade - grade[i] )
					id_res = monks[pos1].id;
				else
					id_res = monks[pos2].id;
			}
			else if ( valid(pos1) && !valid(pos2) )
				id_res = monks[pos1].id;
			else if ( !valid(pos1) && valid(pos2) )
				id_res = monks[pos2].id;
			printf("%d %d\n", id[i], id_res );
			Insert( 1, RB_T[grade[i]], RB_T[grade[i]] );
		}
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
