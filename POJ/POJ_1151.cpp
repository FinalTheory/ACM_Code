/**
 * @file POJ_1151.cpp
 * @brief   线段树扫描线入门。
 * 这题需要注意一些trick。首先是线段如何插入。将所有y坐标离散化，二分查找做映射。
 * 扫描线从左到右，计算每次扫描线的位置与下一个位置的差，乘以当前可以用来计算面积的长度。
 * 而线段树的功能就是用来维护这个长度。插入左边对Cover增1，右边则对Cover减1。
 * 注意每次是先插入一条线段，在插入的过程中，递归返回时用PushUp更新父亲的状态。
 * 插入完成之后根节点就保存了长度信息，直接用就可以了。
 * 由于每条线段是对称的，所以PushUp过程不用考虑太复杂，不会出现节点的值为负数的情况。
 * 直接插入到目标位置，然后更新上去就可以。如果某个节点的Cover为正，说明它已经被覆盖，所以直接计算长度；
 * 如果为零，说明它没有被覆盖，这时候如果这个节点是叶子，就赋值为零，如果不是叶子，它的值就取决于子树了。
 * @author FinalTheory
 * @version 1.0
 * @date 2013-05-13
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
#define MAX 210
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;
struct NND
{
	int L, R, Cover;
	double calc;
} Tree[MAX<<2];
struct TMD
{
	double high, low, x;
	int flag;
} lines[MAX];
double buffer[MAX];
double height[MAX];
void CreateTree( int root, int L, int R )  
{  
	Tree[root].L = L;
	Tree[root].R = R;
	Tree[root].Cover = 0;
	Tree[root].calc = 0.;
	if (L == R) return;
	int M = ( L + R ) >> 1;
	CreateTree( L_son, L, M );
	CreateTree( R_son, M + 1, R );
}
bool fuck( TMD & A, TMD & B )
{
	return A.x < B.x;
}

int BinSearch( double Key, int low, int high )
{
	int mid;
	while ( high >= low )
	{
		mid = ( high + low ) >> 1;
		if ( height[mid] == Key )
			return mid;
		else if ( height[mid] > Key )
			high = mid - 1;
		else
			low = mid + 1;
	}
	return 0;
}

void PushUp( int root )
{
	if ( Tree[root].Cover )
		Tree[root].calc = height[Tree[root].R + 1] - height[Tree[root].L];
	else if ( Tree[root].L == Tree[root].R )
		Tree[root].calc = 0.;
	else
		Tree[root].calc = Tree[L_son].calc + Tree[R_son].calc;
}

void Insert( int root, int L, int R, int flag )
{
	if ( Tree[root].L == L && Tree[root].R == R )
	{
		Tree[root].Cover += flag;
		PushUp(root);
		return;
	}
	int M = ( Tree[root].L + Tree[root].R ) / 2;
	if ( R <= M )
	{
		Insert( L_son, L, R, flag );
	}
	else if ( L > M )
	{
		Insert( R_son, L, R, flag );
	}
	else
	{
		Insert( L_son, L, M, flag );
		Insert( R_son, M + 1, R, flag );
	}
	PushUp(root);
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
	int n, i, p_lines, p_buffer, p_height, j, index = 1;
	double x1, y1, x2, y2, sum;
	while ( scanf( "%d", &n ) && n )
	{
		sum = 0.;
		p_lines = p_buffer = p_height = 0;
		for ( i = 0; i < n; ++i )
		{
			scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
			buffer[p_buffer++] = y1;
			buffer[p_buffer++] = y2;
			lines[p_lines].high = y1;
			lines[p_lines].low = y2;
			lines[p_lines].x = x1;
			lines[p_lines++].flag = 1;
			lines[p_lines].high = y1;
			lines[p_lines].low = y2;
			lines[p_lines].x = x2;
			lines[p_lines++].flag = -1;
		}
		sort( buffer, buffer + p_buffer );
		sort( lines, lines + p_lines, fuck );
		height[1] = buffer[0];
		double prev = buffer[0];
		for ( i = 1, j = 2; i < p_buffer; ++i )
		{
			if ( buffer[i] != prev )
				height[j++] = buffer[i];
			prev = buffer[i];
		}
		int num_points = j - 1;
		CreateTree( 1, 1, num_points - 1 );
		//把线段从左到右插入
		for ( i = 0; i < p_lines - 1; ++i )
		{
			//确定左右端点开始插入
			int left = BinSearch( lines[i].high, 1, num_points );
			int right = BinSearch( lines[i].low, 1, num_points ) - 1;
			Insert( 1, left, right, lines[i].flag );
			//更新面积
			sum += (lines[i + 1].x - lines[i].x) * Tree[1].calc;
		}
		printf("Test case #%d\nTotal explored area: %.2lf\n\n", index, sum);
		index++;
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
