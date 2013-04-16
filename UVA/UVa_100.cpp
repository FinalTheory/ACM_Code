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
	int a, b, i, m, n, step, step_max;
	unsigned num;
	while ( cin >> a >> b )
	{
		m = a; n = b;
		if ( m > n )
			SWAP(m, n);
		step_max = 0;
		for ( i = m; i <= n; i++ )
		{
			step = 0;
			num = i;
			while ( num != 1 )
			{
				++step;
				if ( num % 2 )
					num = num * 3 + 1;
				else
					num /= 2;
			}
			if ( step > step_max )
				step_max = step;
		}
		printf("%d %d %d\n", a, b, step_max + 1);
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cout << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}