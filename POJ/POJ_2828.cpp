/**
 * @file POJ_2828.cpp
 * @brief   线段树区间查询问题，注意逆序插入就可以了，因为逆序的话后面的位置一定是确定的。
 * 这样就只需要删掉已经插入的位置就可以了。1A太爽了！
 * @author FinalTheory
 * @version 0.1
 * @date 2013-05-01
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
#include <set>
#include <stack>
#include <sstream>
#include <iomanip>
#define MAX 200010
#define L_son root << 1
#define R_son root << 1 | 1
#define Father root >> 1
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

int pos[MAX], val[MAX], res[MAX];

struct TMD
{
	int L, R, nSum;
}Tree[MAX<<2];

void CreateTree( int root, int L, int R )  
{  
	Tree[root].L = L;
	Tree[root].R = R;
	Tree[root].nSum = R - L + 1;
	if (L == R) return ;
	int M = ( L + R ) >> 1;
	CreateTree( L_son, L, M );
	CreateTree( R_son, M + 1, R );
}

void Insert( int root, int pos, int val )
{
	Tree[root].nSum--;
	if ( Tree[root].L == Tree[root].R )
	{
		res[Tree[root].L] = val;
		return;
	}
	if ( pos <= Tree[L_son].nSum )
		Insert( L_son, pos, val );
	else
		Insert( R_son, pos - Tree[L_son].nSum, val );
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
	int N, i;
	while ( scanf("%d", &N) != EOF )
	{
		CreateTree( 1, 1, N );
		for ( i = 1; i <= N; ++i )
			scanf( "%d %d", &pos[i], &val[i] );
		for ( i = N; i >= 1; --i )
			Insert( 1, pos[i] + 1, val[i] );
		printf("%d", res[1]);
		for ( i = 2; i <= N; ++i )
			printf(" %d", res[i]);
		printf("\n");
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
