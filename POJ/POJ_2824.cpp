/**
 * @file POJ_2824.cpp
 * @brief   欧拉函数模版题。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-02
 */
#include <iostream>
#include <algorithm>
#include <functional>
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
#include <queue>
#include <iomanip>
#define MAX 3000000
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;
bool prime[MAX+10];
//unsigned long long sum[MAX+10];
int E[MAX+10];

int main()
{
	std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	CLR(prime, 1);
	prime[0] = prime[1] = 0;
	for ( int i = 2; i <= MAX; ++i )
		if ( prime[i] )
			for ( int j = 2 * i; j <= MAX; j += i )
				prime[j] = 0;
	for ( int i = 1; i <= MAX; ++i )
		E[i] = i;
	for ( int i = 2; i <= MAX; ++i )
		if ( prime[i] )
		{
			for ( int j = 2 * i; j <= MAX; j += i )
				E[j] = E[j] / i * ( i - 1 );
			E[i] = i - 1;
		}
// 	for ( int i = 1; i <= MAX; ++i )
// 		sum[i] = sum[i - 1] + E[i];
	int a, b;
	unsigned long long sum;
	while ( cin >> a >> b )
	{
		sum = 0;
		//cout << sum[b] - sum[a - 1] << endl;
		for ( int i = a; i <= b; ++i )
			sum += E[i];
		cout << sum << endl;
	}
#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
