/**
 * @file HDU_3265.cpp
 * @brief   线段树扫描线，由于矩形镂空，所以直接拆成四个小矩形就可以了。
 * 不知道为什么用long long不行，WA了两发，RE了两发。
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
#define MAX 100010
#define CLR(arr,val) memset(arr,val,sizeof(arr))
typedef __int64 LL;
using namespace std;
struct NND
{
	int L, R, Cover;
	int calc;
} Tree[MAX<<4];
struct TMD
{
	int high, low, x;
	int flag;
} lines[MAX<<4];
int buffer[MAX<<4];
int height[MAX<<4];
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
bool fuck2( int A, int B )
{
	return A > B;
}
int BinSearch( int Key, int low, int high )
{
	int mid;
	while ( high >= low )
	{
		mid = ( high + low ) >> 1;
		if ( height[mid] == Key )
			return mid;
		else if ( height[mid] < Key )
			high = mid - 1;
		else
			low = mid + 1;
	}
	return 0;
}

void PushUp( int root )
{
	if ( Tree[root].Cover )
		Tree[root].calc = height[Tree[root].L] - height[Tree[root].R + 1];
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

int p_lines, p_buffer, p_height;

void Cut( int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4 )
{
	buffer[p_buffer++] = y1;
	buffer[p_buffer++] = y2;
	buffer[p_buffer++] = y3;
	buffer[p_buffer++] = y4;
	if( y2 != y4 )
	{
		lines[p_lines].high = y2;
		lines[p_lines].low = y4;
		lines[p_lines].x = x1;
		lines[p_lines++].flag = 1;
		lines[p_lines].high = y2;
		lines[p_lines].low = y4;
		lines[p_lines].x = x2;
		lines[p_lines++].flag = -1;
	}
	if ( y1 != y3 )
	{
		lines[p_lines].high = y3;
		lines[p_lines].low = y1;
		lines[p_lines].x = x1;
		lines[p_lines++].flag = 1;
		lines[p_lines].high = y3;
		lines[p_lines].low = y1;
		lines[p_lines].x = x2;
		lines[p_lines++].flag = -1;
	}
	if ( x1 != x3 )
	{
		lines[p_lines].high = y4;
		lines[p_lines].low = y3;
		lines[p_lines].x = x1;
		lines[p_lines++].flag = 1;
		lines[p_lines].high = y4;
		lines[p_lines].low = y3;
		lines[p_lines].x = x3;
		lines[p_lines++].flag = -1;
	}
	if ( x2 != x4 )
	{
		lines[p_lines].high = y4;
		lines[p_lines].low = y3;
		lines[p_lines].x = x4;
		lines[p_lines++].flag = 1;
		lines[p_lines].high = y4;
		lines[p_lines].low = y3;
		lines[p_lines].x = x2;
		lines[p_lines++].flag = -1;
	}
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int n, i, j;
	int x1, y1, x2, y2, x3, y3, x4, y4;
	LL sum;
	while ( scanf( "%d", &n ) && n )
	{
		sum = 0;
		p_lines = p_buffer = p_height = 0;
		for ( i = 0; i < n; ++i )
		{
			scanf("%d %d %d %d %d %d %d %d", &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4);
			Cut( x1, y1, x2, y2, x3, y3, x4, y4 );
		}
		sort( buffer, buffer + p_buffer, fuck2 );
		sort( lines, lines + p_lines, fuck );
		int prev = -1;
		for ( i = 0, j = 1; i < p_buffer; ++i )
		{
			if ( buffer[i] != prev )
				height[j++] = buffer[i];
			prev = buffer[i];
		}
		int num_points = j - 1;
		CreateTree( 1, 1, num_points - 1 );
		for ( i = 0; i < p_lines - 1; ++i )
		{
			int left = BinSearch( lines[i].high, 1, num_points );
			int right = BinSearch( lines[i].low, 1, num_points ) - 1;
			Insert( 1, left, right, lines[i].flag );
			sum += (LL)((lines[i + 1].x - lines[i].x)) * (LL)(Tree[1].calc);
		}
		printf("%I64d\n", sum);
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
