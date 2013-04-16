/*
	最简单的贪心，尼玛一个笔误WA了两次，Fuck！
	按照节目长度排序，然后优先看时间短的就可以了。
*/
#include <iostream>
#include <algorithm>
using namespace std;
struct TMD
{
	int start, end, len;
} T[102];
char flags[50];
bool fuck( TMD A, TMD B )
{
	return A.len < B.len;
}
int main()
{
	//freopen("in.txt", "r", stdin);
	int n, i, j, sum, no;
	while ( cin >> n && n )
	{
		memset(flags, 0, sizeof(flags));
		sum = 0;
		for ( i = 0; i < n; i++ )
		{
			cin >> T[i].start >> T[i].end;
			T[i].len = T[i].end - T[i].start;
		}
		sort(T, T + n, fuck);
		for ( i = 0; i < n; i++ )
		{
			no = 0;
			for ( j = T[i].start; j < T[i].end; j++ )
				if ( flags[j] )
				{
					no = 1;
					break;
				}
			if ( !no )
			{
				for ( j = T[i].start; j < T[i].end; j++ )
					flags[j] = 1;
				sum ++;
			}
		}
		cout << sum << endl;
	}
}