/**
 * @file POJ_1876.cpp
 * @brief   模拟水题，没什么可说的，读懂题意就可以。
 * 要求是发牌并排序，发牌按照顺时针发，数据开头就指定了发牌者。
 * 排序的话首先按照花色排序，然后花色相同的话再按照牌面大小排序。
 * 一开始没注意怎么设置发牌者，结果连着RE两发，后来才发现自增之后没有求模，肯定RE啊……
 * 最后注意控制一下输出格式，而且每个case后面有一个空行的，居然还因为这个PE了一发，伤不起……
 * @author FinalTheory
 * @version 0.1
 * @date 2013-07-15
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
#include <vector>
#include <set>
#include <stack>
#include <sstream>
#include <iomanip>

#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

struct TMD
{
	char color;
	char number;
} cards[1000];
int map_color[256];
int map_number[256];
bool fuck( const TMD & A, const TMD & B )
{
	if ( A.color != B.color )
		return map_color[A.color] < map_color[B.color];
	else
		return map_number[A.number] < map_number[B.number];
}

char * names[4] = {"North player:", "East player:", "South player:", "West player:"};
char buffer[20000], buffer2[20000];
void Out( const vector <TMD> & ans )
{
	for ( int i = 0; i < ans.size(); ++i )
		cout << "+---";
	cout << "+" << endl;
	for ( int i = 0; i < ans.size(); ++i )
		cout << '|' << ans[i].number << ' ' << ans[i].number;
	cout << "|" << endl;
	for ( int i = 0; i < ans.size(); ++i )
		cout << "| " << ans[i].color << ' ';
	cout << "|" << endl;
	for ( int i = 0; i < ans.size(); ++i )
		cout << '|' << ans[i].number << ' ' << ans[i].number;
	cout << "|" << endl;
	for ( int i = 0; i < ans.size(); ++i )
		cout << "+---";
	cout << "+" << endl;
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
	char start;
	int pos;
	int p;
	vector<TMD> people[4];
	map_color['H'] = 4;
	map_color['S'] = 3;
	map_color['D'] = 2;
	map_color['C'] = 1;
	for ( int i = '2'; i <= '9'; ++i )
		map_number[i] = i - '1';
	map_number['A'] = 13;
	map_number['K'] = 12;
	map_number['Q'] = 11;
	map_number['J'] = 10;
	map_number['T'] = 9;
	while ( cin >> start && start != '#' )
	{
		for ( int i = 0; i < 4; ++i )
			people[i].clear();
		switch ( start )
		{
		case 'N':
			pos = 1;
			break;
		case 'E':
			pos = 2;
			break;
		case 'S':
			pos = 3;
			break;
		case 'W':
			pos = 0;
			break;
		}
		p = 0;
		cin >> buffer;
		cin >> buffer2;
		strcat( buffer, buffer2 );
		for ( int i = 0; i < strlen(buffer); i += 2 )
		{
			cards[p].color = buffer[i];
			cards[p++].number = buffer[i + 1];
		}
		for ( int i = 0; i < p; ++i )
		{
			people[pos].push_back(cards[i]);
			pos++;
			if ( pos == 4 )
				pos = 0;
		}
		for ( int i = 0; i < 4; ++i )
			sort( people[i].begin(), people[i].end(), fuck );
		int tmp = 2;
		for ( int tmp = 0; tmp < 4; ++tmp )
		{
			int i = (tmp + 2) % 4;
			cout << names[i] << endl;
			Out( people[i] );
		}
		cout << endl;
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
