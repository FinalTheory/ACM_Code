#define MAX 200010
int Tree[MAX];

int find_root( int x )
{
	int root = x;
	while ( Tree[root] != root )
		root = Tree[root];
	int i = x, j;
	while ( i != root )
	{
		j = Tree[i];
		Tree[i] = root;
		i = j;
	}
	return root;
}
int find_root_2(int v){
    if(Tree[v]!=v)
        Tree[v]=find_root_2(Tree[v]);
    return Tree[v];
}

