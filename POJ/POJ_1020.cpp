/**
 * @file POJ_1020.cpp
 * @brief   �ر�����ҵ�һ��������Ŀ����Ҫ�������ν��м�֦�Ż��ġ�
 * �ڷ������ε�˳����Ҫ�������⴦����һ��һά�����¼ÿһ���ж��ٸ��Ѿ���������λ�á�
 * �����ļ�¼��ʽ������ȫ��ԭ����ǰ���棬������Ҫ������ʱ�İڷŷ�ʽ��һ��Ҫ��
 * �����˼·�ǣ�ÿ����һ����͵�λ�ã������Ҵ��ϵ��³��԰�һ�������ηŽ�ȥ��
 * ֻ�з�����ÿһ��֮��Ż��������һ�㡣���������м�¼�ľ�����ȫ��Ӧ�ľ����ˡ�
 * @author FinalTheory
 * @version 0.1
 * @date 2013-07-21
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

#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

int num[15];
//ÿ�б�ռ�õķ�������
int col_num[50];
int s, depth;

bool suc;

void DFS( int n )
{
	if ( suc )
		return;
	if ( n >= depth )
	{
		suc = 1;
		return;
	}
	int low = 50, low_pos = -1;
	bool gonext;
	//Ѱ����͵�λ��
	for ( int x = 0; x < s; ++x )
		if ( col_num[x] < low ) { low = col_num[x]; low_pos = x; }
	for ( int len = 10; len >= 1; --len )
	{
		if ( num[len] > 0 && low_pos + len <= s && low + len <= s )
		{
			gonext = true;
			for ( int i = low_pos; i < low_pos + len; ++i )
				//�������д�������д���ͻ�TLE
				//if ( col_num[i] + len > s ) { gonext = false; break; }
				//��Ϊ�����Ҫ����������λ�õĻ���Ҫ���ұ����еĶ����ܱ����λ�ø�
				//������ֻҪ�ܷ��¾Ϳ��ԡ�����ԭ����д���Ǵ���ġ�
				if ( col_num[i] > low ) { gonext = false; break; }
			if ( gonext )
			{
				for ( int j = low_pos; j < low_pos + len; ++j )
					col_num[j] += len;
				num[len]--;
				DFS(n + 1);
				for ( int j = low_pos; j < low_pos + len; ++j )
					col_num[j] -= len;
				num[len]++;
			}
		}
	}
}

bool fuck( int a, int b )
{
	return a > b;
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
	int t, n, sum, tmp;
	cin >> t;
	while ( t-- )
	{
		CLR(num, 0); CLR(col_num, 0);
		sum = 0;
		cin >> s >> n;
		for ( int i = 0; i < n; ++i )
		{
			cin >> tmp;
			sum += tmp * tmp;
			num[tmp]++;
		}
		if ( sum != s * s )
		{
			cout << "HUTUTU!" << endl;
			continue;
		}
		suc = 0; depth = n;
		DFS(0);
		if ( suc )
			cout << "KHOOOOB!" << endl;
		else
			cout << "HUTUTU!" << endl;
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
