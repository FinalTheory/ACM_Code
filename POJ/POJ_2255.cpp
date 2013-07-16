/**
 * @file POJ_2255.cpp
 * @brief   白书上的数据结构入门题，非常漂亮的递归写法。具体见代码注释。
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

void DFS( int n, char * preorder, char * inorder, char * postorder )
{
	if ( n <= 0 ) return;
	//先序遍历结果的第一个元素是根节点。
	//首先在中序遍历的结果中找到根节点；
	//由此，中序遍历中根节点左边的元素即为左子树的元素，根节点右边的元素即为右子树的元素；
	int p = strchr( inorder, preorder[0] ) - inorder;
	//p表示左子树中的元素个数，而n - p - 1表示右子树中的元素个数；
	//在先序遍历中，preorder + 1是左子树的起始元素位置，而preorder + p + 1是右子树的起始位置；
	//在中序遍历中，左子树的起始位置还是inorder，但是右子树的起始位置则是inorder + p + 1，中间间隔了一个根节点；
	//在后续遍历中，前p个元素是左子树的，后面的n - p - 1个则是右子树的，而最后一个元素是根节点。
	DFS( p, preorder + 1, inorder, postorder );
	DFS( n - p - 1, preorder + p + 1, inorder + p + 1, postorder + p );
	//这样递归处理下去，并在最后将根节点的元素（先序遍历第一个）添加到后续遍历的结果中去，显然应该放在最后一个位置。
	postorder[n - 1] = preorder[0];
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
	char preorder[30], inorder[30], postorder[30];
	while ( scanf("%s %s", preorder, inorder) != EOF )
	{
		CLR(postorder, 0);
		int n = strlen(preorder);
		DFS( n, preorder, inorder, postorder );
		printf("%s\n", postorder);
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
