/*
	直接BFS，不出意外MLE，不剪枝无节操无节制地使用new的必然结果。
	为了先看到AC，保存了输出直接打表，第一次用这么猥琐的手段。
	不过即便如此还是鄙视网上那些直接用unsigned long long存m的，太TMD猥琐了，过了只是因为数据弱！
	最后还是copy的别人的剪枝，用到了一个性质：如果某个余数出现过，就不再对它生成下一个节点。
	原理和数论有关，暂时没想明白。
	另外还有一个同余模定理，可以用前一步操作的余数来代替当前操作的值，大大优化复杂度，0MS就是这么过的。
	最后，这里写了一个大数的模板，是大数除以小数的，算是自己的一个成果吧。
*/
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <climits>
#include <time.h>
#define MAX(x, y) (x) > (y) ? (x) : (y)
#define MIN(x, y) (x) < (y) ? (x) : (y)
#define BIG 100000
using namespace std;
char * nums[BIG];
char flags[BIG];
char * nums_bak[BIG];
char remains[1000];
int div( char * num, int n, char * num_res )
{
	int len = strlen(num), i, j, remain = 0;
	for ( i = 0, j = 0; i < len; i++, j++ )
	{
		remain *= 10;
		remain += num[i] - 48;
		num_res[j] = remain / n;
		remain -= num_res[j] * n;
		num_res[j] += 48;
	}
	num_res[j] = 0;
	return remain;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int n, N, N_bak, i, j, num_len, k;

	char found, res[101];
	while ( cin >> n && n )
	{
		num_len = 3;
		memset(nums, NULL, sizeof(nums));
		memset(remains, 0, sizeof(remains));
		memset(nums_bak, NULL, sizeof(nums_bak));
		nums[0] = new char [num_len];
		nums[1] = new char [num_len];
		strcpy(nums[0], "10");
		strcpy(nums[1], "11");
		N = 2;
		found = 0;
		while ( !found )
		{
			//先检测当前的所有节点是否满足
			num_len++;
			N_bak = N;
			N = 0;
			for ( i = 0; i < N_bak; i++ )
			{
				nums_bak[i] = nums[i];
				k = div( nums[i], n, res );
				if ( remains[k] )
					flags[i] = 0;
				else
					remains[k] = 1;
				if ( !k )
				{
					cout << nums[i] << endl;
					found = 1;
					goto end;
				}
			}
			//然后构造下一层节点。(只有某个节点的余数没有出现过时才构造。)
			for ( i = 0; i < N_bak; i++ )
				for ( j = 48; j <= 49; j++ )
					if ( flags[i] )
					{
						nums[N] = new char [num_len];
						strcpy(nums[N], nums_bak[i]);
						nums[N][num_len - 2] = j;
						nums[N++][num_len - 1] = 0;
					}
end:
			memset(flags, 1, sizeof(flags));
		}
		delete [] nums[0];
		delete [] nums[1];
	}
#ifndef ONLINE_JUDGE
	program_end = clock();
	cout << ( program_end - program_start ) << " MS" << endl;
#endif
}