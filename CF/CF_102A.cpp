/*
	数据规模小，直接枚举就可以了。
	两处SB的笔误，死的心都有了！
	尼玛一开始居然是按照最贵的买的！
	而且这样居然都到了test11才错……
*/
#include <iostream>
#include <algorithm>
using namespace std;
struct Node
{
	int index, price;
} clothes[105];
bool cmp( Node A, Node B )
{
	return A.price < B.price;
}
char map[105][105];
void link( int i, int j )
{
	map[i-1][j-1] = 1;
	map[j-1][i-1] = 1;
}
bool match( int i, int j )
{
	return map[i][j];
}
int main()
{
	//freopen("in.txt", "r", stdin);
	int n, m, i, j, k, x, y, found, sum;
	cin >> n >> m;
	for ( i = 0; i < n; i++ )
	{
		cin >> clothes[i].price;
		clothes[i].index = i;
	}
	sort(clothes, clothes + n, cmp);
	for ( i = 0; i < m; i++ )
	{
		cin >> x >> y;
		link(x, y);
	}
	sum = found = 0;
	for ( i = 0; i < n - 2 && !found; i++ )
		for ( j = i + 1; j < n - 1 && !found; j++ )
			for ( k = j + 1; k < n && !found; k++ )
				if ( match(clothes[i].index, clothes[j].index) && match(clothes[j].index, clothes[k].index) && match(clothes[k].index, clothes[i].index) )
				{
					found = 1;
					sum += clothes[i].price + clothes[j].price + clothes[k].price;
				}
	if ( found )
		cout << sum << endl;
	else
		cout << "-1"  << endl;
}