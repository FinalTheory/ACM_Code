/*
	ò���ٶȾ��ҵĴ���������30MS���ð����ˡ�
	������������ģ�⣬��Ҫ��Ҫ�ҵ�һ�����ʵ��ַ���������ԡ�
	�����ַ���˳������ģ����Ը�������Ҫ���棬ֱ�ӱ߶���ߴ�������ˡ�
	һ��ʼ˼·������N��Σ���������ҵ��������õķ�ʽ��һ��AC��
	���ķ�ʽ��Ȼ���Դ����Ż���������
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