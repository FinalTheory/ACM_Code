/*
	ģ���⡣һ��ʼû���뵽�ر�õĲ��ԣ����ǵ����ݹ�ģ��������ֱ�ӱ��ѡ�
	����������п������У������Ļ���Ҫ��ֻ��Ҫдһ������Ƿ�����������жϺ����Ϳ����ˡ�
	���ϲ鵽��next_permutation()����������������ȫ���е���һ��״̬����ȻҲ��prev_permutation()��
	�˺���������algorithm���棬������ģ�����Կ��Խ��ܸ����������ͣ����ò�˵������кö�ö�����
	�˺�����sort()һ���������Զ���ȽϺ�����û�еĻ���Ҫ��Ҫ��������ò�ƽ���Ч�ʡ�
	���Ҫ���ȫ���еĻ����������ݱ������������ģ���Ϊ�������������ǵ�һ�������������е����С�
	��ȻA������⣬�����÷����ǲ��󶮣�����/�������и��ݵ����Զ���ĺ�����next_permutation()ͬ����
	�����ƺ�ֻҪ��֤�������ȽϺ���һ���Ϳ����ˣ�����Ļ�ȥ��sort()˵���ɡ�
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