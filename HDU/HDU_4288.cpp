/**
 * @file HDU_4288.cpp
 * @brief   线段树单点更新问题。
 * @hint    这题代码量其实不大，主要是需要设计好每个区间记录怎样的状态。
 *	    这里是记录区间中各个位置标号模5后的求和，查询时输出根节点的对应值即可。
 *	    由于是单点更新，每次更新到叶子，所以可以利用PushUp来更新所有父亲节点的信息。
 *	    核心思路是，对于每一个父亲区间，初始化为其左儿子的值，而对于每个右儿子中的位置，计算出其在
 *	    父亲节点中的位置，并再加上去，这样就完成了整棵树的信息更新。
 *	    注意离散化不需要再去重，因为数据保证了不出现重复。
 * @feeling 这题让我学到了对于单点更新问题，可以如何设计PushUp函数以做到更新整棵树的信息的。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-30
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
#define MAX 100010
#define CLR(arr,val) memset(arr,val,sizeof(arr))
using namespace std;
const int INF = 0x3f3f3f3f;
typedef __int64 LL;
struct TMD
{
	int L, R;
	LL nSum[5];
	int nSize;
	int len(){return R - L + 1;}
}Tree[MAX<<2];
struct NND
{
	int num, type;
} instr[MAX];
int nums[MAX];
void CreateTree( int root, int L, int R )  
{  
	Tree[root].L = L;
	Tree[root].R = R;
	CLR( Tree[root].nSum, 0 );
	Tree[root].nSize = 0;
	if ( Tree[root].L == Tree[root].R )
		 return;
	int M = ( L + R ) >> 1;
	CreateTree( L_son, L, M );
	CreateTree( R_son, M + 1, R );
}

void PushUp( int root )
{
	Tree[root].nSize = Tree[L_son].nSize + Tree[R_son].nSize;
	//这里是最核心的两步。
	memcpy( Tree[root].nSum, Tree[L_son].nSum, sizeof(Tree[root].nSum) );
	//重新计算对应位置在父亲区间中的位置
	for ( int i = 0; i < 5; ++i )
		Tree[root].nSum[( i + Tree[L_son].nSize ) % 5] += Tree[R_son].nSum[i];
}

void Insert( int root, int pos, int num, bool type )
{
	if ( Tree[root].L == pos && Tree[root].R == pos )
	{
		if ( type ) {
			Tree[root].nSum[1] = num;
			Tree[root].nSize = 1;
		} else {
			Tree[root].nSum[1] = 0;
			Tree[root].nSize = 0;
		}
		return;
	}
	int M = ( Tree[root].L + Tree[root].R ) >> 1;
	if ( pos <= M )
		Insert( L_son, pos, num, type );
	else
		Insert( R_son, pos, num, type );
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
	int N, num, nn;
	char str[20];
	while ( scanf("%d", &N) != EOF )
	{
		int p_orders = 0, p_nums = 0;
		for ( int i = 0; i < N; ++i )
		{
			scanf("%s", str);
			if ( str[0] == 'a' ) {
				scanf("%d", &num);
				nums[p_nums++] = num;
				instr[p_orders].num = num;
				instr[p_orders++].type = 1;
			} else if ( str[0] == 'd' ) {
				scanf("%d", &num);
				instr[p_orders].num = num;
				instr[p_orders++].type = 2;
			} else {
				instr[p_orders++].type = 3;
			}
		}
		sort( nums, nums + p_nums );
		nn = p_nums;
		//nn = unique( nums, nums + p_nums ) - nums;
		CreateTree( 1, 1, nn );
		for ( int i = 0; i < N; ++i )
		{
			if ( instr[i].type == 1 ) {
				int pos = lower_bound( nums, nums + nn, instr[i].num ) - nums + 1;
				Insert( 1, pos, instr[i].num, true );
			} else if ( instr[i].type == 2 ) {
				int pos = lower_bound( nums, nums + nn, instr[i].num ) - nums + 1;
				Insert( 1, pos, instr[i].num, false );
			} else {
				//cout << Tree[1].nSum[3] << endl;
				printf("%I64d\n", Tree[1].nSum[3]);
			}
		}
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
