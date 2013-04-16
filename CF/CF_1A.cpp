#include <stdio.h>

int main()
{
	unsigned long long n, m, a, x, y;

	while ( scanf("%llu %llu %llu" ,&n, &m, &a) != EOF )
	{
		if ( n > a )
		{
			x = n / a;
			if ( n % a )
				x++;
		}
		else
			x = 1;
		if ( m > a )
		{
			y = m / a;
			if ( m % a )
				y++;
		}
		else 
			y = 1;
		printf("%llu\n", x * y);
	}
	return 0;
}
