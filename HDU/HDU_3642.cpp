/**
 * @file HDU_3642.cpp
 * @brief   线段树求体积并，原理上跟二维的矩形面积是一样的，只不过需要离散化Z轴然后从下到上扫描一遍而已。
 * 难点在于如何处理被覆盖三次的面积，这里的超级复杂的PushUp是直接Copy的别人的，自己实在是没想出来。
 * 另外注意的是，这里面的线段树操作非常干净，插入所有边之后整棵树恢复原状。
 * 这样的话每次只需要一次建树就可以了……
 * 这题简直WA死我了，一开始是没注意要把从下往上扫描时符合要求的线段单独拿出来；
 * 然后是没注意排序的时候如果横坐标相同，flag为正的边应该靠前；
 * 最后是发现那长长的PushUp里面居然有笔误?！！！真是跪了……
 * RE一发，CE一发（撞墙），WA六发，去死吧尼玛！！！
 * 不过交题时第一次上首页了，哇咔咔咔……
 * @author FinalTheory
 * @version 0.1
 * @date 2013-05-29
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
#define MAX 2010
#define INF -100000000
#define CLR(arr,val) memset(arr,val,sizeof(arr))
typedef __int64 LL;
using namespace std;
struct NND
{
	int L, R, Cover, calc, once, twice;
} Tree[MAX<<2];
struct TMD
{
	int high, low, x, up, down;
	int flag;
} lines[MAX], to_insert[MAX];
int buffer[MAX];
int buffer_z[MAX];
int height[MAX];
int z_pos[MAX];
void CreateTree( int root, int L, int R )  
{  
	Tree[root].L = L;
	Tree[root].R = R;
	Tree[root].Cover = 0;
	Tree[root].calc = 0;
	Tree[root].once = 0;
	Tree[root].twice = 0;
	if (L == R) return;
	int M = ( L + R ) >> 1;
	CreateTree( L_son, L, M );
	CreateTree( R_son, M + 1, R );
}
bool fuck( const TMD & A, const TMD & B )
{
	if ( A.x != B.x )
		return A.x < B.x;
	else
		return A.flag > B.flag;
}

int BinSearch( int Key, int low, int high )
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
	//由于节点信息没有被PushDown，所以只能分开讨论被覆盖的三种情况
	//如果当前根节点被覆盖三次的话，显然它的长度都有效
	if ( Tree[root].Cover >= 3 )
	{
		Tree[root].once = Tree[root].twice = 0;
		Tree[root].calc = height[Tree[root].R + 1] - height[Tree[root].L];
		return;
	}
	//如果当前节点被覆盖两次
	if ( Tree[root].Cover == 2 )
	{
		//如果是叶子节点，那么没有有效长度和覆盖一次的长度，而被覆盖两次的长度就是节点长度
		if ( Tree[root].L == Tree[root].R )
		{
			Tree[root].twice = height[Tree[root].R + 1] - height[Tree[root].L];
			Tree[root].calc = Tree[root].once = 0;
		}
		//否则，这个节点被覆盖一次的长度一定为零，有效长度是叶子被覆盖1、2、3次的长度之和
		//被覆盖两次的长度更新为节点总长度减去被覆盖三次（即有效长度）的长度，因为当前节点至少被覆盖了两次。
		else
		{
			Tree[root].once = 0;
			Tree[root].calc = Tree[L_son].calc + Tree[R_son].calc \
				+ Tree[L_son].once + Tree[R_son].once\
				+ Tree[L_son].twice + Tree[R_son].twice;
			Tree[root].twice = height[Tree[root].R + 1] - height[Tree[root].L] - Tree[root].calc;
		}
		return;
	}
	if ( Tree[root].Cover == 1 )
	{
		//如果是叶子节点，没有儿子的话不可能有覆盖两次的节点，这时候不存在有效长度。
		if ( Tree[root].L == Tree[root].R )
		{
			Tree[root].calc = Tree[root].twice = 0;
			Tree[root].once = height[Tree[root].R + 1] - height[Tree[root].L];
		}
		else
		{
			//否则的话，有效长度就是左右儿子被覆盖两次及以上的长度和
			Tree[root].calc = Tree[L_son].calc + Tree[R_son].calc \
				+ Tree[L_son].twice + Tree[R_son].twice;
			//被覆盖两次的就是左右儿子被覆盖一次的和
			Tree[root].twice = Tree[L_son].once + Tree[R_son].once;
			//排除掉上面的，剩下的自然就是被覆盖一次的长度和
			Tree[root].once = height[Tree[root].R + 1] - height[Tree[root].L] - Tree[root].calc - Tree[root].twice;
		}
		return;
	}
	if ( Tree[root].Cover == 0 )
	{
		if ( Tree[root].L == Tree[root].R )
			Tree[root].calc = Tree[root].twice = Tree[root].once = 0;
		else
		{
			Tree[root].calc = Tree[L_son].calc + Tree[R_son].calc;
			Tree[root].once = Tree[L_son].once + Tree[R_son].once;
			Tree[root].twice = Tree[L_son].twice + Tree[R_son].twice;
		}
		return;
	}
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
	//std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int n, i, p_lines, p_buffer, p_height, j, index = 1, T, p_z, k, p_insert, left, right;
	int x1, y1, z1, x2, y2, z2;
	LL sum_area, sum_V;
	scanf("%d", &T);
	while ( T-- )
	{
		scanf("%d", &n);
		p_z = p_lines = p_buffer = p_height = 0;
		for ( i = 0; i < n; ++i )
		{
			scanf("%d %d %d %d %d %d", &x1, &y1, &z1, &x2, &y2, &z2);
			buffer[p_buffer++] = y1;
			buffer[p_buffer++] = y2;
			buffer_z[p_z++] = z1;
			buffer_z[p_z++] = z2;
			lines[p_lines].high = y2;
			lines[p_lines].low = y1;
			lines[p_lines].x = x1;
			lines[p_lines].up = z2;
			lines[p_lines].down = z1;
			lines[p_lines++].flag = 1;
			lines[p_lines].high = y2;
			lines[p_lines].low = y1;
			lines[p_lines].x = x2;
			lines[p_lines].up = z2;
			lines[p_lines].down = z1;
			lines[p_lines++].flag = -1;
		}
		sort( buffer, buffer + p_buffer );
		sort( buffer_z, buffer_z + p_z );
		sort( lines, lines + p_lines, fuck );
		int prev = INF, prev_z = INF;
		for ( i = 0, j = k = 1; i < p_buffer; ++i )
		{
			if ( buffer[i] != prev )
				height[j++] = buffer[i];
			if ( buffer_z[i] != prev_z )
				z_pos[k++] = buffer_z[i];
			prev = buffer[i];
			prev_z = buffer_z[i];
		}
		int num_points = j - 1, num_z = k - 1;
		sum_V = 0;
		CreateTree( 1, 1, num_points - 1 );
		for ( j = 1; j < num_z; ++j )
		{
			sum_area = 0;
			p_insert = 0;
			for ( i = 0; i < p_lines; ++i )
				if ( z_pos[j] >= lines[i].down && z_pos[j] < lines[i].up )
					to_insert[p_insert++] = lines[i];
			for ( i = 0; i < p_insert; ++i )
			{
				left = BinSearch( to_insert[i].low, 1, num_points );
				right = BinSearch( to_insert[i].high, 1, num_points ) - 1;
				Insert( 1, left, right, to_insert[i].flag );
				if ( i != p_insert - 1 )
				sum_area += (to_insert[i + 1].x - to_insert[i].x) * (LL)Tree[1].calc;
			}
			sum_V += sum_area * (LL)(z_pos[j + 1] - z_pos[j]);
		}
		printf("Case %d: %I64d\n", index++, sum_V);
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
