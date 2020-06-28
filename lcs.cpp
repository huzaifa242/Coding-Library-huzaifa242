/**
 * Usage pre_lcs(a,b);
 * lcs has the required string 
 */
vector <vector <int> > lcs_dp;
vector <int> lcs;
void pre_lcs(vector<int> &a, vector<int> &b) {
	int i,j,l;
	lcs_dp.assign(a.size() + 1, vector <int>(b.size() + 1, 0));
	for (i = 0; i <= a.size(); ++i) {
		for (j = 0; j <= b.size(); ++j) {
			if (i == 0 || j == 0)
				lcs_dp[i][j] = 0;
			else if (a[i - 1] == b[j - 1])
				lcs_dp[i][j] = lcs_dp[i - 1][j - 1] + 1;
			else
				lcs_dp[i][j]=max(lcs_dp[i - 1][j], lcs_dp[i][j - 1]);
		}
	}
	l = lcs_dp[a.size()][b.size()];
	lcs.resize(l, -1);
	i = a.size();
	j = b.size();
	while (i > 0 && j > 0) {
		if (a[i - 1] == b[j - 1]) {
			lcs[l - 1] = a[i - 1];
			i--;j--;l--;
		}
		else if (lcs_dp[i - 1][j] > lcs_dp[i][j - 1])
			i--;
		else
			j--;
	}
}
