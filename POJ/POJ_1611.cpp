/**
 * @file POJ_1611.cpp
 * @brief   ���鼯���⣬�����ͳ����ڱ��������������������������֪�����ԡ�����ûд��
 * �����������Ǽ��ÿ��С�飬��������и��ڵ���0���ˣ��ͽ������������˵ĸ��ڵ��Ϊ�㡣
 * �����Ϊ��һ���˵ĸ��ڵ�Ϳ����ˡ��������������б�����Ǳ���Ⱦ�ˣ��ͻ��ҵ������ĸ��ڵ���Ϊ0.
 * ����������˵ĸ��ڵ㣬ÿ����0�ı�ʾ����Ⱦ�ˣ�����ܺͼ��ɡ�ע���·��ѹ����find������
 * @author FinalTheory
 * @version 0.1
 * @date 2013-07-16
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
#define MAX 30010
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

int Set[MAX];
int peoples[MAX];

int find( int x )
{
	int r = x, i = x, j;
	while ( Set[r] != r )
		r = Set[r];
	while ( i != r )
	{
		j = Set[i];
		Set[i] = r;
		i = j;
	}
	return r;
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
	int n, m;
	while ( scanf("%d %d", &n, &m) && n + m )
	{
		for ( int i = 0; i < n; ++i )
			Set[i] = i;
		for ( int i = 0; i < m; ++i )
		{
			int k, root = -1;;
			scanf("%d", &k);
			for ( int j = 0; j < k; ++j )
			{
				scanf("%d", &peoples[j]);
				//����ҵ���Ⱦ�ߣ��Ͱѵ�ǰ���ϵ������˶���Ϊ��Ⱦ
				if ( find(peoples[j]) == 0 )
					root = 0;
			}
			//���û���ҵ����Ͱ������˵ĸ�������Ϊ��һ���˵ĸ���
			if ( root == -1 )
				root = find( peoples[0] );
			for ( int j = 0; j < k; ++j )
				Set[find(peoples[j])] = root;
		}
		int sum = 0;
		for ( int i = 0; i < n; ++i )
		{
			if ( find(i) == 0 )
				sum++;
		}
		printf("%d\n", sum);
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
