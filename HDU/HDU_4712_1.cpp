/**
 * @file HDU_4712_1.cpp
 * @brief   此题解空间很小但是枚举复杂度很高，所以直接用随机算法乱搞来枚举，有很大概率找到最小值。
 *	    枚举次数最好先估算一下，在尽量不超时的前提下尽可能多枚举几次。
 * @feeling 居然有这种淫荡的算法，跪了！
 * @author FinalTheory
 * @version 0.1
 * @date 2013-09-10
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
#define MAX 100010
#define CLR(arr,val) memset(arr,val,sizeof(arr))
using namespace std;
const int INF = 1 << 20;
const int base = 0x10;

int nums[MAX], _map[256];
char buffer[10];
inline void read( int idx )
{
	int sum = 0;
	scanf("%s", buffer);
	for ( int i = 0; i < 5; ++i )
	{
		sum *= 16;
		sum += _map[buffer[i]];
	}
	nums[idx] = sum;
}
inline int check( int num )
{
	int ans = 0;
	for ( int i = 0; i < 20; ++i ) if ( (num >> i) & 1 )
		ans++;
	return ans;
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
	int T, N, res, A, B, _min, ans;
	scanf("%d", &T);
	srand(time(NULL));
	for ( char i = '0'; i <= '9'; ++i ) _map[i] = i - '0';
	for ( char i = 'A'; i <= 'F'; ++i ) _map[i] = i - 'A' + 10;
	while ( T-- )
	{
		scanf("%d", &N);
		for ( int i = 0; i < N; ++i )
			read(i);
		_min = 20;
		for ( int i = 0; i < 600000; ++i )
		{
			A = rand() % N;
			B = rand() % N;
			if ( A == B ) continue;
			ans = check(nums[A ]^ nums[B]);
			if ( ans < _min )
				_min = ans;
		}
		printf("%d\n", _min);
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
