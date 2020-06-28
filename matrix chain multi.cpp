/**
 * Usage matrix_chain_multi()
 * Matrix A[i] has dimension dims[i-1] x dims[i] for i = 1..n
 * cost[i, j] = Minimum number of scalar multiplications (i.e., cost)
 * needed to compute the matrix A[i]A[i+1]...A[j] = A[i..j]
 * The cost is zero when multiplying one matrix
 * split[i, j] = Index of the subsequence split that achieved minimal cost
 * dims is 0 based indexed, cost and split are 1 based indexed 
 * look out for n as per scenario
 */
int matrix_chain_multi(vector <int> &dim) {
	int n = dim.size() - 1;
	vector <vector <int> > cost(n + 1, vector <int> (n + 1));
	vector <vector <int> > split(n + 1, vector <int> (n + 1, -1));
	for (int len = 2; len <= n; ++len) {
		for (int i = 1; i <= n - len + 1; ++i) {
			int j = i + len - 1;
			cost[i][j] = INT_MAX;
			for (int k = i; k <= j - 1; ++k) {
				int new_cost = cost[i][k] + cost[k + 1][j] + 
								dim[i - 1] * dim[k] * dim[j];
				if (new_cost < cost[i][j]) {
					cost[i][j] = new_cost;
					split[i][j] = k
				} 
			}
		}
	}
	return cost[1][n];
}