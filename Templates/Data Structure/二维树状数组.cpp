/**
 * @file POJ_1195.cpp
 * @brief   二维树状数组模版
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-09
 */
#define MAX 1100
int Mat[MAX][MAX];
inline int Lowbit( int x )
{
	return x & (-x);
}
int S;
//更新点Mat[x][y]的值
void Add( int x, int y, int num )
{
	for ( int i = x ; i <= S; i += Lowbit(i) )
		for ( int j = y ; j <= S; j += Lowbit(j) )
			Mat[i][j] += num;
}
//查询区间Mat[1~x][1~y]的和
long long Query( int x, int y )
{
	long long res = 0;
	for ( int i = x ; i > 0; i -= Lowbit(i) )
		for ( int j = y ; j > 0; j -= Lowbit(j) )
			res += Mat[i][j];
	return res;
}
