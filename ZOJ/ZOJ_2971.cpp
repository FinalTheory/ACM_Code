/*
	貌似速度就我的代码最慢，30MS，好吧认了。
	这道题可以算是模拟，主要是要找到一个合适的字符串处理策略。
	由于字符是顺序输入的，所以根本不需要保存，直接边读入边处理就行了。
	一开始思路错误了N多次，最后总算找到了这个最好的方式，一次AC。
	打表的方式果然可以大量优化代码量。
*/
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const char num1[20][10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
const char num2[20][10] = {"", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
const char num3[3][10] = {"million", "thousand", "hundred"};
const int num4[2] = {1000000, 1000};
int main()
{
	//freopen("in.txt", "r", stdin);
	char words[20][20], c;
	int T, i, j, num, sum;
	cin >> T;
	while ( T-- )
	{
		i = sum = num = 0;
		do 
		{
			scanf("%s", words[i]);
			for ( j = 0; j < 20; j++ )
				if ( !strcmp(words[i], num1[j]) )
				{
					num += j;
					goto end;
				}
			for ( j = 2; j < 10; j++ )
				if ( !strcmp(words[i], num2[j]) )
				{
					num += j * 10;
					goto end;
				}
			if ( !strcmp(words[i], num3[2]) )
			{
				num *= 100;
				goto end;
			}
			for ( j = 1; j >= 0; j-- )
			if ( !strcmp(words[i], num3[j]) )
			{
				num *= num4[j];
				sum += num;
				num = 0;
				goto end;
			}
end:
			i++;
		} while ( ( c = getchar() ) != '\n' );
		cout << sum + num << endl;
	}
}