/**
 * @file Changsha Regional E.cpp
 * @brief   坑题，注意所有进行比较的地方精度控制eps的设置。
 * @feeling 1A的感觉还是很爽滴~
 * @author FinalTheory
 * @version 0.1
 * @date 2013-09-29
 */
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
#define eps 0.000001

string week[8] = {"", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

double _left[9] = { 0, 48, 40, 32, 24, 16, 8, 4, 0 };
double _remain[8] = { 0, 8, 16, 24, 32, 40, 44, 48 };

int main()
{
	//std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	string date;
	int L;
	double s, time;
	int start_day, i;
	while ( cin >> date >> L >> s )
	{
		for ( start_day = 1; start_day <= 7; ++start_day )
			if ( date == week[start_day] )
				break;
		time = (double)L / s;
		if ( time > _left[start_day] )
			time -= _left[start_day];
		else
		{
			for ( i = start_day + 1; i <= 8; ++i )
				if ( _left[start_day] - _left[i] + eps > time )
					break;
			cout << week[i - 1] << endl;
			continue;
		}
		int t = int( time / 48. );
		time -= t * 48.;
		if ( time < eps )
		{
			cout << week[7] << endl;
			continue;
		}
		for ( i = 1; i <= 7; ++i )
			if ( time < _remain[i] + eps )
				break;
		cout << week[i] << endl;
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
