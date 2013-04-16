/*
	水题，蒙的，所求概率是牌出现在第一堆的概率。
	回去好好复习概率论吧。
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
#define MAX(x, y) (x) > (y) ? (x) : (y)
#define MIN(x, y) (x) < (y) ? (x) : (y)
#define SWAP(x, y) (x) ^= (y) ^= (x) ^= (y)

using namespace std;
int main()
{
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int T, sum, first, M, i, j;
	cin >> T;
	for ( j = 1; j <= T; j++ )
	{
		cin >> M;
		cin >> first;
		sum = first;
		--M;
		while ( M-- )
		{
			cin >> i;
			sum += i;
		}
		printf("Case %d: %.6lf\n", j, (double)first / sum);
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cout << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}