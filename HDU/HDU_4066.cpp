/*
	找规律，尼玛真心找不到啊！！！
	方向一开始错了，不然应该还是能猜出来的！
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
double ans[1540];
int main()
{
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	double x=1.0;
	ans[1]=1.0;
	for (int i=2;i<=1500;i++)
	{
		if (i%2==0)
			x=x*(i-1.0)/(i*1.0);
		ans[i]=ans[i-1]+x;
	}
	int t;
	int cas=0;
	scanf("%d",&t);
	while (t--)
	{
		int n;
		scanf("%d",&n);
		printf("Case %d: %.6lf\n",++cas,ans[n]);
	}
#ifndef ONLINE_JUDGE
	program_end = clock();
	cout << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}