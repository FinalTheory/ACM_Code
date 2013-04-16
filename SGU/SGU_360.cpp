#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <climits>
#include <time.h>
#include <cctype>
#define MAX(x, y) (x) > (y) ? (x) : (y)
#define MIN(x, y) (x) < (y) ? (x) : (y)
using namespace std;
struct TMD
{
	char real;
	char dummy;
};
char map[55][55];
char codes[10010];
char commands[1010];
int pointer = 0, len_all;
int robot_x, robot_y;
char robot_toward = 1;
int moves[5][2] = { {0, 0}, {0, -1}, {-1, 0}, {0, 1}, {1, 0} };
int N, M;
int pos[2502][2];
char * make_func( char func_name )
{
	int i, j, k, len;
	//首先找到函数位置
	for ( i = 0; i < len_all; i++ )
		if ( codes[i] == func_name && ( codes[i+3] == '{' || codes[i+4] == '{' || codes[i+6] == '{' ) )
			break;
	++i;
	j = i;//用i的备份统计长度
	len = 1;
	while ( codes[j] != '}' )
		len++, j++;
	char * p = ( char * )calloc(len+2, sizeof(char));
	k = 0;
	while ( codes[i] != '}' )
		p[k++] = codes[i++];
	p[k++] = '}';
	p[k] = 0;
	return p;
}
void function( char arg1, char arg2, char * func )
{
	int len = strlen(func), i = 0;
	char dummy1, dummy2, func_name;
	//首先读取此函数形参。
	dummy1 = dummy2 = 0;
	while( func[i] != ')' )
	{
		if ( isalpha(func[i]) && !dummy1 )
		{
			dummy1 = func[i++];
			continue;
		}
		if ( isalpha(func[i]) && !dummy2 )
			dummy2 = func[i];
		i++;
	}
	//置换形参
	for ( ; i < len; i++ )
	{
		if ( func[i] == dummy1 )
			func[i] = arg1;
		if ( func[i] == dummy2 )
			func[i] = arg2;
	}
	i = 0;
	while ( i < len )
	{
		while ( func[i] == 'L' || func[i] == 'R' || func[i] == 'C' )
			commands[pointer++] = func[i++];
		//如果发现函数调用
		if ( 'a' <= func[i] && func[i] <= 'z' )
		{
			func_name = func[i++];
			arg1 = arg2 = 0;
			while( func[i] != ')' )
			{
				if ( isalpha(func[i]) && !arg1 )
				{
					arg1 = func[i++];
					continue;
				}
				if ( isalpha(func[i]) && !arg2 )
					arg2 = func[i];
				i++;
			}
			char * c = make_func(func_name);
			function( arg1, arg2, c );
		}
		i++;
	}
}

bool check( int i, int j )
{
	if ( i < 0 || i >= M || j < 0 || j >= N )
		return 0;
	return 1;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int i, j, c, sum = 0, k = 0;
	cin >> N >> M;
	for ( i = 0; i < N; i++ )
		scanf("%s", map[i]);
	//找到ROBOT的初始化位置。
	for ( i = 0; i < N; i++ )
		for ( j = 0; j < M; j++ )
			if ( map[i][j] == 'R' )
				robot_x = j, robot_y = i;
	i = 0;
	//读入命令并去除白字符。
	while ( ( c = getchar() ) != EOF )
	{
		if ( c == '\n' || c == ' ' || c == '\t' )
			continue;
		codes[i++] = c;
	}
	len_all = i;
	i = codes[len_all] = 0;
	//开始展开所有函数。首先定位到m()。
	char * m = make_func('m');
	function( 0, 0, m );
	for ( i = 0; i < pointer; i++ )
	{
		switch( commands[i] )
		{
			case 'L' :
				robot_toward++;
				if ( robot_toward > 4 )
					robot_toward -= 4;
				break;
			case 'R' :
				robot_toward--;
				if ( !robot_toward )
					robot_toward += 4;
				break;
			case 'C' :
				if ( check( robot_x + moves[robot_toward][0], robot_y + moves[robot_toward][1] ) )
					robot_x += moves[robot_toward][0], robot_y += moves[robot_toward][1];
				if ( map[robot_y][robot_x] == '*' )
				{
					map[robot_y][robot_x] = '~';
					sum++;
					pos[k][0] = robot_y + 1;
					pos[k++][1] = robot_x + 1;
				}
		}
	}
	cout << sum << endl;
	for ( i = 0; i < sum; i++ )
		cout << pos[i][0] << ' ' << pos[i][1] << endl;
#ifndef ONLINE_JUDGE
	program_end = clock();
	cout << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}