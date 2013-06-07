/**
 * @file POJ_1039.cpp
 * @brief   ���㼸����Ŀ��ö���������¶��㣬�ж��Ƿ�Ϸ����Լ��ɴ����Զ���롣
 * һЩ���ȿ����Լ���Ҫע��ĵط�д��ע�������д�����ˡ���
 * �Ƚ϶��ĵĵط�����������ж�һ��ֱ���ǲ��ǺϷ���ҪС������ֱ�Ӿͳ�����Χ�������
 * @author FinalTheory
 * @version 0.1
 * @date 2013-06-05
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
#include <vector>
#include <sstream>
#include <iomanip>
#define MAX 30
#define eps 0.0000001
#define INF 10000000000.
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;
int n;
struct TMD
{
	double x, y;
} Up[MAX], Down[MAX];

//�ж�����ȷ����ֱ���Ƿ��ָ����������ɵ��߶�
bool legal( TMD A, TMD B, TMD Up_bound, TMD Down_bound )
{
	double k = ( A.y - B.y ) / ( A.x - B.x );
	double b = A.y - k * A.x;
	double res = k * Up_bound.x + b;
	if ( res >= Down_bound.y - eps && Up_bound.y + eps >= res )
		return true;
	return false;
}

bool cross;

double get_pos( TMD A, TMD B, TMD C, TMD D )
{
	double k1 = ( A.y - B.y ) / ( A.x - B.x );
	double k2 = ( C.y - D.y ) / ( C.x - D.x );
	double b1 = A.y - k1 * A.x;
	double b2 = C.y - k2 * C.x;
	//���ֱ��ƽ�У���ֱ����Ϊû���ཻ
	if ( fabs( k1 - k2 ) < eps )
	{
		cross = false;
		return INF;
	}
	//�����������ĺ����꣬�ж��Ƿ������߶����˵㷶Χ��
	//����ע����Ҫ�ʵ���Сˮƽ��Χ�������������û���ཻ�ı�����ཻ��
	double x = ( b2 - b1 ) / ( k1 - k2 );
	if ( x >= C.x + eps && D.x - eps >= x )
	{
		cross = true;
		return x;
	}
	else
	{
		cross = false;
		return INF;
	}
}

double calc( TMD Up_point, TMD Down_point )
{
	int i;
	bool up_cross = false, down_cross = false, fail = false;
	double x_pos1, x_pos2;
	for ( i = 0; i < n - 1; ++i )
	{
		x_pos1 = get_pos( Up_point, Down_point, Up[i], Up[i + 1] );
		up_cross = cross;
		x_pos2 = get_pos( Up_point, Down_point, Down[i], Down[i + 1] );
		down_cross = cross;
		if ( up_cross || down_cross )
			break;
		if ( !legal( Up_point, Down_point, Up[i + 1], Down[i + 1] ) )
		{
			fail = true;
			break;
		}

	}
	if ( up_cross && down_cross )
		return max( x_pos1, x_pos2 );
	else if ( !down_cross && up_cross )
		return x_pos1;
	else if ( down_cross && !up_cross )
		return x_pos2;
	//���û�����κ����±��ཻ���п�����ֱ�ӾͲ��Ϸ���Ҳ�п�����ȫ��ͨ���ˡ�
	else
	{
		if ( fail )
			return Up[0].x;
		else
			return Up[n - 1].x;
	}

}

int main()
{
	//std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int i, j;
	double _max;
	while ( scanf("%d", &n) && n )
	{
		for ( i = 0; i < n; ++i )
		{
			scanf("%lf %lf", &Up[i].x, &Up[i].y);
			Down[i].x = Up[i].x;
			Down[i].y = Up[i].y - 1.;
		}
		_max = Up[0].x;
		for ( i = 0; i < n - 1; ++i )
			for ( j = i + 1; j < n; ++j )
			{
				double tmp;
				if ( legal( Up[i], Down[j], Up[0], Down[0] ) )
				{
					tmp = calc( Up[i], Down[j] );
					if ( tmp > _max ) _max = tmp;
				}
				if ( legal( Up[j], Down[i], Up[0], Down[0] ) )
				{
					tmp = calc( Up[j], Down[i] );
					if ( tmp > _max ) _max = tmp;
				}
			}
		if ( fabs( _max - Up[n - 1].x ) < eps )
			printf("Through all the pipe.\n");
		else
			printf("%.2lf\n", _max);
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
