#include <iostream>
#include <set>
#include <sstream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cctype>
#include <climits>
#include <ctime>
#include <vector>
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

int MAX( int A, int B )
{
	return A > B ? A : B;
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
	int DP[1010];
	int N, price[1010], i, j, money, maxmoney;
	char flags[1010];
	while ( cin >> N && N )
	{
		memset(price, 0, sizeof(price));
		for ( i = 0 ; i < N; ++i )
			cin >> price[i];
		cin >> money;
		sort( price, price + N );
		memset( flags, 0, sizeof(flags) );
		memset(DP, 0, sizeof(DP));
		if ( money >= 5 )
		{
			for ( i = 0; i < N - 1; ++i )
				for ( j = money - 5; j >= price[i]; j-- )
				{
					if ( DP[j] < DP[j-price[i]] + price[i] )
					{
						DP[j] = DP[j-price[i]] + price[i];
						flags[i] = 1;
					}
				}
		}
		else
		{
			cout << money << endl;
			continue;
		}
		maxmoney = -1;
		for ( i = 0; i < 1010; ++i )
			if ( DP[i] > maxmoney )
				maxmoney = DP[i];
		money -= maxmoney;
		money -= price[N-1];
		cout << money << endl;
	}


#ifndef ONLINE_JUDGE
	program_end = clock();
	cout << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
