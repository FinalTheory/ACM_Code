/**
 * @file CF_234D.cpp
 * @brief   坑死人的模拟，必须认真读题啊，边界，跪了！
 * 需要注意的就是如何计算每场电影如果有没记住的演员的话，至少会有几个是喜欢的。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-13
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
set<int> favourate;
vector<int> m_list[110];
int min_possible_actors[110], max_possible_actors[110];
int m, k, n;
int check( int index )
{
	set<int> :: iterator iter;
// 	int num_match = 0, num_zeros = 0, nums_not_match = 0;
// 	for ( int i = 0; i < m_list[index].size(); ++i )
// 	{
// 		if ( m_list[index][i] == 0 )
// 		{
// 			num_zeros++;
// 			continue;
// 		}
// 		iter = favourate.find( m_list[index][i] );
// 		if ( iter != favourate.end() )
// 			num_match++;
// 		else
// 			nums_not_match++;
// 	}
	int greater = 0, smaller = 0;
	for ( int i = 1; i <= n; ++i ) if ( i != index )
	{
		if ( min_possible_actors[index] >= max_possible_actors[i] )
			++greater;
		if ( max_possible_actors[index] < min_possible_actors[i] )
			++smaller;
	}
	if ( greater == n - 1 )
		return 0;
	else if ( smaller > 0 )
		return 1;
	else
		return 2;
}

int main()
{
	std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#else
	freopen( "input.txt", "r", stdin );
	freopen( "output.txt", "w", stdout );
#endif
	int d;
	char names[20];
	set<int> :: iterator iter;
	while ( scanf("%d %d", &m, &k) != EOF )
	{
		CLR( min_possible_actors, 0 );
		CLR( max_possible_actors, 0 );
		favourate.clear();
		for ( int i = 1; i <= k; ++i )
		{
			int index;
			scanf("%d", &index);
			favourate.insert(index);
		}
		scanf("%d", &n);
		for ( int i = 1; i <= n; ++i )
		{
			m_list[i].clear();
			int num_actors = 0, num_zeros = 0, num_not_match = 0;
			scanf("%s %d",names, &d);
			for ( int j = 1; j <= d; ++j )
			{
				int actor;
				scanf("%d", &actor);
				m_list[i].push_back(actor);
				if ( actor == 0 )
				{
					num_zeros++;
					continue;
				}
				if ( ( iter = favourate.find(actor) ) != favourate.end() )
					num_actors++;
				else
					num_not_match++;
			}
			min_possible_actors[i] = num_actors + max(0, num_zeros - (m - k - num_not_match));
			max_possible_actors[i] = num_zeros + num_actors;
			if ( max_possible_actors[i] > favourate.size() )
				max_possible_actors[i] = favourate.size();
		}
		for ( int i = 1; i <= n; ++i )
			cout << check( i ) << endl;
	}
	
#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
