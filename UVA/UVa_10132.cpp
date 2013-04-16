/*
	字符串问题，key是相同长度的碎片最多只有两种，分开尝试一下他们的组合就行了。
	不过这代码写的真心有够垃圾的！
	另外，尼玛UVa没有PE吗？！少输出了个换行就直接给我WA了！害我仔细检查了半天……
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
#define MAX(x, y) (x) > (y) ? (x) : (y)
#define MIN(x, y) (x) < (y) ? (x) : (y)
using namespace std;
struct TMD
{
	char str[2100];
	int len;
} files[300];
char str1[5000], str2[5000];
bool fuck( TMD * A, TMD * B )
{
	if ( (*A).len != (*B).len )
		return (*A).len < (*B).len;
	else
		return (strcmp( (*A).str, (*B).str ) < 0) ? 1 : 0;
}
bool check( TMD * head1, TMD * head2, TMD * tail1, TMD * tail2 )
{
	strcpy( str1, head1->str );
	strcat( str1, tail1->str );
	strcpy( str2, head2->str );
	strcat( str2, tail2->str );
	if ( !strcmp( str1, str2 ) )
	{
		cout << str1 << endl;
		return 1;
	}
	strcpy( str1, head1->str );
	strcat( str1, tail1->str );  
	strcpy( str2, tail2->str );
	strcat( str2, head2->str );
	if ( !strcmp( str1, str2 ) )
	{
		cout << str1 << endl;
		return 1;
	}
	strcpy( str1, tail1->str );
	strcat( str1, head1->str );
	strcpy( str2, head2->str );
	strcat( str2, tail2->str );
	if ( !strcmp( str1, str2 ) )
	{
		cout << str1 << endl;
		return 1;
	}
	strcpy( str1, tail1->str );
	strcat( str1, head1->str );
	strcpy( str2, tail2->str );
	strcat( str2, head2->str );
	if ( !strcmp( str1, str2 ) )
	{
		cout << str1 << endl;
		return 1;
	}
	return 0;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int max_len, min_len, i, j, T, len, N, len_all;
	char str[2100], found;
	TMD * pointers[300], *head1, *head2, *tail1, *tail2;
	scanf("%d", &T);
	getchar();
	gets(str);
	while ( T-- )
	{
		i = 0;
		max_len = INT_MIN;
		min_len = INT_MAX;
		while ( gets(str) != NULL && ( len = strlen(str) ) != 0 )
		{
			strcpy(files[i].str, str);
			files[i++].len = len;
			if ( len < min_len )
				min_len = len;
			if ( len > max_len )
				max_len = len;
		}
		N = i; len_all = min_len + max_len;
		if ( N == 2 )
		{
			cout << files[0].str << files[1].str << endl;
			continue;
		}
		for ( i = 0; i < N; i++ )
			pointers[i] = files + i;
		sort( pointers, pointers + N, fuck );
		i = found = 0;
		for ( j = i + 1; j < N / 2; j++ )
		{
			if ( pointers[i]->len != pointers[j]->len )
			{
				i = j;
				continue;
			}
			if ( strcmp(pointers[i]->str, pointers[j]->str) )
			{
				found = 1;
				head1 = pointers[i];
				head2 = pointers[j];
				min_len = pointers[i]->len;
				break;
			}
		}
		if ( !found )
		{
			head1 = pointers[0];
			head2 = pointers[1];
			tail1 = pointers[N - 1];
			tail2 = pointers[N - 2];
			check( head1, head2, tail1, tail2 );
		}
		else
		{
			tail1 = tail2 = NULL;
			for ( i = N - 1; i >= N / 2; i-- )
				if ( pointers[i]->len == len_all - min_len )
				{
					if ( tail1 == NULL && tail2 == NULL )
					{
						tail1 = pointers[i];
						continue;
					}
					if ( tail1 != NULL && tail2 == NULL )
						if ( strcmp( (*tail1).str, pointers[i]->str ) )
						{
							tail2 = pointers[i];
							break;
						}
				}
			if ( !check( head1, head2, tail1, tail2 ) )
				check( head2, head1, tail1, tail2 );
		}
		if ( T != 0 )
			cout << endl;
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cout << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}