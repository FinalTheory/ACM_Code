#include <stdio.h>
#include <string.h>
int a, b, m, n, error;
struct {
	int x[4];
	int y[4];
} go = { { 0, 0, 1, -1 }, { 1, -1, 0, 0 } };

struct {
	int x;
	int y;
	char direct;
} robot[100];

struct {
	int rob;
	char act;
	int repeat;
} steps;

int check( int i, int x, int y )
{
	int j;
	for ( j = 0; j < n; j++ )
	{
		if ( j != i )
		{
			if ( robot[j].x == x && robot[j].y == y )
			{
				printf( "Robot %d crashes into robot %d\n", i + 1, j + 1 );
				return 1;
			}
		}
	}
	if ( x > a || x < 1 || y > b || y < 1 )
	{
		printf( "Robot %d crashes into the wall\n", i + 1 );
		return 1;
	}
	return 0;
}

void move()
{
	int k, p;
			switch ( steps.act )
			{
				case 'F' : 
					switch ( robot[steps.rob-1].direct )
					{
						case 'N' : p = 0;break;
						case 'S' : p = 1;break;
						case 'E' : p = 2;break;
						case 'W' : p = 3;
 					}
					for ( k = 0; k < steps.repeat; k++ )
					{
						robot[steps.rob-1].x += go.x[p];
						robot[steps.rob-1].y += go.y[p];
						if ( check( steps.rob - 1, robot[steps.rob-1].x, robot[steps.rob-1].y ) ) 
							{
								error = 1;
								return;
							}
					}
					break;
				case 'L':
					for ( k = 0; k < steps.repeat % 4; k++ )
					switch ( robot[steps.rob-1].direct )
					{
						case 'N' : robot[steps.rob-1].direct = 'W';
							break;
						case 'S' : robot[steps.rob-1].direct = 'E';
							break;
						case 'E' : robot[steps.rob-1].direct = 'N';
							break;
						case 'W' : robot[steps.rob-1].direct = 'S';
					}
					break;
				case 'R':
					for ( k = 0; k < steps.repeat % 4; k++ )
					switch ( robot[steps.rob-1].direct )
					{
					case 'N' : robot[steps.rob-1].direct = 'E';
						break;
					case 'S' : robot[steps.rob-1].direct = 'W';
						break;
					case 'E' : robot[steps.rob-1].direct = 'S';
						break;
					case 'W' : robot[steps.rob-1].direct = 'N';
					}
					break;
			}
}


void main()
{

	int k, i;
	//freopen( "123.txt", "r", stdin );
	scanf("%d",&k);
	while ( k-- )
	{
		error = 0;
		scanf( "%d %d", &a, &b );
		scanf( "%d %d", &n, &m );
		for ( i = 0; i < n; i++ )
			scanf( "%d %d %c", &robot[i].x, &robot[i].y, &robot[i].direct );
		for ( i = 0; i < m; i++ )
		{
			scanf( "%d %c %d", &steps.rob, &steps.act, &steps.repeat );
			if ( !error )
				move();
		}
		if ( !error ) printf( "OK\n" );
	}
}
