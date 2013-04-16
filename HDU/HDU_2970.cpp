#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <climits>
#include <time.h>
#define MAX(x, y) (x) > (y) ? (x) : (y)
#define MIN(x, y) (x) < (y) ? (x) : (y)
#define SIZE 500005
using namespace std;
struct TMD
{
	int num, index;
} arr[SIZE], arr_bak[SIZE];
char str[SIZE];
bool fuck( TMD A, TMD B )
{
	return A.num < B.num;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int t, n, i;
	int c;
	cin >> t;
	while ( t-- )
	{
		cin >> n;
		c = 'a';
		for ( i = 0; i <= n + 1; i++ )
			arr_bak[i].index = 0;
		for ( i = 1; i <= n; i++ )
		{
			cin >> arr[i].num;
			arr[i].index = i;
			arr_bak[i] = arr[i];
		}
		sort(arr_bak + 1, arr_bak + n + 1, fuck);
		str[arr[1].num] = c;
		for ( i = 1; i < n; i++ )
		{
			if ( arr_bak[arr[i].num + 1].index < arr_bak[arr[i+1].num + 1].index )
				str[arr[i+1].num] = c;
			else
				str[arr[i+1].num] = ++c;
		}
		str[n+1] = 0;
		if ( c <= 'z' )
			printf("%s\n", str+1);
		else
			printf("-1\n");
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cout << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}