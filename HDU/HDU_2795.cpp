/**
 * @file HDU_2795.cpp
 * @brief   �߶�������������⡣
 * �������Ҫע�����ÿ�ν�������һ��ʼ����ȫ��������Ϊ����̫���MLE��
 * ��Ϊÿ������ĳ�ʼ���ֵ��ȷ���ģ�����ֻ��Ҫÿ�β�ѯʱ�����ڵ㼴�ɡ�
 * �����ڵݹ���õĹ����д���������˵㣬���Խڵ��в��ñ���˵���Ϣ��
 * @author FinalTheory
 * @version 0.1
 * @date 2013-04-25
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
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

int h, w;
int h_pos;

inline int _max( int A, int B )
{
	return A > B ? A : B;
}
struct TMD
{
	int nMax;
	TMD * p_left, * p_right;
	TMD()
	{
		p_left = p_right = NULL;
		nMax = w;
	}
};
stack<TMD *> Pointers;

void Query( TMD * root, int wei, int L, int R )
{
	//����������Һ��ӽڵ�
	if ( root->p_left == NULL )
	{
		root->p_left = new TMD();
		Pointers.push(root->p_left);
	}
	if ( root->p_right == NULL )
	{
		root->p_right = new TMD();
		Pointers.push(root->p_right);
	}
	//��ѯʧ�ܵĻ�ֱ�ӷ���
	if ( root->nMax < wei )
		return;
	if ( L == R )//�����ѯ��Ҷ�ӽڵ㣬������ζ�Ҫ����
	{
		if ( root->nMax >= wei )
		{
			h_pos = L;
			root->nMax -= wei;
		}
		return;
	}
	//�������������Ļ����Ȳ�ѯ������
	int M = ( L + R ) / 2;
	if ( root->p_left->nMax >= wei )
		Query( root->p_left, wei, L, M );
	else
		Query( root->p_right, wei, M + 1, R );
	//�������������ֵ
	root->nMax = _max( root->p_left->nMax, root->p_right->nMax );
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
	int n, i, wei;
	TMD * root;
	while ( scanf( "%d %d %d", &h, &w, &n ) != EOF )
	{
		while ( !Pointers.empty() )
		{
			delete Pointers.top();
			Pointers.pop();
		}
		root = new TMD;
		Pointers.push(root);
		for ( i = 1; i <= n; ++i )
		{
			scanf("%d", &wei);
			h_pos = -1;
			Query( root, wei, 1, h );
			if ( h_pos != -1 )
				printf( "%d\n", h_pos );
			else
				printf("-1\n");
		}
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
