/**
 * @file HDU_4594.cpp
 * @brief   超级恶心的模拟题
 * @hint    注意两个地方，一个是虽然保证字符串中不存在双引号，但是可能存在空格！
 *	    第二个就是命令的名称也可能作为常量出现，所以要先检查每一行是否为赋值语句。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-17
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
map<string, string> Variable, Constant;
char buffer[300];
bool Errmsg;
void out_str( string & str )
{
	for ( int i = 0; i < str.size(); ++i )
		if ( str[i] != '\"' )
			putchar(str[i]);
}
bool assign_str( int len )
{
	for ( int i = 0; i < len; ++i )
		if ( buffer[i] == '\"' )
			return true;
	return false;
}
void VarAssign( int len )
{
	map<string, string> :: iterator iter;
	bool is_const = true, Assign_STR = assign_str(len);
	char _name[300], _value[300];
	string var_name, var_value;
	for ( int i = 0; i < len; ++i ) if ( buffer[i] == '=' )
	{
		buffer[i] = ' ';
		break;
	}
	if ( !Assign_STR ) {
		sscanf(buffer, "%s %s", _name, _value);
		var_name = _name; var_value = _value;
	} else {
		sscanf(buffer, "%s", _name);
		var_name = _name;
		int i, j;
		for ( i = 0; i < len; ++i )
			if ( buffer[i] == '\"' )
				break;
		for ( j = i + 1; j < len; ++j )
			if ( buffer[j] == '\"' )
				break;
		var_value.assign(buffer + i, buffer + j + 1);
	}
	if ( var_name[0] == '$' ) is_const = false;
	if ( is_const ) {
		iter = Constant.find(var_name);
		if ( iter == Constant.end() ) {
			Constant[var_name] = var_value;
		}
		else {
			if ( Errmsg )
				printf("WARNING: Constant %s Already Defined!\n", var_name.c_str());
		}
	} else {
		Variable[var_name] = var_value;
	}
}
void PrintVar( bool is_dump )
{
	char skip[300], _name[300];
	string var_name;
	map<string, string> :: iterator iter;
	bool is_const = true;
	sscanf(buffer, "%s %s", skip, _name);
	if ( _name[0] == '$' ) is_const = false;
	var_name = _name;
	if ( is_const ) {
		iter = Constant.find(var_name);
		if ( iter == Constant.end() ) {
			if ( is_dump )
				printf("string: \"%s\"\n", var_name.c_str());
			else {
				printf("%s\n", var_name.c_str());
			}
			if ( Errmsg )
				printf("NOTICE: Undefined Constant %s.\n", var_name.c_str());
		} else {
			if ( is_dump ) {
				string tmp = Constant[var_name];
				if ( tmp.find('\"') != tmp.npos )
					printf("string: ");
				else
					printf("integer: ");
				printf("%s\n", tmp.c_str());
			} else {
				out_str(Constant[var_name]);
				puts("");
			}
		}
	} else {
		iter = Variable.find(var_name);
		if ( iter == Variable.end() ) {
			puts("NULL");
			if ( Errmsg )
				printf("NOTICE: Undefined Variable %s.\n", var_name.c_str());
		} else {
			if ( is_dump ) {
				string tmp = Variable[var_name];
				if ( tmp.find('\"') != tmp.npos )
					printf("string: ");
				else
					printf("integer: ");
				printf("%s\n", tmp.c_str());
			} else {
				out_str(Variable[var_name]);
				puts("");
			}
		}
	}
}
bool is_Assign( int len )
{
	bool _meet_quote = false;
	for ( int i = 0; i < len; ++i )
	{
		if ( buffer[i] == '\"' ) _meet_quote = true;
		if ( !_meet_quote && buffer[i] == '=' )
			return true;
	}
	return false;
}
int main()
{
	//std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int T, N;
	bool panic;
	char str1[20], str2[20], str[260];
	scanf("%d", &T);
	while ( T-- )
	{
		Variable.clear(); Constant.clear();
		panic = false;
		Errmsg = true;
		scanf("%d", &N);
		for ( int k = 0; k < N; ++k )
		{
			do 
			{
				gets(buffer);
			} while (buffer[0] == 0);
			int len = strlen(buffer);
			if ( panic ) continue;
			sscanf(buffer, "%s", str);
			if ( is_Assign( len ) ) {
				VarAssign(len);
			} else if ( !strcmp(str, "Errmsg") ) {
				sscanf(buffer, "%s %s", str1, str2);
				if ( str2[1] == 'N' )
					Errmsg = true;
				else
					Errmsg = false;
			} else if ( !strcmp(str, "Panic") ) {
				 panic = true;
				 puts("Script was KILLED.");
			} else if ( !strcmp(str, "Print") ) {
				PrintVar(false);
			} else if ( !strcmp(str, "Dump") ) {
				PrintVar(true);
			}
		}
		if ( T ) puts("");
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
