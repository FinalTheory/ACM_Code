/*
	二叉排序树，不会，所以用了C++ STL里面的map。
	注意map的使用方法，不知道用printf输出的话会不会快一些。
*/

#include<map>  
#include<string>  
#include<iostream>
#include<iomanip>
using namespace std;
int main()   
{   
	char t[31];
	int i , j = 0, sum = 0;
	map<string,int>  trees;
	map<string,int>::iterator it;
	//freopen("123.txt", "r", stdin);
	while ( gets(t) != NULL )
	{
		sum++;
		it = trees.find(t);
		if ( it == trees.end() )
			trees[t] = 1; 
		else
			trees[t]++;
	}
	cout << setprecision(4) << fixed;
	for(it=trees.begin();it!=trees.end();++it)
		cout<<it->first <<' '<<it->second * 100 / (double)sum<<endl;
	return 0;
}