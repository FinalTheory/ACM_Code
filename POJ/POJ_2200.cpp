/*
	模拟题。一开始没有想到特别好的策略，考虑到数据规模不大，所以直接暴搜。
	首先穷举所有可能排列，这样的话主要就只需要写一个检测是否符合条件的判断函数就可以了。
	网上查到了next_permutation()这个函数，用于输出全排列的下一个状态。当然也有prev_permutation()。
	此函数包含在algorithm里面，由于是模板所以可以接受各种数据类型，不得不说这个库有好多好东西。
	此函数跟sort()一样，可以自定义比较函数。没有的话必要不要用容器，貌似降低效率。
	如果要输出全排列的话，首先数据本身必须是有序的，因为这个函数输出的是第一个不按升序排列的序列。
	虽然A了这道题，但是用法还是不大懂，升序/降序排列根据的是自定义的函数，next_permutation()同样。
	所以似乎只要保证这两个比较函数一样就可以了，具体的回去看sort()说明吧。
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
struct TMD
{
	char value;
	char suit;
} cards[5];
bool fuck( TMD A, TMD B )
{
	if ( A.value != B.value )
		return A.value < B.value;
	else
		return A.suit < B.suit;
}
bool check()
{
	int sum = cards[1].value, i, j, pos;
	TMD min = {100, 'Z'}, max[2];
	if ( cards[0].suit != cards[1].suit )
		return 0;
	for ( i = 2; i < 5; i++ )
		if ( fuck( cards[i], min ) )
		{
			pos = i - 1;
			min = cards[i];
		}
	for ( i = 2, j = 0; i < 5; i++ )
	{
		if ( i == pos + 1 ) continue;
		max[j++] = cards[i];
	}
	sum += pos;
	if ( !fuck(max[0], max[1]) )
		sum += 3;
	if ( sum > 13 )
		sum %= 13;
	if ( sum == cards[0].value )
		return 1;
	else
		return 0;
}
int main()
{
	//freopen("in.txt", "r", stdin);
	char str[5];
	int n, i, j;
	cin >> n;
	for ( j = 1; j <= n; j++ )
	{
		for ( i = 0; i < 5; i++ )
		{
			scanf("%s", str);
			if ( 3 == strlen(str) )
			{
				cards[i].value = 10;
				cards[i].suit = str[2];
			}
			else
			{
				switch (str[0])
				{
					case 'A' :
						cards[i].value = 1;
						break;
					case 'J' :
						cards[i].value = 11;
						break;
					case 'Q' :
						cards[i].value = 12;
						break;
					case 'K' :
						cards[i].value = 13;
						break;
					default:
						cards[i].value = str[0] - 48;
				}
				cards[i].suit = str[1];
			}
		}
		sort(cards, cards + 5, fuck);
		while ( next_permutation(cards, cards + 5, fuck) )
		{
			if ( check() )
				break;
		}
		printf("Problem %d: ", j);
		for ( i = 0; i < 5; i++ )
		{
			switch ( cards[i].value )
			{
				case 1 :
					printf("A");
					break;
				case 11 :
					printf("J");
					break;
				case 12 :
					printf("Q");
					break;
				case 13 :
					printf("K");
					break;
				default :
					printf("%d", cards[i].value);
			}
			printf("%c ", cards[i].suit);
		}
		printf("\n");
	}
}