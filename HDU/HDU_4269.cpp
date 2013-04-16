/*
	水模拟一道，读错题意坑死爹了！
	注意几点：
	1 背包满了之后即便是consume物品也不能买；
	2 如果背包满了，依然可以合成mixture物品；
	3 但是某些mixture物品不需要消耗，因此当背包满了的时候不能再买；
	4 合成mixture物品时只需扣除合成的费用，但是卖出mixture物品时要注意获得其完全的价值；
	5 合成mixture物品时注意扣除掉消耗的Normal物品和mixture物品，如果两者中有不够的话就失败。
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
#include <sstream>
#define MAX 25
#define NAME 25
#define LEN 2000
using namespace std;
int N1, N2, N3, grids;
struct
{
	char name[NAME];
	int price, num;
} consume[MAX], normal[MAX];
struct
{
	char name[NAME], buffer[LEN], flag;
	int price, price_all, num, flags_normal[MAX], flags_mixture[MAX];
} mixture[MAX];
struct TMD
{
	char * ptr, flag;
	int num;
} pointers[100];
bool fuck( TMD A, TMD B )
{
	if ( strcmp( A.ptr, B.ptr ) < 0 )
		return 1;
	else
		return 0;
}
int find1( char * ptr )
{
	int i;
	for ( i = 0; i < N1; i++ )
		if ( !strcmp(ptr, normal[i].name) )
			return i;
	return -1;
}
int find2( char * ptr )
{
	int i;
	for ( i = 0; i < N2; i++ )
		if ( !strcmp(ptr, mixture[i].name) )
			return i;
	return -1;
}
int find3( char * ptr )
{
	int i;
	for ( i = 0; i < N3; i++ )
		if ( !strcmp(ptr, consume[i].name) )
			return i;
	return -1;
}
bool check_cost( int index )
{
	for ( int i = 0; i < MAX; i++ )
		if ( mixture[index].flags_normal[i] || mixture[index].flags_mixture[i] )
			return 1;
	return 0;
}
int make_price( int index )
{
	int i;
	if ( !mixture[index].flag )
	{
		mixture[index].flag = 1;
		for ( i = 0; i < N1; i++ )
			if ( mixture[index].flags_normal[i] )
				mixture[index].price_all += normal[i].price * mixture[index].flags_normal[i];
		for ( i = 0; i < N2; i++ )
			if ( mixture[index].flags_mixture[i] )
				mixture[index].price_all += make_price( i ) * mixture[index].flags_mixture[i];
	}
	return mixture[index].price_all;
}
bool check( int index )
{
	int i;
	for ( i = 0; i < N1; i++ )
		if ( mixture[index].flags_normal[i] > normal[i].num )
			return 0;
	for ( i = 0; i < N2; i++ )
		if ( mixture[index].flags_mixture[i] > mixture[i].num )
			return 0;
	for ( i = 0; i < N1; i++ )
		if ( mixture[index].flags_normal[i] )
		{
			normal[i].num -= mixture[index].flags_normal[i];
			grids -= mixture[index].flags_normal[i];
		}
	for ( i = 0; i < N2; i++ )
		if ( mixture[index].flags_mixture[i] )
		{
			mixture[i].num -= mixture[index].flags_mixture[i];
			grids -= mixture[index].flags_mixture[i];
		}
	return 1;
}
int main()
{
	//freopen( "in.txt", "r", stdin );
	int i, j, k, M, money, num, index = 1;
	char str[NAME], ch, command[NAME];
	istringstream ss;
	while ( cin >> N1 )
	{
		grids = money = 0;
		memset( normal, 0, sizeof(normal) );
		memset( mixture, 0, sizeof(mixture) );
		memset( consume, 0, sizeof(consume) );
		memset( pointers, 0, sizeof(pointers) );
		for ( i = 0; i < N1; i++ )
			cin >> normal[i].name >> normal[i].price;
		cin >> N2;
		for ( i = 0; i < N2; i++ )
		{
			cin >> mixture[i].name >> mixture[i].price;
			mixture[i].price_all = mixture[i].price;
			ch = getchar();
			gets( mixture[i].buffer );
		}
		cin >> N3;
		for ( i = 0; i < N3; i++ )
			cin >> consume[i].name >> consume[i].price;
		for ( i = 0; i < N2; i++ )
		{
			ss.str( mixture[i].buffer );
			ss.clear();
			while ( ss >> str >> num )
			{
				char found = 0;
				if ( ( j = find1( str ) ) != -1 )
				{
					mixture[i].flags_normal[j] = num;
					found = 1;
				}
				if ( !found )
					if ( ( j = find2( str ) ) != -1 )
						mixture[i].flags_mixture[j] = num;
				ch = ss.get();
			}
		}
		for ( i = 0; i < N2; i++ )
			make_price(i);
		cin >> M;
		for ( i = 0; i < M; ++i )
		{
			cin >> command;
			if ( command[0] == '+' )
			{
				if ( command[1] >= '0' && command[1] <= '9' )
				{
					sscanf( command + 1, "%d", &num );
					money += num;
				}
				else
				{
					sscanf( command + 1, "%s", str );
					char found = 0;
					if ( ( j = find1( str ) ) != -1 )
						if ( money >= normal[j].price && grids < 6 )
						{
							++normal[j].num;
							++grids;
							money -= normal[j].price;
							found = 1;
						}
					if ( !found )
						if ( ( j = find2( str ) ) != -1 )
							if ( money >= mixture[j].price && check( j ) )
							{
								if ( grids == 6 && !check_cost(j) )
									goto out;
								++mixture[j].num;
								++grids;
								money -= mixture[j].price;
								found = 1;
							}
					if ( !found )
						if ( ( j = find3( str ) ) != -1 )
							if ( money >= consume[j].price && grids < 6 )
							{
								if ( !consume[j].num )
									++grids;
								++consume[j].num;
								money -= consume[j].price;
							}
				out:;
				}
			}
			else
			{
				char found = 0;
				sscanf( command + 1, "%s", str );
				if ( ( j = find1( str ) ) != -1 )
				{
					if ( normal[j].num )
					{
						--normal[j].num;
						--grids;
						money += normal[j].price;
						found = 1;
					}
				}
				if ( !found )
					if ( ( j = find2( str ) ) != -1 )
					{
						if ( mixture[j].num )
						{
							--mixture[j].num;
							--grids;
							money += mixture[j].price_all;
							found = 1;
						}
					}
				if ( !found )
					if ( ( j = find3( str ) ) != -1 )
					{
						if ( consume[j].num )
						{
							money += consume[j].price * consume[j].num;
							consume[j].num = 0;
							--grids;
							found = 1;
						}
					}
			}
		}
		k = 0;
		for ( i = 0; i < MAX; i++ )
		{
			if ( normal[i].num )
			{
				pointers[k].num = normal[i].num;
				pointers[k++].ptr = normal[i].name;
			}
			if ( mixture[i].num )
			{
				pointers[k].num = mixture[i].num;
				pointers[k++].ptr = mixture[i].name;
			}
			if ( consume[i].num )
			{
				pointers[k].num = consume[i].num;
				pointers[k].flag = 1;
				pointers[k++].ptr = consume[i].name;
			}
		}
		sort( pointers, pointers + k, fuck );
		printf("Case %d:\n%d\n%d\n", index++, money, grids);
		for ( i = 0; i < k; i++ )
			if ( !pointers[i].flag )
				for ( j = 0; j < pointers[i].num; j++ )
					printf("%s: 1\n", pointers[i].ptr);
			else
				printf("%s: %d\n", pointers[i].ptr, pointers[i].num);
		printf("\n");
	}
}