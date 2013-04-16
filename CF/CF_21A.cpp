/*
	尼玛这SB题调了整整五个小时啊！！！
	擦，疯了快！
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int check_host( char * hostname )
{
	int i = 0, len, max_len = 0, min_len = 1000;
	while( i <= strlen(hostname) )
	{
		len = 0;
		while ( hostname[i] != '.' && hostname[i] != 0 )
			len++, i++;
		if ( len > max_len ) max_len = len;
		if ( len < min_len ) min_len = len;
		i++;
	}
	if ( !min_len || max_len > 16 )
		return 1;
	else
		return 0;
}

int check_res( char * resource )
{
	int i = 0, len, max_len = 0, min_len = 1000;
	while( i <= strlen(resource) )
	{
		len = 0;
		while ( resource[i] != '/' && resource[i] != 0 )
			len++, i++;
		if ( len > max_len ) max_len = len;
		if ( len < min_len ) min_len = len;
		i++;
	}
	if ( !min_len || max_len > 16 )
		return 1;
	else
		return 0;
}

int main()
{
	//freopen("123.txt", "r", stdin);
	char str[201], username[201], hostname[201], resource[201];
	int i, j, len;
	char res, at, point, next;
	next = at = res = point = 0;
	scanf("%s",str);
	len = strlen(str);
	for ( i = 0; i < len; i++ )
		if ( str[i] == '@' )
		{
			at = 1;
			break;
		}
		if ( !at )
		{
			printf("NO\n");
			exit(0);
		}
		j = i;
		for ( i = j + 1; i < len; i++ )
		{
			if ( str[i] == '.' )
				point = 1;
			if ( str[i] == '/' )
				res = 1;
		}
		for ( i = 0, j = 0; str[i] != '@'; i++, j++ )
			username[j] = str[i];
		username[i] = 0;
		if ( res )
		{
			for ( ++i, j = 0; str[i] != '/'; i++, j++ )
				hostname[j] = str[i];
			hostname[j] = 0;
			for ( ++i, j = 0; str[i] != 0; i++, j++ )
				resource[j] = str[i];
			resource[j] = 0;
		}
		else 
		{
			for ( ++i, j = 0; str[i] != 0; i++, j++ )
				hostname[j] = str[i];
			hostname[j] = 0;
			resource[0] = 0;
		}
		for ( i = 0; i < strlen(username); i++ )
			if ( !( isalnum(username[i]) || username[i]=='_' ) )
				next = 1;
		for ( i = 0; i < strlen(hostname); i++ )
			if ( !( isalnum(hostname[i]) || hostname[i]=='_' || hostname[i]=='.' ) )
				next = 1;
		for ( i = 0; i < strlen(resource); i++ )
			if ( !( isalnum(resource[i]) || resource[i]=='_' || resource[i]=='/' ) )
				next = 1;
		if ( strlen(username) > 16 || strlen(username) == 0 )
			next = 1;
		if ( strlen(hostname) > 32 || strlen(hostname) == 0 || check_host( hostname ) )
			next = 1;
		if ( res && check_res( resource ) )
			next = 1;
		( next ) ? printf("NO\n") : printf("YES\n");
		return 0;
}