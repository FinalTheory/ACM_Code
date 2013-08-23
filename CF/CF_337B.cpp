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
typedef long long LL;
LL gcd( LL a, LL b )
{
	if ( a < b ) swap(a, b);
	if ( b == 0 )
		return a;
	else
		return gcd( b, a % b );
}

void Out( LL a, LL b )
{
	LL tmp = gcd(a, b);
	cout << a / tmp << '/' << b / tmp << endl;
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
	LL a, b, c, d;
	while ( cin >> a >> b >> c >> d )
	{
		LL aa, bb, cc, dd;
		aa = a * c;
		bb = b * c;
		cc = c * a;
		dd = d * a;
		if ( bb >= dd )
			Out( aa * bb - cc * dd, aa * bb );
		else
		{
			aa = a * d;
			bb = b * d;
			cc = c * b;
			dd = d * b;
			Out( aa * bb - cc * dd, aa * bb );
		}
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
