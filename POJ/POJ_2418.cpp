/*
	���������������ᣬ��������C++ STL�����map��
	ע��map��ʹ�÷�������֪����printf����Ļ��᲻���һЩ��
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