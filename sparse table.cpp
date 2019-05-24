//Sparse Table
#define lgs 20
int sprs[MAX][lgs];
void build_sprs(int n)
{
	memset(sprs,-1,sizeof(sprs));
	int i,j;
	for(i=0;i<n;i++)
	sprs[i][0]=//initialize value;
	for(j=1;j<lgs;j++)
	{
		for(i=0;i<n;i++)
		{
			sprs[i][j]= min(sprs[i][j-1],sprs[i+(1<<(j-1))][j-1]);
			//always relation between sprs[i][j-1] and sprs[i+(1<<(j-1))][j-1]
		}
	}
}
int sprs_query(int l, int r)
{
	int i=log2(r-l+1),j;
	return min(sprs[l][i], sprs[r-(1<<i)+1][i]);//for O(1) relation use this
	//otherwise do log query using bits x=r-l+1
	long long sum = 0;
	for (j=lgs;j>=0;j--) 
	{
		if((1<<j)<=r-l+1) 
		{
			sum+=sprs[l][j];
			l+= (1<<j);
		}
	}
}