/*
���SB�⣬TMDһ��ʼ��while������˸��ֺţ������ύ����ô���û��AC��������ܳ��
*/
#include <stdio.h>
void main()
{
	int y,m,d,o;
	//freopen("123.txt","r",stdin);
	while(scanf("%d/%d/%d",&y,&m,&d)!=EOF)
	{
		o=0;
		switch(m)
		{
		case 12:o+=30;
		case 11:o+=31;
		case 10:o+=30;
		case 9:o+=31;
		case 8:o+=31;
		case 7:o+=30;
		case 6:o+=31;
		case 5:o+=30;
		case 4:o+=31;
		case 3:o+=(y%4==0&&y%100!=0||y%400==0)?29:28;
		case 2:o+=31;
		}
		printf("%d\n",o+d);
	}
}