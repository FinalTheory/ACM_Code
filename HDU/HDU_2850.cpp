/**
 * @file HDU_2850.cpp
 * @brief   贪心水题，原本问题是NP的，但是不要求最优。
 * 敢不敢写是个问题，一开始思路对的但是莫名其妙地WA，后来改用优先队列就好了。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-06
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
#define MAX 100010
#define CLR(arr,val) memset(arr,val,sizeof(arr))
typedef unsigned long long LL;
using namespace std;
int N, M;
struct TMD
{
	int time;
	int index;
} jobs[MAX];

struct NND
{
	int index;
	LL time;
};

bool operator <( const NND & A, const NND & B )
{
	return A.time > B.time;
}

int res[MAX];
const LL INF = 1000000000000ULL;

priority_queue<NND> q;



bool fuck( const TMD & A, const TMD & B )
{
	if ( A.time != B.time )
		return A.time > B.time;
	else
		return A.index > B.index;
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
	int C;
	NND tmp;
	scanf("%d", &C);
	while ( C-- )
	{
		scanf("%d %d", &N, &M);
		while ( !q.empty() ) q.pop();
		for ( int i = 1; i <= N; ++i )
		{
			jobs[i].index = i;
			scanf("%d", &jobs[i].time);
		}
		sort( jobs + 1, jobs + N + 1, fuck );
		int stop = min( N, M );
		for ( int i = 0; i < M; ++i )
		{
			tmp.time = 0;
			tmp.index = i;
			q.push(tmp);
		}
		for ( int i = 1; i <= N; ++i )
		{
			tmp = q.top(); q.pop();
			tmp.time += jobs[i].time;
			res[jobs[i].index] = tmp.index;
			q.push(tmp);
		}
		printf("%d\n", N);
		printf("%d", res[1]);
		for ( int i = 2; i <= N; ++i )
			printf(" %d", res[i]);
		puts("");
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
