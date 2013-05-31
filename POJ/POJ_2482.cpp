/**
 * @file POJ_2482.cpp
 * @brief   线段树扫描线问题，没注意范围RE了两发，读题错误WA了一发。
 * 这题的主要思想就是，一个星星的亮度影响它右边W处的位置。
 * 所以对横轴离散化建树，每个星星成为一条水平线段，从上到下扫描星星的影响范围，记录最大值就可以了。
 * 难想的地方主要是模型的转化，搞定这个之后剩下的就简单了。
 * 这道题暴露出我对线段树的理解，特别是更新的顺序仍然是短板。
 * 需要认真思索一下。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-05-28
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
#define L_son root << 1
#define R_son root << 1 | 1
#define MAX 10010
#define CLR(arr,val) memset(arr,val,sizeof(arr))
typedef long long LL;
using namespace std;
LL W, H;
struct NND
{
	int L, R, nMax, nInc;
} Tree[MAX<<3];
struct TMD
{
	LL left, right, height;
	int value;
} lines[MAX<<1];
bool fuck( const TMD & A, const TMD & B )
{
	if ( A.height != B.height )
		return A.height > B.height;
	else
		return A.value < B.value;
}
LL x_pos[MAX<<1];
LL buffer[MAX<<1];
void CreateTree( int root, int L, int R )  
{  
	Tree[root].L = L;
	Tree[root].R = R;
	Tree[root].nMax = Tree[root].nInc = 0;
	if (L == R) return;
	int M = ( L + R ) >> 1;
	CreateTree( L_son, L, M );
	CreateTree( R_son, M + 1, R );
}

void PushUp( int root )
{

	Tree[root].nMax = max( Tree[L_son].nMax, Tree[R_son].nMax );
}

void PushDown( int root )
{
	//下推的时候以同样的方式更新儿子的信息，然后在PushUp的过程中会自动更新父亲的nMax
	Tree[L_son].nInc += Tree[root].nInc;
	Tree[L_son].nMax += Tree[root].nInc;
	Tree[R_son].nInc += Tree[root].nInc;
	Tree[R_son].nMax += Tree[root].nInc;
	Tree[root].nInc = 0;
}


void Insert( int root, int L, int R, int value )
{
	if ( Tree[root].L == L && Tree[root].R == R )
	{
		//如果存在区间直接匹配，就更新这个区间的增量（用于PushDown）和最大值本身
		Tree[root].nInc += value;
		Tree[root].nMax += value;
		return;
	}
	//否则就把信息下推
	PushDown(root);
	int M = (Tree[root].L + Tree[root].R) >> 1;
	if ( R <= M )
	{
		Insert( L_son, L, R, value );
	}
	else if ( L > M )
	{
		Insert( R_son, L, R, value );
	}
	else
	{
		Insert( L_son, L, M, value );
		Insert( R_son, M + 1, R, value );
	}
	PushUp(root);
}

int BinSearch( LL Key, int low, int high )
{
	int mid;
	while ( low <= high )
	{
		mid = ( low + high ) >> 1;
		if ( x_pos[mid] == Key )
			return mid;
		else if ( x_pos[mid] > Key )
			high = mid - 1;
		else
			low = mid + 1;
	}
	return -1;
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
	LL x, y;
	int n, i, j, c, res;;
	LL p_xpos, p_lines;
	while ( scanf("%d %d %d", &n, &W, &H) != EOF )
	{
		p_lines = p_xpos = 0;
		for ( i = 0; i < n; ++i )
		{
			scanf("%lld %lld %d", &x, &y, &c);
			buffer[p_xpos++] = x;
			buffer[p_xpos++] = x + W;
			lines[p_lines].left = x;
			lines[p_lines].right = x + W;
			lines[p_lines].height = y;
			lines[p_lines++].value = c;
			lines[p_lines].left = x;
			lines[p_lines].right = x + W;
			lines[p_lines].height = y - H;
			lines[p_lines++].value = -c;
		}
		sort( lines, lines + p_lines, fuck );
		sort( buffer, buffer + p_xpos );
		LL prev = -1;
		for ( i = 0, j = 1; i < p_xpos; ++i )
		{
			if ( buffer[i] != prev )
				x_pos[j++] = buffer[i];
			prev = buffer[i];
		}
		int x_pos_nums = j - 1;
		CreateTree( 1, 1, x_pos_nums - 1 );
		res = -1;
		for ( i = 0; i < p_lines; ++i )
		{
			int left = BinSearch( lines[i].left, 1, x_pos_nums );
			int right = BinSearch( lines[i].right, 1, x_pos_nums ) - 1;
			Insert( 1, left, right, lines[i].value );
			if ( Tree[1].nMax > res )
				res = Tree[1].nMax;
		}
		printf("%d\n", res);
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
