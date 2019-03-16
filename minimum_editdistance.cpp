//Usage min_edit(a,b,in,rm,sb);
int cr,ci,cs,min_dp[MAX][MAX];
int conv_atob(string &a,string &b)
{
	int i,j;
	memset(min_dp,-1,sizeof(min_dp));
	for(i=0;i<=a.size();i++)
	{
		for(j=0;j<=b.size();j++)
		{
			if(i==0)
			min_dp[i][j]=(j*ci);
			else if(j==0)
			min_dp[i][j]=(i*cr);
			else if(a[i-1]==b[j-1])
			min_dp[i][j]=min_dp[i-1][j-1];
			else
			min_dp[i][j]=min(min_dp[i][j-1]+ci,min(min_dp[i-1][j]+cr,min_dp[i-1][j-1]+cs));
		}
	}
	return min_dp[a.size()][b.size()];
}
int min_edit(string &a,string &b, int ins=1, int rmv=1,int sub=2)
{
	ci=ins;
	cr=rmv;
	cs=sub;
	return min(conv_atob(a,b),conv_atob(b,a));
}