/**
 * @file POJ_1151.cpp
 * @brief   �߶���ɨ�������š�
 * ������Ҫע��һЩtrick���������߶���β��롣������y������ɢ�������ֲ�����ӳ�䡣
 * ɨ���ߴ����ң�����ÿ��ɨ���ߵ�λ������һ��λ�õĲ���Ե�ǰ����������������ĳ��ȡ�
 * ���߶����Ĺ��ܾ�������ά��������ȡ�������߶�Cover��1���ұ����Cover��1��
 * ע��ÿ�����Ȳ���һ���߶Σ��ڲ���Ĺ����У��ݹ鷵��ʱ��PushUp���¸��׵�״̬��
 * �������֮����ڵ�ͱ����˳�����Ϣ��ֱ���þͿ����ˡ�
 * ����ÿ���߶��ǶԳƵģ�����PushUp���̲��ÿ���̫���ӣ�������ֽڵ��ֵΪ�����������
 * ֱ�Ӳ��뵽Ŀ��λ�ã�Ȼ�������ȥ�Ϳ��ԡ����ĳ���ڵ��CoverΪ����˵�����Ѿ������ǣ�����ֱ�Ӽ��㳤�ȣ�
 * ���Ϊ�㣬˵����û�б����ǣ���ʱ���������ڵ���Ҷ�ӣ��͸�ֵΪ�㣬�������Ҷ�ӣ�����ֵ��ȡ���������ˡ�
 * @author FinalTheory
 * @version 1.0
 * @date 2013-05-13
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
#include <set>
#include <stack>
#include <sstream>
#include <iomanip>
#define L_son root << 1
#define R_son root << 1 | 1
#define MAX 210
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;
struct NND
{
	int L, R, Cover;
	double calc;
} Tree[MAX<<2];
struct TMD
{
	double high, low, x;
	int flag;
} lines[MAX];
double buffer[MAX];
double height[MAX];
void CreateTree( int root, int L, int R )  
{  
	Tree[root].L = L;
	Tree[root].R = R;
	Tree[root].Cover = 0;
	Tree[root].calc = 0.;
	if (L == R) return;
	int M = ( L + R ) >> 1;
	CreateTree( L_son, L, M );
	CreateTree( R_son, M + 1, R );
}
bool fuck( TMD & A, TMD & B )
{
	return A.x < B.x;
}

int BinSearch( double Key, int low, int high )
{
	int mid;
	while ( high >= low )
	{
		mid = ( high + low ) >> 1;
		if ( height[mid] == Key )
			return mid;
		else if ( height[mid] > Key )
			high = mid - 1;
		else
			low = mid + 1;
	}
	return 0;
}

void PushUp( int root )
{
	if ( Tree[root].Cover )
		Tree[root].calc = height[Tree[root].R + 1] - height[Tree[root].L];
	else if ( Tree[root].L == Tree[root].R )
		Tree[root].calc = 0.;
	else
		Tree[root].calc = Tree[L_son].calc + Tree[R_son].calc;
}

void Insert( int root, int L, int R, int flag )
{
	if ( Tree[root].L == L && Tree[root].R == R )
	{
		Tree[root].Cover += flag;
		PushUp(root);
		return;
	}
	int M = ( Tree[root].L + Tree[root].R ) / 2;
	if ( R <= M )
	{
		Insert( L_son, L, R, flag );
	}
	else if ( L > M )
	{
		Insert( R_son, L, R, flag );
	}
	else
	{
		Insert( L_son, L, M, flag );
		Insert( R_son, M + 1, R, flag );
	}
	PushUp(root);
}

int main()
{
	std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int n, i, p_lines, p_buffer, p_height, j, index = 1;
	double x1, y1, x2, y2, sum;
	while ( scanf( "%d", &n ) && n )
	{
		sum = 0.;
		p_lines = p_buffer = p_height = 0;
		for ( i = 0; i < n; ++i )
		{
			scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
			buffer[p_buffer++] = y1;
			buffer[p_buffer++] = y2;
			lines[p_lines].high = y1;
			lines[p_lines].low = y2;
			lines[p_lines].x = x1;
			lines[p_lines++].flag = 1;
			lines[p_lines].high = y1;
			lines[p_lines].low = y2;
			lines[p_lines].x = x2;
			lines[p_lines++].flag = -1;
		}
		sort( buffer, buffer + p_buffer );
		sort( lines, lines + p_lines, fuck );
		height[1] = buffer[0];
		double prev = buffer[0];
		for ( i = 1, j = 2; i < p_buffer; ++i )
		{
			if ( buffer[i] != prev )
				height[j++] = buffer[i];
			prev = buffer[i];
		}
		int num_points = j - 1;
		CreateTree( 1, 1, num_points - 1 );
		//���߶δ����Ҳ���
		for ( i = 0; i < p_lines - 1; ++i )
		{
			//ȷ�����Ҷ˵㿪ʼ����
			int left = BinSearch( lines[i].high, 1, num_points );
			int right = BinSearch( lines[i].low, 1, num_points ) - 1;
			Insert( 1, left, right, lines[i].flag );
			//�������
			sum += (lines[i + 1].x - lines[i].x) * Tree[1].calc;
		}
		printf("Test case #%d\nTotal explored area: %.2lf\n\n", index, sum);
		index++;
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
