//Usage pre_lcs(a,b);
//lcs has the required string 
int lcs_dp[MAX][MAX];
string lcs;
void pre_lcs(string &a, string &b){
	int i,j,l;
	lcs="";
	for(i=0;i<=a.length();i++){
		for(j=0;j<=b.length();j++){
			if(i==0||j==0)
				lcs_dp[i][j]=0;
			else if(a[i-1]==b[j-1])
				lcs_dp[i][j]=lcs_dp[i-1][j-1]+1;
			else
				lcs_dp[i][j]=max(lcs_dp[i-1][j],lcs_dp[i][j-1]);
		}
	}
	l=lcs_dp[a.length()][b.length()];
	for(i=0;i<l;i++)
		lcs+=" ";
	i=a.length();j=b.length();
	while(i>0 && j>0){
		if(a[i-1]==b[j-1]){
			lcs[l-1]=a[i-1];
			i--;j--;l--;
		}
		else if(lcs_dp[i-1][j]>lcs_dp[i][j-1])
			i--;
		else
			j--;
	}
}
