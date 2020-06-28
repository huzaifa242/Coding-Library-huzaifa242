/**
 * Smallest Cost Hamiltonian Path
 * for Hamiltonian Cycyle
 * Base: dp[1][0]=0;
 * cst=min(cst,dp[(1<<n)-1][i]+cst[i][0])
 * prv=0 initilly not -1
 * Few More Application
 * ->Finding Number of Hamiltonian Path/Cycle
 * ->Check for existance of Hamiltonian Path/Cycle
 * ->Finding Number of Simple Path/Cycle
 * **for 3rd(Path)
 * sum for all mask,i where set bit in mask>=2 and divide sum by 2
 * **for 3rd(Cycle) [In applying Recurrence take note that LSB!=i]
 * sum for all mask,i where set bit in mask>=3 and divide sum by 2
 */
int cost[MAX][MAX], n;
int dp[1 << MAX][MAX];
int ord[MAX];
int hamiltonian(){
	int i, j, mask;
	memset(dp, INT_MAX,sizeof(dp));
	//Base
	for (i = 0; i < n; ++i)
		dp[1 << i][i]=0;
	for (mask = 1; mask < (1 << n); mask += 2) {
		for (i = 1; i < n; ++i) {
			if (mask & (1 << i)) {
				for (j = 0;j < n; ++j) {
					if (mask & (1 << j)) {
						//Recurrence
						dp[mask][i] = min(dp[mask][i], dp[mask ^ (1 << i)][j] + cost[j][i]);
					}
				}
			}
		}
	}
	//Result
	mask = (1 << n) - 1;
	int cst = INT_MAX;
	for(i = 1;i < n; ++i)
		cst = min(cst, dp[mask][i]);
	//Reconstruct Order
	int prv = -1;
	for(i = n - 1; i >= 0; --i) {
		int tpr = -1;
		for(j = 0; j < n; ++j) {
			if ((mask & (1 << j)) && (tpr == -1) || 
				dp[mask][tpr] + (prv == -1? 0: cost[prv][old]) > 
				dp[mask][j] + (prv == -1? 0: cost[j][old]))
				tpr = j;
		}
		ord[i] = tpr;
		mask ^= (1 << tpr);
		old = tpr;
	}
	return cst;
}
