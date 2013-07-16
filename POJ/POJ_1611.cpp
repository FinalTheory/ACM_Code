/**
 * @file POJ_1611.cpp
 * @brief   并查集问题，上来就沉迷于暴力的做法，后来认真想了想才知道不对。好在没写。
 * 大体做法就是检查每个小组，如果里面有根节点是0的人，就将这个组的所有人的根节点改为零。
 * 否则改为第一个人的根节点就可以了。这样如果这个组有别的人是被感染了，就会找到这个组的根节点标记为0.
 * 最后检查所有人的根节点，每个是0的表示被感染了，输出总和即可。注意带路径压缩的find函数。
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
				//如果找到感染者，就把当前集合的所有人都设为感染
				if ( find(peoples[j]) == 0 )
					root = 0;
			}
			//如果没有找到，就把所有人的父亲设置为第一个人的父亲
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
