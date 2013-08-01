/**
 * @file POJ_1020.cpp
 * @brief   特别恶心我的一道搜索题目。主要理解是如何进行剪枝优化的。
 * 摆放正方形的顺序需要经过特殊处理。用一个一维数组记录每一列有多少个已经被放满的位置。
 * 这样的记录方式可以完全还原出当前局面，但是需要对搜索时的摆放方式有一定要求。
 * 这里的思路是，每次找一个最低的位置，从左到右从上到下尝试把一个正方形放进去。
 * 只有放满了每一层之后才会继续放下一层。这样数组中记录的就是完全对应的局面了。
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
//每列被占用的方格数量
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
	//寻找最低的位置
	for ( int x = 0; x < s; ++x )
		if ( col_num[x] < low ) { low = col_num[x]; low_pos = x; }
	for ( int len = 10; len >= 1; --len )
	{
		if ( num[len] > 0 && low_pos + len <= s && low + len <= s )
		{
			gonext = true;
			for ( int i = low_pos; i < low_pos + len; ++i )
				//这里如果写成下面的写法就会TLE
				//if ( col_num[i] + len > s ) { gonext = false; break; }
				//因为如果想要放在这个最低位置的话，要求右边所有的都不能比最低位置高
				//而不是只要能放下就可以。所以原来的写法是错误的。
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
