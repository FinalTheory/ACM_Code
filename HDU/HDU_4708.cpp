/**
 * @file HDU_4708.cpp
 * @brief   模拟题，直接转一遍枚举最大值就行。笔误一次WA了一发。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-09-11
 */
#if defined(__GNUC__)
#pragma GCC optimize ("O2")
#endif
#if defined(_MSC_VER)
#pragma comment(linker, "/STACK:36777216")
#endif
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <bitset>
#include <stack>
#include <queue>
#include <deque>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cctype>
#include <climits>
#include <ctime>
#define CLR(arr,val) memset(arr,val,sizeof(arr))
using namespace std;
const int INF = 0x3f3f3f3f;

int mat[20][20], tmp[20][20];
int n;
void Rotate( int layer, int elem )
{
	memcpy( tmp, mat, sizeof(tmp) );
	for ( int i = 1; i <= elem - 1;  ++i )
	{
		tmp[i + layer - 1][layer] = mat[i + layer][layer];
		tmp[layer][i + layer] = mat[layer][i + layer - 1];
		tmp[i + layer][n - layer + 1] = mat[i + layer - 1][n - layer + 1];
		tmp[n - layer + 1][i + layer - 1] = mat[n - layer + 1][i + layer];
	}
	memcpy( mat, tmp, sizeof(tmp) );
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
	while ( scanf("%d", &n) && n )
	{
		for ( int i = 1; i <= n; ++i )
			for ( int j = 1; j <= n; ++j )
				scanf("%d", &mat[i][j]);
		int sum = 0, max_sum, min_step, steps = 0, step;
		for ( int pos = 1, elem = n; pos <= n / 2; ++pos, elem -= 2 )
		{
			max_sum = mat[pos][pos] + mat[n - pos + 1][n - pos + 1] + mat[pos][n - pos + 1] + mat[n - pos + 1][pos];
			min_step = 0;
			for ( int k = 1; k <= (elem - 1) * 4; ++k )
			{
				Rotate(pos, elem);
				int kkk = mat[pos][pos] + mat[n - pos + 1][n - pos + 1] + mat[pos][n - pos + 1] + mat[n - pos + 1][pos];
				if ( k > ( elem - 1 ) * 2 ) step = ( elem - 1 ) * 4 - k;
				else step = k;
				if ( kkk > max_sum || ( kkk == max_sum && step < min_step ) )
				{
					max_sum = kkk;
					min_step = step;
				}
			}
			sum += max_sum;
			steps += min_step;
		}
		sum += mat[n / 2 + 1][n / 2 + 1];
		printf("%d %d\n", sum, steps);
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
