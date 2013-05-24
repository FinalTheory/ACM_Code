/**
 * @file HDU_1828.cpp
 * @brief   线段树扫描线问题，TMD在HDU上面是多组数据！！！
 * 横竖扫描两遍就可以了，考虑边的插入以及长度的变化，每次插入完成用PushUp把信息提到根节点。
 * 需要注意的是边重合的情况，所以排序的时候如果边重合的话应该先插入权值为1的边再插入权值为-1的。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-05-21
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
#define MAX 2*5010
#define L_son root << 1
#define R_son root << 1 | 1
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

int x_pos[MAX], y_pos[MAX];
int buffer1[MAX], buffer2[MAX];

char flag;

struct TMD1
{
	int left, right, height, flag;
} x_lines[MAX];
bool fuck1( TMD1 & A, TMD1 & B )
{
	if ( A.height != B.height )
		return A.height > B.height;
	else
		return A.flag > B.flag;
}
struct TMD2
{
	int up, down, x_pos, flag;
} y_lines[MAX];
bool fuck2( TMD2 & A, TMD2 & B )
{
	if ( A.x_pos != B.x_pos )
		return A.x_pos < B.x_pos;
	else
		return A.flag > B.flag;
}
bool fuck( int A, int B )
{
	return A > B;
}
struct NND
{
	int L, R, Cover, len;
} Tree[MAX<<2];

void CreateTree( int root, int L, int R )  
{  
	Tree[root].L = L;
	Tree[root].R = R;
	Tree[root].Cover = Tree[root].len = 0;
	if (L == R) return;
	int M = ( L + R ) >> 1;
	CreateTree( L_son, L, M );
	CreateTree( R_son, M + 1, R );
}

int BinSearch1( int key, int low, int high )
{
	int mid;
	while ( low <= high )
	{
		mid = ( low + high ) >> 1;
		if ( y_pos[mid] == key )
			return mid;
		else if ( y_pos[mid] < key )
			high = mid - 1;
		else
			low = mid + 1;
	}
	return -1;
}
int BinSearch2( int key, int low, int high )
{
	int mid;
	while ( low <= high )
	{
		mid = ( low + high ) >> 1;
		if ( x_pos[mid] == key )
			return mid;
		else if ( x_pos[mid] > key )
			high = mid - 1;
		else
			low = mid + 1;
	}
	return -1;
}
void PushUp( int root )
{
	if ( Tree[root].Cover )
	{
		if ( flag )
			Tree[root].len = y_pos[Tree[root].L] - y_pos[Tree[root].R + 1];
		else
			Tree[root].len = x_pos[Tree[root].R + 1] - x_pos[Tree[root].L];
	}
	else if ( Tree[root].L == Tree[root].R )
		Tree[root].len = 0;
	else
		Tree[root].len = Tree[L_son].len + Tree[R_son].len;
}

void Insert( int root, int L, int R, int num )
{
	if ( Tree[root].L == L && Tree[root].R == R )
	{
		Tree[root].Cover += num;
		PushUp(root);
		return;
	}
	int M = ( Tree[root].L + Tree[root].R ) >> 1;
	if ( R <= M )
		Insert( L_son, L, R, num );
	else if ( L > M )
		Insert( R_son, L, R, num );
	else
	{
		Insert( L_son, L, M, num );
		Insert( R_son, M +1, R, num );
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
	int T, x1, y1, x2, y2, i, prev, p_new, len_prev, sum;
	int p_buf1, p_buf2;
	int p_xlines, p_ylines;
	TMD1 tmp1;
	TMD2 tmp2;
	while ( scanf("%d", &T) != EOF )
	{
		sum = p_buf1 = p_buf2 = p_xlines = p_ylines = 0;
		for ( i = 0; i < T; ++i )
		{
			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
			//保存所有横纵坐标
			buffer1[p_buf1++] = x1;
			buffer1[p_buf1++] = x2;
			buffer2[p_buf2++] = y1;
			buffer2[p_buf2++] = y2;
			//保存所有横线
			tmp1.left = x1; tmp1.right = x2; tmp1.height = y2; tmp1.flag = 1;
			x_lines[p_xlines++] = tmp1;
			tmp1.left = x1; tmp1.right = x2; tmp1.height = y1; tmp1.flag = -1;
			x_lines[p_xlines++] = tmp1;
			tmp2.up = y2; tmp2.down = y1; tmp2.x_pos = x1; tmp2.flag = 1;
			y_lines[p_ylines++] = tmp2;
			tmp2.up = y2; tmp2.down = y1; tmp2.x_pos = x2; tmp2.flag = -1;
			y_lines[p_ylines++] = tmp2;
		}
		sort(x_lines, x_lines + p_xlines, fuck1);
		sort(y_lines, y_lines + p_ylines, fuck2);
		sort( buffer1, buffer1 + p_buf1 );
		//纵坐标从大到小排序
		sort( buffer2, buffer2 + p_buf2, fuck );
		prev = -10000000;
		for ( i = 0, p_new = 1; i < p_buf1; ++i )
		{
			if ( buffer1[i] != prev )
				x_pos[p_new++] = buffer1[i];
			prev = buffer1[i];
		}
		int x_num = p_new - 1;
		prev = -10000000;
		for ( i = 0, p_new = 1; i < p_buf2; ++i )
		{
			if ( buffer2[i] != prev )
				y_pos[p_new++] = buffer2[i];
			prev = buffer2[i];
		}
		int y_num = p_new - 1;
		CreateTree( 1, 1, y_num - 1 );
		len_prev = 0; flag = 1;
		for ( i = 0; i < p_ylines; ++i )
		{
			int left, right;
			left = BinSearch1( y_lines[i].up, 1, y_num );
			right = BinSearch1( y_lines[i].down, 1, y_num ) - 1;
			Insert( 1, left, right, y_lines[i].flag );
			sum += abs( Tree[1].len - len_prev );
			len_prev = Tree[1].len;
		}
		CreateTree( 1, 1, x_num - 1 );
		len_prev = 0; flag = 0;
		for ( i = 0; i < p_xlines; ++i )
		{
			int left, right;
			left = BinSearch2( x_lines[i].left, 1, x_num );
			right = BinSearch2( x_lines[i].right, 1, x_num ) - 1;
			Insert( 1, left, right, x_lines[i].flag );
			sum += abs( Tree[1].len - len_prev );
			len_prev = Tree[1].len;
		}
		printf("%d\n", sum);
	}
#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
