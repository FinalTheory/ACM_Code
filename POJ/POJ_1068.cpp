/**
 * @file POJ_1068.cpp
 * @brief   这道题可以理解为一道模拟题，数据规模很小，一组最多20个数也就是说最多40个括号。
 * 个人感觉应该有一定规律可循，不过我们是搞编程的不是推公式的，
 * 所以就直接用模拟硬来了，反正数据规模不大。首先用输入的一组数据构造出对应的括号序列，
 * 由于题目说这是个良序的序列，所以构造方法很容易，直接按序插入即可。
 * 然后利用栈来找出每个右括号对应的左括号位置，记录下这些位置，
 * 然后枚举一遍数出这一对括号中间（包括右括号）有几个右括号，输出即可。
 * 一开始没有注意获取栈顶元素时要先检查栈是否为空，居然RE了4发才发现问题。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-07-16
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

#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

int num[1000];
int pos[1000];

struct TMD
{
	char c;
	int idx;
};

int main()
{
	//std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int t, n;
	vector<char> S;
	stack<TMD> stk;
	scanf("%d", &t);
	while ( t-- )
	{
		CLR(pos, -1);
		scanf("%d", &n);
		if ( n > 20 ) while (1);
		S.clear();
		while ( !stk.empty() ) stk.pop();
		for ( int i = 1; i <= n; ++i )
			scanf("%d", &num[i]);
		num[0] = 0;
		for ( int i = 1; i <= n; ++i )
		{
			int tmp1 = num[i] - num[i - 1];
			for ( int j = 0; j < tmp1; ++j )
				S.push_back('(');
			S.push_back(')');
		}
		int ans = 1;
		TMD tmp;
		tmp.c = S[0];
		tmp.idx = 0;
		stk.push( tmp );
 		for ( int i = 1; i < S.size(); ++i )
		{
			if ( !stk.empty() && stk.top().c == '(' && S[i] == ')' )
			{
				pos[i] = stk.top().idx;
				stk.pop();
			}
			else
			{
				tmp.c = S[i];
				tmp.idx = i;
				stk.push(tmp);
			}
		}
		bool outed = 0;
		for ( int i = 0; i < S.size(); ++i )
		{
			if ( pos[i] != -1 )
			{
				int sum = 0;
				for ( int j = pos[i]; j <= i; ++j )
					if ( S[j] == ')' )
						sum++;
				if ( !outed )
				{
					printf("%d", sum);
					outed = 1;
				}
				else
					printf(" %d", sum);
			}
		}
		printf("\n");
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
