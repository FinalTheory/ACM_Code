/**
 * @file POJ_3468.cpp
 * @brief   �߶���ˮ�⣬�����˸��²��������������������ע�͡�
 * @author FinalTheory
 * @version 0.1
 * @date 2013-04-24
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
#define INF 0x3f3f3f3f
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;
typedef long long LL;

inline int max( int a, int b )
{
	return a > b ? a : b;
}
inline int min( int a, int b )
{
	return a < b ? a : b;
}

struct TMD
{
	int L, R;		//�������Ҷ˵�
	LL nSum;		//�������
	LL nInc;		//��������
	TMD * p_left, * p_right;	//��������ָ��
	TMD()
	{
		p_left = p_right = NULL;
		nSum = nInc = 0;
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
//��Ԫ�ز����߶���
void Insert( TMD * root, LL num, int pos )
{
	if ( pos >= root->L && pos <= root->R )
		root->nSum += num;
	if ( root->L == pos && root->R == pos )
		return;
	int M = ( root->L + root->R ) / 2;
	if ( pos > M )
		Insert( root->p_right, num, pos );
	else
		Insert( root->p_left, num, pos );
}

void Add( TMD * root, int L, int R, int num )
{
	//�������ƥ��Ļ�ֱ�Ӹ�������������һֱ����Ҷ��
	if ( root->L == L && root->R == R )
	{
		root->nInc += num;
		return;
	}
	//����ȫƥ��Ļ��϶�Ҳ��֤���ڷ�Χ�ڣ����ԶԵ�ǰ����ֱ�������Ϳ���
	root->nSum += ( R - L + 1 ) * num;
	int M = ( root->L + root->R ) / 2;
	if ( L > M )
	{
		Add( root->p_right, L, R, num );
	}
	else if ( R <= M )
	{
		Add( root->p_left, L, R, num );
	}
	else
	{
		Add( root->p_left, L, M, num );
		Add( root->p_right, M + 1, R, num );
	}
}

LL Query( TMD * root, int L, int R )
{
	//��ѯ����ƥ��Ļ�ֱ�ӷ���ֵ
	if ( root->L == L && root->R == R )
		return root->nSum + root->nInc * ( R - L + 1 );
	//���������ƥ�䣬���ȸ��µ�ǰ��������
	root->nSum += root->nInc * ( root->R - root->L + 1 );
	int M = ( root->L + root->R ) / 2;
	//Ȼ����������ݸ�������������յ�ǰ�ڵ������
	if ( root->nInc != 0 )
	{
		Add( root->p_left, root->L, M, root->nInc );
		Add( root->p_right, M + 1, root->R, root->nInc );
		root->nInc = 0;
	}
	//�����������ݹ��ѯ
	if ( L > M )
	{
		return Query( root->p_right, L, R );
	}
	else if ( R <= M )
	{
		return Query( root->p_left, L, R );
	}
	else
	{
		return Query( root->p_left, L, M ) + Query( root->p_right, M + 1, R );
	}
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

	int N, Q, i, a, b, c;
	char com;
	LL num;
	TMD * root;
	while ( scanf("%d %d", &N, &Q) != EOF )
	{
		//�ͷ��ڴ�
		while ( !Pointers.empty() )
		{
			delete Pointers.top();
			Pointers.pop();
		}

		root = CreateTree( 1, N );

		for ( i = 1; i <= N; ++i )
		{
			scanf("%lld", &num);
			Insert( root, num, i );
		}
		for ( i = 1; i <= Q; ++i )
		{
			do 
			{
				com = getchar();
			} while ( com == '\n' );
			if ( com == 'C' )
			{
				scanf( "%d %d %d", &a, &b, &c );
				Add( root, a, b, c );
			}
			else
			{
				scanf("%d %d", &a, &b);
				printf( "%lld\n", Query( root, a, b ) );
			}
		}

	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
