/*
	看懂题意就行，还是水爆了！
*/
#include <stdio.h>
int main()
{
	int Y, W, max;
	scanf("%d %d", &Y, &W);
	max = ( Y > W ) ? Y : W;
	switch (max)
	{
	case 1:
		printf("1/1\n");
		break;
	case 2:
		printf("5/6\n");
		break;
	case 3:
		printf("2/3\n");
		break;
	case 4:
		printf("1/2\n");
		break;
	case 5:
		printf("1/3\n");
		break;
	case 6:
		printf("1/6\n");
	}
	return 0;
}