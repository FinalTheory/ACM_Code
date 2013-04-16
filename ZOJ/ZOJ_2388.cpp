/*
	完全的水题
*/

#include <iostream>
using namespace std;
int main()
{
	int n, s, d;
	//freopen("123.txt", "r", stdin);
	cin >> n;
	while ( n-- )
	{
		cin >> s >> d;
		if ( s % 2 && !(d % 2) || !( s % 2 ) && d % 2 )
		{
			cout << "impossible\n";
			continue;
		}
		if ( ( s + d ) / 2  >= 0 && ( s - d ) / 2  >= 0 )
			cout << ( s + d ) / 2  << ' ' << ( s - d ) / 2  << '\n';
		else
			cout << "impossible\n";
	}
}