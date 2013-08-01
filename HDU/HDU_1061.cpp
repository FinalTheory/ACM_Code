/**
 * @file HDU_1061.cpp
 * @brief   看这么大的数据规模，显然是规律题。打表水过。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-07-31
 */
#include <iostream>
using namespace std;
int ans[50] = { 0, 1, 4, 7, 6, 5, 6, 3, 6, 9, 0, 1, 6, 3, 6, 5, 6, 7, 4, 9, 0 };
int main()
{
	unsigned long long N;
	int T;
	cin >> T;
	while ( T-- )
	{
		cin >> N;
		cout << ans[N % 20] << endl;
	}
}
