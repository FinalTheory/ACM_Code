#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cctype>
#define MAX(x, y) (x) > (y) ? (x) : (y)
#define MIN(x, y) (x) < (y) ? (x) : (y)
using namespace std;
const char commands[4][15] = {"writeln(a^);", "writeln(b^);", "writeln(c^);", "writeln(d^);"};
const char oper[4] = "^:=";
int main()
{
	int a, b, c, d;
	int * var[4] = {&a, &b, &c, &d}, N, i;
	char command[20], printed, var1, var2;
	cin >> N;
	a = b = c = d = 0;
	while ( N-- )
	{
		cin >> command;
		printed = 0;
		for ( i = 0; i < 4; i++ )
			if ( !strcmp(command, commands[i]) )
			{
				cout << *(var[i]) << endl;
				printed = 1;
				break;
			}
		if ( printed )
			continue;
		var1 = var2 = 0;
		for ( i = 0; i < strlen(command); i++)
		{
			if ( isalpha(command[i]) && !var1 )
			{
				var1 = command[i];
				continue;
			}
			if ( isalnum(command[i]) && !var2 )
			{
				var2 = command[i];
				break;
			}
		}
		if ( strstr(command, oper) )
		{
			if ( '0' <= var2 && var2 <= '9' )
				*(var[var1-97]) = var2 - 48;
			else
				*(var[var1-97]) = *(var[var2-97]);
		}
		else
			var[var1-97] = var[var2-97];
	}
}