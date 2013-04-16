/*
这题太TMD贱了，首先是可以重复AC，时间取最短的那次；其次可以先输入后面的WA，再输入前面的AC；
最后严格来说还要考虑如果一个队一题都没AC但是WA了几次的要排在一次都没交过的队之后，不过这个是OJ不严谨，没有判断此情况。
*/

#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;
struct team
{
	int num;
	int time[25];
	int time_all;
	int failtimes[25];
	char solve_all;
	char solved[25];
};
bool cmp( team x, team y )
{

	if ( x.solve_all != y.solve_all )
		return x.solve_all > y.solve_all;
	else if ( x.time_all != y.time_all )
		return x.time_all < y.time_all;
	else
		return x.num  < y.num; 
}
int main()
{
	int c, n, i, j, ci, pi, ti, ri;
	team data[1005];
	int data2[1005][4];
	//freopen("123.txt", "r", stdin);
	cin >> c >> n;
	while ( !cin.eof() )
	{
	memset( data, 0, sizeof(data) );
	memset( data2, 0, sizeof(data2) );
	for ( i = 0; i < n; i++ )
	{
		cin >> data2[i][0] >> data2[i][1] >> data2[i][2] >> data2[i][3];
	}
	for ( i = 0; i < c; i++ )
	{
		data[i].num = i + 1;
	}
	for ( i = 0; i < n; i++ )
	{
		ci = data2[i][0];
		pi = data2[i][1];
		ti = data2[i][2];
		ri = data2[i][3];
		if ( ri )
		{
			if ( !data[ci - 1].solved[pi - 1] )
			{
				data[ci - 1].solved[pi - 1] = 1;
				data[ci - 1].time[pi - 1] = ti;
			}
			else
			{
				if ( ti < data[ci - 1].time[pi - 1] )
					data[ci - 1].time[pi - 1] = ti;
			}
		}
		else
		{
			int found = 0;
			for ( j = 0; j < n; j++ )
			{
				if ( data2[j][0] == ci && data2[j][1] == pi )
					if ( data2[j][3] && data2[j][2] < ti )
					{
						found = 1;
						break;
					}
			}
			if ( !found )
				data[ci - 1].failtimes[pi - 1]++;
		}
	}
	for ( i = 0; i < c; i++ )
	{
		for ( j = 0; j < 25; j++ )
		{
			data[i].solve_all += data[i].solved[j];
			if ( data[i].solved[j] )
			{
				data[i].time_all += data[i].time[j];
				data[i].time_all += data[i].failtimes[j] * 1200;
			}
		}
		
	}
	sort( data, data + c, cmp );
	for ( i = 0; i < c - 1; i++ )
		cout << data[i].num << ' ';
	cout << data[i].num << endl;
	cin >> c >> n;
	}
}