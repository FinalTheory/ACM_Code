/**
 * @file POJ_3225_1.cpp
 * @brief   �߶�������������⣬����Ҫ�ر�ע������������ʹ�õģ�
 * �Ѹ��ڵ����Ϣ�Ƶ�����֮��һ��ע��Ҫ��ո��׽ڵ����Ϣ����������Ǻ�״̬��ǣ�
 * ����ʹ����һ�����ѿ��ķ�ʽ�����������DFS����״̬Ȼ�������sha��Ҳ������д�ģ�����
 * �����ú��ѿ��ķ�ʽ������һ�������顣
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
	//��ʼ״̬�����䲻����Ԫ�أ����������Ϊ��
	//ע������ǲ����÷Ƿ�״̬
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
		//������׵ı����Ч����ֱ���Ƶ�����
		Tree[L_son].Signbit = Tree[root].Signbit;
		Tree[L_son].Xorbit = 0;
		Tree[R_son].Signbit = Tree[root].Signbit;
		Tree[R_son].Xorbit = 0;
		//����ǰ���ڵ���Ϊ�Ƿ�����û�б�һ��״̬����ȫ����
		Tree[root].Signbit = -1;
	}
	else
	{
		//���ߵĻ��������׵������Ϊ1�Ŵ���
		if ( Tree[root].Xorbit )
		{
			//��ʱ��Ҫ�����ӵı���Ƿ�Ϸ�������Ϸ�˵�����ζ���һ��״̬
			//ֱ�ӷ������Ϳ��ԣ�������Ϸ���ֻ�ܸ���������ˡ�
			if ( Tree[L_son].Signbit != -1 )
				Tree[L_son].Signbit ^= 1;
			else
				Tree[L_son].Xorbit ^= 1;
			if ( Tree[R_son].Signbit != -1 )
				Tree[R_son].Signbit ^= 1;
			else
				Tree[R_son].Xorbit ^= 1;
		}
		//���������ȥ֮��ע����ո��ڵ�ģ�
		Tree[root].Xorbit = 0;
	}
}

void Update_Bool( int root, int L, int R, int Signbit )
{
	if ( L > R ) return;
	if ( Tree[root].L == L && Tree[root].R == R )
	{
		//�������串�ǲ������������պ�ƥ�䣬��ֱ�Ӹ���
		//Ȼ��ע��Ҫ���������գ���Ϊֱ�ӱ����ǵ���
		Tree[root].Signbit = Signbit;
		Tree[root].Xorbit = 0;
		return;
	}
	//��ƥ��Ļ�����Ϣ����ȥ
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
	//�������ƥ��Ļ��������������״̬��ǻ��������
	if ( Tree[root].L == L && Tree[root].R == R )
	{
		if ( Tree[root].Signbit != -1 )
			Tree[root].Signbit ^= 1;
		else
			Tree[root].Xorbit ^= 1;
		return;
	}
	//��ƥ��Ļ�����Ϣ����ȥ
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
		//��������������������Χ
		a++; b++;
		a += a; b += b;
		//�����������Ŀ�����ֱ������
		if ( a == b && left == '(' && right == ')' ) continue;
		//���Կ�����������
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
