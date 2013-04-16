#include <iostream>
using namespace std;
int main()
{
	freopen("in.txt", "r", stdin);
	unsigned long long a[105], sum;
	int n, i;
	while ( cin >> n )
	{
	sum = 0;
	for ( i = 0; i < n; i++ )
		cin >> a[i];
	sum += a[0];
	for ( i = 1; i < n; i++ )
			sum += ( a[i] - 1 ) * (i + 1) + 1;
	cout << sum << endl;
	}
}