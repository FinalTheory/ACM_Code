#define SIZE 1000
#define MAX(x, y) (x) > (y) ? (x) : (y)
#define MIN(x, y) (x) < (y) ? (x) : (y)
using namespace std;

void get_next( char * TAR, int * next, int len )
{
	int i, j;
	i = 0; next[0] = -1; j = -1;
	while ( i < len )
	{
		if ( j == -1 || TAR[i] == TAR[j] )
		{
			++i, ++j;
			next[i] = j;
		}
		else
			j = next[j];
	}
}

char * KMP( char * SRC, char * TAR )
{
	int i, j, len1, len2;
	len1 = strlen(SRC);
	len2 = strlen(TAR);
	int * next = (int *)calloc(len2, sizeof(int));
	get_next(TAR, next, len2);
	i = j = 0;
	while ( i < len1 && j < len2 )
		if ( j == -1 || TAR[j] == SRC[i] )
			++i, ++j;
		else
			j = next[j];
	if ( j == len2 )
		return SRC + i - len2;
	else
		return NULL;
}

int main()
{
	char str1[SIZE], str2[SIZE];
	cin >> str1 >> str2;
	char * p = KMP(str1, str2);
}
