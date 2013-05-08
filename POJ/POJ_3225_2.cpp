/**
 * @file POJ_3225_2.cpp
 * @brief   取消了没有意义的区间修正，然后学习sha崽的方式用了一个小trick进行输出。
 * 注意这里是怎样处理空格以及边界的，直接遍历一遍flags数组即可，不用特意考虑两端元素。
 * @author FinalTheory
 * @version 1.0
 * @date 2013-05-08
 */
#include <cstdio>
#define L_son root << 1
#define R_son root << 1 | 1
#define MAX 65546
#define maxn 65535<<1
#define CLR(arr,val) memset(arr,val,sizeof(arr))
using namespace std;
char flags[(maxn)+10];

struct TMD
{
	int L, R;
	int Signbit, Xorbit;
} Tree[MAX<<3];

void CreateTree( int root, int L, int R )  
{  
	Tree[root].L = L;
	Tree[root].R = R;
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
		Tree[L_son].Signbit = Tree[root].Signbit;
		Tree[L_son].Xorbit = 0;
		Tree[R_son].Signbit = Tree[root].Signbit;
		Tree[R_son].Xorbit = 0;
		Tree[root].Signbit = -1;
	}
	else
	{
		if ( Tree[root].Xorbit )
		{
			if ( Tree[L_son].Signbit != -1 )
				Tree[L_son].Signbit ^= 1;
			else
				Tree[L_son].Xorbit ^= 1;
			if ( Tree[R_son].Signbit != -1 )
				Tree[R_son].Signbit ^= 1;
			else
				Tree[R_son].Xorbit ^= 1;
		}
		Tree[root].Xorbit = 0;
	}
}

void Update_Bool( int root, int L, int R, int Signbit )
{
	if ( L > R ) return;
	if ( Tree[root].L == L && Tree[root].R == R )
	{
		Tree[root].Signbit = Signbit;
		Tree[root].Xorbit = 0;
		return;
	}
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
	if ( Tree[root].L == L && Tree[root].R == R )
	{
		if ( Tree[root].Signbit != -1 )
			Tree[root].Signbit ^= 1;
		else
			Tree[root].Xorbit ^= 1;
		return;
	}
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
	char oper[5], Interval[30], left, right;
	int a, b, i;
	CreateTree( 1, 0, maxn );
	while ( scanf("%s %s", oper, Interval) != EOF )
	{
		sscanf( Interval, "%c%d%*c%d%c", &left, &a, &b, &right );
		a <<= 1; b <<= 1;
		if ( a == b && (left == '(' || right == ')') ) continue;
		if ( left == '(' ) a++;
		if ( right == ')' ) b--;
		switch ( oper[0] )
		{
		case 'U':
			Update_Bool( 1, a, b, 1 );
			break;
		case 'I':
			Update_Bool( 1, 0, a - 1, 0 );
			Update_Bool( 1, b + 1, maxn, 0 );
			break;
		case 'D':
			Update_Bool( 1, a, b, 0 );
			break;
		case 'C':
			Update_Bool( 1, 0, a - 1, 0 );
			Update_Bool( 1, b + 1, maxn, 0 );
			Update_Xor( 1, a, b );
			break;
		case 'S':
			Update_Xor( 1, a, b );
			break;
		}
	}
	Query( 1 );
	int start = -1, end;
	char outed = 0;
	for ( i = 0; i <= maxn; ++i )
	{
		if ( flags[i] )
		{
			if ( start == -1 ) start = i;
			end = i;
		}
		else
		{
			if ( start != -1 )
			{
				if ( outed )
					printf(" ");
				outed = 1;
				printf( "%c%d,%d%c", start & 1 ? '(' : '[', start >> 1,\
					( end + 1 ) >> 1, end & 1 ? ')' : ']' );
				start = -1;
			}
		}
	}
	if ( !outed )
		printf("empty set");
	printf("\n");
}
