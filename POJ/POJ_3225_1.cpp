/**
 * @file POJ_3225_1.cpp
 * @brief   线段树区间更新问题，这里要特别注意异或标记是如何使用的！
 * 把父节点的信息推到儿子之后，一定注意要清空父亲节点的信息！包括异或标记和状态标记！
 * 这里使用了一个很难看的方式进行输出，即DFS所有状态然后输出（sha崽也是这样写的）……
 * 而且用很难看的方式遍历了一遍标记数组。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-05-08
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
#define Father root >> 1
#define MAX 65546
#define BEGIN 2
#define END 65536<<1
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

char flags[END];

struct TMD
{
	int L, R;
	int Signbit, Xorbit;
} Tree[MAX<<3];

void CreateTree( int root, int L, int R )  
{  
	Tree[root].L = L;
	Tree[root].R = R;
	//初始状态下区间不包括元素，并且异或标记为无
	//注意异或标记不设置非法状态
	Tree[root].Signbit = 0;
	Tree[root].Xorbit = 0;
	if (L == R) return ;
	int M = ( L + R ) >> 1;
	CreateTree( L_son, L, M );
	CreateTree( R_son, M + 1, R );
}

void Pushdown( int root )
{
	if ( Tree[root].Signbit != -1 )
	{
		//如果父亲的标记有效，就直接推到儿子
		Tree[L_son].Signbit = Tree[root].Signbit;
		Tree[L_son].Xorbit = 0;
		Tree[R_son].Signbit = Tree[root].Signbit;
		Tree[R_son].Xorbit = 0;
		//将当前根节点标记为非法，即没有被一种状态所完全覆盖
		Tree[root].Signbit = -1;
	}
	else
	{
		//否者的话仅当父亲的异或标记为1才处理
		if ( Tree[root].Xorbit )
		{
			//这时候还要看儿子的标记是否合法，如果合法说明整段都是一个状态
			//直接反过来就可以；如果不合法就只能更新异或标记了。
			if ( Tree[L_son].Signbit != -1 )
				Tree[L_son].Signbit ^= 1;
			else
				Tree[L_son].Xorbit ^= 1;
			if ( Tree[R_son].Signbit != -1 )
				Tree[R_son].Signbit ^= 1;
			else
				Tree[R_son].Xorbit ^= 1;
		}
		//异或标记推下去之后，注意清空根节点的！
		Tree[root].Xorbit = 0;
	}
}

void Update_Bool( int root, int L, int R, int Signbit )
{
	if ( L > R ) return;
	if ( Tree[root].L == L && Tree[root].R == R )
	{
		//对于区间覆盖操作，如果区间刚好匹配，就直接覆盖
		//然后注意要将异或标记清空，因为直接被覆盖掉了
		Tree[root].Signbit = Signbit;
		Tree[root].Xorbit = 0;
		return;
	}
	//不匹配的话把信息推下去
	Pushdown(root);
	int M = ( Tree[root].L + Tree[root].R ) / 2;
	if ( L > M )
	{
		Update_Bool( R_son, L, R, Signbit );
	}
	else if ( R <= M )
	{
		Update_Bool( L_son, L, R, Signbit );
	}
	else
	{
		Update_Bool( L_son, L, M, Signbit );
		Update_Bool( R_son, M + 1, R, Signbit );
	}

}

void Update_Xor( int root, int L, int R )
{
	if ( L > R ) return;
	//如果区间匹配的话，根据情况更新状态标记或者异或标记
	if ( Tree[root].L == L && Tree[root].R == R )
	{
		if ( Tree[root].Signbit != -1 )
			Tree[root].Signbit ^= 1;
		else
			Tree[root].Xorbit ^= 1;
		return;
	}
	//不匹配的话把信息推下去
	Pushdown(root);
	int M = ( Tree[root].L + Tree[root].R ) / 2;
	if ( L > M )
	{
		Update_Xor( R_son, L, R );
	}
	else if ( R <= M )
	{
		Update_Xor( L_son, L, R );
	}
	else
	{
		Update_Xor( L_son, L, M );
		Update_Xor( R_son, M + 1, R );
	}
}

void Query( int root )
{
	if ( Tree[root].Signbit != -1 )
	{
		for ( int i = Tree[root].L; i <= Tree[root].R; ++i )
			flags[i] = Tree[root].Xorbit ^ Tree[root].Signbit;
		return;
	}
	Pushdown(root);
	Query( L_son );
	Query( R_son );
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
	char oper[5], Interval[30], left, right;
	int a, b, i;
	vector<int> res;
	vector<int> :: iterator iter;
	CreateTree( 1, 2, END );
	while ( scanf("%s %s", oper, Interval) != EOF )
	{
		sscanf( Interval, "%c%d%*c%d%c", &left, &a, &b, &right );
		//把区间修正到正整数范围
		a++; b++;
		a += a; b += b;
		//不符合条件的开区间直接跳掉
		if ( a == b && left == '(' && right == ')' ) continue;
		//最后对开区间做修正
		if ( left == '(' ) a++;
		if ( right == ')' ) b--;
		switch ( oper[0] )
		{
		case 'U':
			Update_Bool( 1, a, b, 1 );
			break;
		case 'I':
			Update_Bool( 1, BEGIN, a - 1, 0 );
			Update_Bool( 1, b + 1, END, 0 );
			break;
		case 'D':
			Update_Bool( 1, a, b, 0 );
			break;
		case 'C':
			Update_Bool( 1, BEGIN, a - 1, 0 );
			Update_Bool( 1, b + 1, END, 0 );
			Update_Xor( 1, a, b );
			break;
		case 'S':
			Update_Xor( 1, a, b );
			break;
		}
		//CLR(flags, 0);
		//Query( 1 );
	}
	CLR(flags, 0);
	Query( 1 );
	for ( i = BEGIN - 1; i <= END; ++i )
		if ( flags[i] != flags[i+1] )
			res.push_back( flags[i] ? i : i + 1 );
	if ( res.empty() )
	{
		printf("empty set\n");
	}
	else
	{
		iter = res.begin();
		while ( iter != res.end() )
		{
			if ( *iter % 2 )
				printf( "(%d", (*iter-1)/2 - 1 );
			else
				printf( "[%d", *iter/2 - 1 );
			++iter;
			if ( *iter % 2 )
				printf( ",%d) ", (*iter+1)/2 - 1 );
			else
				printf( ",%d] ", *iter/2 - 1 );
			++iter;
		}
		printf("\n");
	}
#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
