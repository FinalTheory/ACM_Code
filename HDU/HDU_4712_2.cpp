/**
 * @file HDU_4712_2.cpp
 * @brief   这题本身由于解空间小数据弱，所以可以用随机化算法乱搞。
 *	    这里使用搜索算法，考虑异或运算的性质：取两个数A ^ B = T，两边同时异或B，有：
 *	    A ^ B ^ B = T ^ B，又有B ^ B = 0，且A ^ 0 = A，所以有A = T ^ B。
 *	    也就是我们可以枚举含有1的个数为n的T，当T ^ B的结果在输入集合中时（用一个_hash数组实现），
 *	    我们就认为这个是合法解。从小到大枚举n，找到合法解后立刻停止即可。
 *	    表面上来看，这个算法的最坏时间复杂度是O(N*2^20)，但是实际上要好得多。
 *	    首先我们考虑输入中有重复数字，这样答案显然是零，可以立刻处理；
 *	    对于输入规模达到10W的数据，互不相同的前提下，根据抽屉原理，可以填满将近17个二进制位。
 *	    这也就是说对于超大规模的数据，答案最多只需要搜索到4就足够了。
 *	    这样来看，其实换种搜索方式的话完全可以满足时间要求，事实上还是绰绰有余的。
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
bool _hash[INF];
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

int ans, N;

bool DFS( int num, int pos, int depth )
{
	
	if ( depth == ans )
	{
		for ( int i = 0; i < N; ++i )
		{
			int tmp = num ^ nums[i];
			if ( _hash[tmp] )
				return true;
		}
		return false;
	}
	for ( int i = pos; i < 20; ++i )
		if ( DFS( num + ( 1 << i ), i + 1, depth + 1 ) )
			return true;
	return false;
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
	int T, res, A, B, _min;
	scanf("%d", &T);
	srand(time(NULL));
	for ( char i = '0'; i <= '9'; ++i ) _map[i] = i - '0';
	for ( char i = 'A'; i <= 'F'; ++i ) _map[i] = i - 'A' + 10;
	while ( T-- )
	{
		CLR(_hash, 0);
		scanf("%d", &N);
		bool flag = false;
		for ( int i = 0; i < N; ++i )
		{
			read(i);
			if ( !_hash[nums[i]] )
				_hash[nums[i]] = true;
			else
				flag = true;
		}
		if ( flag ) {
			puts("0");
			continue;
		}
		_min = 20; ans = 1;
		while ( !DFS( 0, 0, 0 ) ) ans++;
		printf("%d\n", ans);
next:;
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
