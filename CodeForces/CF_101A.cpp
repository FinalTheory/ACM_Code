/*
	�����ϻ���̰�ģ�����������ĸ��������
	Ȼ�����ĸ�ٵ�����ĸ���ɾ�������Ժܼ򵥡�
	��������ʱ��ûע�⣬˵�����������������ɣ�����������������
	���ע���TMD��SBһ������freopen���ύ�ˣ�����
*/
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
struct TMD
{
	char c;
	int num;
} flags[26];
bool cmp( TMD A, TMD B )
{
	return A.num < B.num;
}
bool cmp2( TMD A, TMD B )
{
	return A.c < B.c;
}
int main()
{
	//freopen("in.txt", "r", stdin);
	int n, k, i, m;
	char str[100001];
	scanf("%s", str);
	scanf("%d", &k);
	m = 0;
	n = strlen(str);
	if ( k >= n )
	{
		printf("0\n");
		exit(0);
	}
	for ( i = 0; i < 26; i++ )
	{
		flags[i].c = i;
		flags[i].num = 0;
	}
	for ( i = 0; i < n; i++ )
		flags[str[i]-97].num++;
	sort(flags, flags + 26, cmp);
	for ( i = 0; i < 26; i++ )
	{
		if ( !flags[i].num ) continue;
		if ( k >= flags[i].num )
		{
			k -= flags[i].num;
			flags[i].num = 0;
		}
		else
		{
			k = 0;
		}
		if ( !k ) break;
	}
	sort(flags, flags + 26, cmp2);
	for ( i = 0; i < 26; i++ )
		if ( flags[i].num )
			m++;
	printf("%d\n", m);
	for ( i = 0; i < n; i++ )
		if ( flags[str[i]-97].num )
		{
			printf("%c", str[i]);
			flags[str[i]-97].num--;
		}
	printf("\n");
}
