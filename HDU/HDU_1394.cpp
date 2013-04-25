/**
 * @file HDU_1394.cpp
 * @brief   利用线段树求逆序对。
 * 核心思想是将取值范围作为区间，这样就可以快速统计某个取值范围里面有多少个数。
 * 这样顺序插入每一个数，对应的区间里的数增加，然后统计比这个数大的有多少个。
 * 因为查询到的比它大的一定是先前插入的，即产生了逆序。
 * 求得初始情况后，直接递推就可以求出剩下的，记录一下最小值就可以了。
 * 核心在于如何增加逆序对以及如何递推剩下的逆序对。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-04-25
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
int nums[5010];
//注意这里是将某个取值范围作为区间!
struct TMD
{
	int L, R;
	int nNum;   //某一个取值范围区间里有多少个数
	TMD * p_left, * p_right;
	TMD()
	{
		p_left = p_right = NULL;
		nNum = 0;
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
void Insert( TMD * root, int num )
{
	root->nNum++;
	if ( root->L == num && root->R == num )
		return;
	int M = ( root->L + root->R ) / 2;
	if ( num > M )
		Insert( root->p_right, num );
	else
		Insert( root->p_left, num );
}
int Query( TMD * root, int L, int R )
{
	if ( root->L == L && root->R == R )
		return root->nNum;
	int M = ( root->L + root->R ) / 2;
	if ( R <= M )
		return Query( root->p_left, L, R );
	else if ( L > M )
		return Query( root->p_right, L, R );
	else
		return Query( root->p_left, L, M ) + Query( root->p_right, M + 1, R );
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
	int n, i, sum, min_sum, start_point;
	TMD * root;
	while ( scanf("%d", &n) != EOF )
	{
		//似乎忘记释放内存了
		root = CreateTree( 1, n );
		for ( i = 1; i <= n; ++i )
			scanf("%d", nums + i);
		sum = 0;
		for ( i = 1; i <= n; ++i )
		{
			if ( nums[i] < n - 1 )
				sum += Query( root, nums[i] + 2, n );
			Insert( root, nums[i] + 1 );
		}
		min_sum = sum;
		for ( i = 1; i <= n; ++i )
		{
			int tmp = nums[i] + 1;
			//这一步递推非常重要！
			//每次移动顺序后用这一句算出下一次的逆序对数
			sum = sum - ( tmp - 1 ) + ( n - tmp );
			if ( sum < min_sum )
				min_sum = sum;
		}
		printf( "%d\n", min_sum );
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
