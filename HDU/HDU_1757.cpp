/**
 * @file HDU_1757.cpp
 * @brief   比较标准的矩阵快速幂乘法，重要的是推出公式。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-10-26
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
#define MAX 10
#define CLR(arr,val) memset(arr,val,sizeof(arr))
using namespace std;
const int INF = 0x3f3f3f3f;
int MOD;
struct Mat
{
	int val[MAX][MAX];
} M;
inline Mat Mul( Mat A, Mat B )
{
	Mat res;
	CLR(res.val, 0);
	for ( int i = 0; i < MAX; ++i )
	for ( int j = 0; j < MAX; ++j )
	for ( int k = 0; k < MAX; ++k )
	{
		res.val[i][j] += A.val[i][k] * B.val[k][j];
		res.val[i][j] %= MOD;
	}
	return res;
}

Mat Fast_Mul( Mat A, int k )
{
	if ( k == 1 ) return A;
	A = Fast_Mul( A, k / 2 );
	if ( k % 2 )
		return Mul( Mul ( A, A ), M );
	else
		return Mul( A, A );
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
	int k, ans;
	for ( int i = 1; i <= 9; ++i )
		M.val[i][i - 1] = 1;
	while ( scanf("%d %d", &k, &MOD) != EOF )
	{
		for ( int i = 0; i < 10; ++i )
			scanf("%d", &M.val[0][i]);
		if ( k < 10 )
		{
			printf("%d", k);
			continue;
		}
		Mat res = Fast_Mul(M, k - 9);
		ans = 0;
		for ( int i = 0; i < 10; ++i )
		{
			ans += res.val[0][i] * ( 9 - i );
			ans %= MOD;
		}
		printf("%d\n", ans);
	}
#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
