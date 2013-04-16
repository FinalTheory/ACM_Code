#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <iostream>
using std::cout;
using std::endl;
int main()
{
	freopen("123.txt", "r", stdin);
	unsigned long long p1, m1;
	int b, i, len1, len2, t;
	char p[1001], m[12], c[1000];
	while ( 1 )
	{
		p1 = m1 = 0;
		scanf("%d", &b);
		if ( b == 0 ) break;
		scanf("%s %s", p, m);
		len1 = strlen(p);
		len2 = strlen(m);
		for ( i = 0; i < len2; i++ )
		{
			m1 *= b;
			m1 += m[i] - 48;
		}
		for ( i = 0; i < len1; i++ )
		{
			p1 *= b;
			p1 += p[i] - 48;
			if ( p1 >= m1 )
				p1 %= m1;
		}
		t=0;
		if(p1==0) cout<<"0"<<endl;
		else
		{  
			while(p1)
			{
				c[t++]=(p1%b)+48;
				p1/=b;   
			}
			for(i=t-1;i>=0;i--)
				cout<<c[i];
			cout<<endl;
		}
	}
	return 0;
}