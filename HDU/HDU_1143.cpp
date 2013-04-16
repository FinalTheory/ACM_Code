/*
	递推问题，特殊的地方在于每一个当前状态由之前所有状态决定。
	公式：f(n)=3*f(n-2)+2*f(n-4)+2*f(n-6)+……+2*f(0)
	该公式由图形的特性决定！
*/
#include <cstdlib>
#include <cmath>
#include <iostream> 
using namespace std;
unsigned long long num[31] = {1};
int main()
{
	int i, j, n;
	for ( i = 2; i <= 30; i += 2 )
	{
		num[i] += 3 * num[i-2];
		for ( j = i - 4; j >= 0; j -= 2 )
			num[i] += 2 * num[j];
	}
	while (1)
	{
		cin >> n;
		if ( n != -1 )
			cout << num[n] << endl;
		else
			break;
	}
}