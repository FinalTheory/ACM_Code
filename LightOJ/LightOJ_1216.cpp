/*
	尼玛这题太坑爹了，控制好精度，Pi至少要到十几位！
*/
#include <stdio.h>
#include <math.h>
int main()
{
	int T, i;
	double r1, r2, h, p, r3, V;
	scanf("%d", &T);
	for ( i = 1; i <= T; i++ )
	{
		scanf("%lf %lf %lf %lf", &r1, &r2, &h, &p);
		r3 = ( p / h ) * ( r1 - r2 ) + r2;
		V = acos((double)-1) * p * ( r2 * r2 + r2 * r3 + r3 * r3 ) / 3.;
		printf("Case %d: %.9lf\n", i, V);
	}
}
