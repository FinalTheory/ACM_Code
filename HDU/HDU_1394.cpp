/**
 * @file HDU_1394.cpp
 * @brief   �����߶���������ԡ�
 * ����˼���ǽ�ȡֵ��Χ��Ϊ���䣬�����Ϳ��Կ���ͳ��ĳ��ȡֵ��Χ�����ж��ٸ�����
 * ����˳�����ÿһ��������Ӧ��������������ӣ�Ȼ��ͳ�Ʊ����������ж��ٸ���
 * ��Ϊ��ѯ���ı������һ������ǰ����ģ�������������
 * ��ó�ʼ�����ֱ�ӵ��ƾͿ������ʣ�µģ���¼һ����Сֵ�Ϳ����ˡ�
 * ���������������������Լ���ε���ʣ�µ�����ԡ�
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
int nums[5010];
//ע�������ǽ�ĳ��ȡֵ��Χ��Ϊ����!
struct TMD
{
	int L, R;
	int nNum;   //ĳһ��ȡֵ��Χ�������ж��ٸ���
	TMD * p_left, * p_right;
	TMD()
	{
		p_left = p_right = NULL;
		nNum = 0;
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
void Insert( TMD * root, int num )
{
	root->nNum++;
	if ( root->L == num && root->R == num )
		return;
	int M = ( root->L + root->R ) / 2;
	if ( num > M )
		Insert( root->p_right, num );
	else
		Insert( root->p_left, num );
}
int Query( TMD * root, int L, int R )
{
	if ( root->L == L && root->R == R )
		return root->nNum;
	int M = ( root->L + root->R ) / 2;
	if ( R <= M )
		return Query( root->p_left, L, R );
	else if ( L > M )
		return Query( root->p_right, L, R );
	else
		return Query( root->p_left, L, M ) + Query( root->p_right, M + 1, R );
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
	int n, i, sum, min_sum, start_point;
	TMD * root;
	while ( scanf("%d", &n) != EOF )
	{
		//�ƺ������ͷ��ڴ���
		root = CreateTree( 1, n );
		for ( i = 1; i <= n; ++i )
			scanf("%d", nums + i);
		sum = 0;
		for ( i = 1; i <= n; ++i )
		{
			if ( nums[i] < n - 1 )
				sum += Query( root, nums[i] + 2, n );
			Insert( root, nums[i] + 1 );
		}
		min_sum = sum;
		for ( i = 1; i <= n; ++i )
		{
			int tmp = nums[i] + 1;
			//��һ�����Ʒǳ���Ҫ��
			//ÿ���ƶ�˳�������һ�������һ�ε��������
			sum = sum - ( tmp - 1 ) + ( n - tmp );
			if ( sum < min_sum )
				min_sum = sum;
		}
		printf( "%d\n", min_sum );
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
