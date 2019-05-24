//Usage floydwarshall()
int dst[MAX][MAX]
void floydwarshall()
{
	int i,j,k;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			for(k=1;k<=n;k++)
			{
				dst[i][j]=min(dst[i][j],dst[i][k]+dst[k][j]);
			}
		}
	}
}