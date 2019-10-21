//Usage Matrix_chain_multi()
//dim[i-1][i] has dimension of ith matrix
int match[MAX][MAX],dim[MAX],n;
int matrix_chain_multi(){
	int i,j,k,l;
	for(i=1;i<n;i++)
	match[i][i]=0;
	for(l=2;l<n;l++){
		for(i=1;i<n-l+1;i++){
			j=i+l-1;
			match[i][j]=INT_MAX;
			for(k=i;k<j;k++){
				match[i][j]=min(match[i][j], 
					match[i][k] + match[k+1][j] + 
					dim[i-1]*dim[k]*dim[j] );
			}
		}
	}
	return match[1][n-1];
}