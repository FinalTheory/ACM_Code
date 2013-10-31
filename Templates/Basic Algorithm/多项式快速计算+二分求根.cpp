/**
 * @file OUC_1128.cpp
 * @brief   递推法快速计算多项式，二分求根。
 * 在题目所述的取值范围内，这个函数是单调的，这题太TMD水了！
 * @author FinalTheory
 * @version 0.1
 * @date 2013-04-10
 */
#define eps 0.0000001
int CF[20], T;
double calc( double x )
{
	double ans = CF[T];
	for ( int i = T - 1; i >= 0; --i )
		ans = ans * x + CF[i];
	return ans;
}
double solve( double up, double down )
{
	double mid;
	while ( up - down > eps )
	{
		mid = ( up + down ) / 2;
		if ( calc(up) * calc(mid) < 0 )
			down = mid;
		else if ( calc(down) * calc(mid) < 0 )
			up = mid;
		else
			break;
	}
	return down;
}

int main()
{
	std::ios::sync_with_stdio(false);
	int i;
	double res;
	while ( cin >> T && T )
	{
		memset( CF, 0, sizeof(CF) );
		for ( i = 0; i <= T; ++i )
			cin >> CF[i];
		res = solve( 100000., 0. );
		if ( res > 0 )
			cout << fixed << setprecision(2) << 1 / res - 1 << endl;
		else
			cout << "No\n";
	}
}
