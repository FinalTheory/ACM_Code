/**
 * @file SGU_177.cpp
 * @brief   线段树扫描线
 * @input   一个矩阵，并给出大量操作要求对矩阵的指定矩形区域染色
 * @output  白色块的个数，即矩阵求和
 * @hint    线段树按列建树查询，是一种类似扫描线的思想。
 * @feeling 一开始脑子抽了，上来开始试图敲二维线段树，结果是显然的——跪烂了！
 *	    完全搞不定带两重惰性标记的线段树区间更新，最后发现不用优化这个n到log(n)也是能过的。
 *	    修改之后，蛋疼地发现居然卡内存，最后不得不改了写法才能过。
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
#define MAX 5010
#define CLR(arr,val) memset(arr,val,sizeof(arr))
using namespace std;
struct SegmentTree
{
	struct TMD
	{
		int U, D, nSum, nNew;
	} Tree[1010*4];
	void CreateTree( int root, int U, int D )
	{
		Tree[root].U = U;
		Tree[root].D = D;
		Tree[root].nSum = D - U + 1;
		Tree[root].nNew = -1;
		if ( U == D )
			return;
		int M = ( U + D ) >> 1;
		CreateTree( L_son, U, M );
		CreateTree( R_son, M + 1, D );
	}
	void PushUp( int root )
	{
		Tree[root].nSum = Tree[L_son].nSum + Tree[R_son].nSum;
	}
	void PushDown( int root )
	{
		if ( Tree[root].nNew != -1 )
		{
			Tree[L_son].nNew = Tree[R_son].nNew = Tree[root].nNew;
			Tree[L_son].nSum = ( Tree[L_son].D - Tree[L_son].U + 1 ) * Tree[L_son].nNew;
			Tree[R_son].nSum = ( Tree[R_son].D - Tree[R_son].U + 1 ) * Tree[R_son].nNew;
			Tree[root].nNew = -1;
		}
	}
	void Update( int root, int U, int D, int num )
	{
		if ( Tree[root].U == U && Tree[root].D == D )
		{
			Tree[root].nNew = num;
			Tree[root].nSum = ( D - U + 1 ) * num;
			return;
		}
		PushDown(root);
		int M = ( Tree[root].U + Tree[root].D ) >> 1;
		if ( U > M ) {
			Update( R_son, U, D, num );
		} else if ( D <= M ) {
			Update( L_son, U, D, num );
		} else {
			Update( L_son, U, M, num );
			Update( R_son, M + 1, D, num );
		}
		PushUp(root);
	}
};
SegmentTree Tree;
int x1[MAX], y3[MAX], x2[MAX], y4[MAX];
char c[MAX][5];
int main()
{
	//std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int N, M, sum, ans;
	while ( scanf("%d %d", &N, &M) != EOF )
	{
		for ( int i = 0; i < M; ++i )
		{
			scanf("%d %d %d %d %s", &x1[i], &y3[i], &x2[i], &y4[i], c[i]);
			if ( x1[i] > x2[i] ) swap(x1[i], x2[i]);
			if ( y3[i] > y4[i] ) swap(y3[i], y4[i]);
		}
		ans = 0;
		for ( int k = 1; k <= N; ++k )
		{
			Tree.CreateTree( 1, 1, N );
			for ( int i = 0; i < M; ++i ) if ( x1[i] <= k && k <= x2[i] )
			{
				if ( c[i][0] == 'w' )
					Tree.Update( 1, y3[i], y4[i], 1 );
				else
					Tree.Update( 1, y3[i], y4[i], 0 );
			}
			ans += Tree.Tree[1].nSum;
		}
		printf("%d\n", ans);
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
