//Usage floydwarshall()
int dst[MAX][MAX]
void floydwarshall(){
	int i,j,k;
	for(k=1;k<=n;k++)
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++)
				dst[i][j]=min(dst[i][j],dst[i][k]+dst[k][j]);
}