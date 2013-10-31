/**
 * @file POJ_3273.cpp
 * @brief   ����˼��
 * @hint    ���ֵĵط��Ƚ��ƣ����������
 * @author FinalTheory
 * @version 0.1
 * @date 2013-10-27
 */
#if defined(__GNUC__)
#pragma GCC optimize ("O2")
#endif
#if defined(_MSC_VER)
#pragma comment(linker, "/STACK:36777216")
#endif
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <bitset>
#include <stack>
#include <queue>
#include <deque>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cctype>
#include <climits>
#include <ctime>
#define MAX 100010
#define CLR(arr,val) memset(arr,val,sizeof(arr))
using namespace std;
const int INF = 0x3f3f3f3f;
int nums[MAX];
int N, M;
//����һ������������鵱ǰ�����ֵ�Ƿ������������С�ڵ���M�������С�
//��������ɵĻ�����Ȼһ��Ҳ������M����ֻ��Ҫ�ٲ�ּ��ɡ�
//������������������жϵ�ǰֵ�Ƿ�Ϸ��ģ�ʵ�ֵ�˼����̰�ķ���
inline bool check( int val )
{
	int sum = 0, res = 1;
	for ( int i = 1; i <= N; ++i )
		if ( sum + nums[i] <= val )
			sum += nums[i];
		else
		{
			sum = nums[i];
			res++;
		}
	if ( res <= M )
		return true;
	else
		return false;
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
	while ( scanf("%d %d", &N, &M) != EOF )
	{
		int _max = 0, sum = 0;
		for ( int i = 1; i <= N; ++i )
		{
			scanf("%d", &nums[i]);
			sum += nums[i];
			if ( nums[i] > _max ) _max = nums[i];
		}
		//�������ɶ��ֱ߽�
		int low = _max, high = sum;
		while ( low < high )
		{
			int mid = ( low + high ) >> 1;
			//���mid�Ϸ����������Ǵ𰸣�������С�Ͻ絫�ǲ���һ
			if ( check(mid) ) {
				high = mid;
			} else {
			    //������Ϸ���˵��Ӧ�������½磬�������midֵ�������Ǵ�
				low = mid + 1;
			}
		}
		printf("%d\n", low);
	}
#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}

