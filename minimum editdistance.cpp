/**
 * Usage min_edit(a,b,in,rm,sb);
 * ci-insertion, cr=deletion, cs-substition
 */
int cr,ci,cs;
int conv_atob(vector <int> &a, vector <int> &b) {
	vector <vector<int> > min_dp(MAX, vector <int> (MAX, -1));
	for (int i = 0; i <= a.size(); ++i) {
		for (int j = 0; j <= b.size(); ++j) {
			if (i==0)
				min_dp[i][j] = (j * ci);
			else if (j == 0)
				min_dp[i][j] = (i * cr);
			else if (a[i - 1] == b[j - 1])
				min_dp[i][j] = min_dp[i - 1][j - 1];
			else
				min_dp[i][j] = min(min_dp[i][j - 1] + ci, min(min_dp[i - 1][j] + cr, min_dp[i - 1][j - 1] + cs));
		}
	}
	return min_dp[a.size()][b.size()];
}
int min_edit(vector <int> &a, vector <int> &b, int ins = 1, int rmv = 1,int sub = 2) {
	ci = ins; cr = rmv; cs = sub;
	return min(conv_atob(a, b), conv_atob(b, a));
}
//---------------------------------------------------------
/**
 * Usage same as above just use for case resticted where 
 * cost cannot increase k
 */
int cr, ci, cs;
vector <int> mdpp,mdps;
int conv_atob(vector <int> &a, vector <int> &b, int k) {
	mdpp.assign(MAX,0);
	mdps.assign(MAX,0);
	int n = a.size(), m = b.size();
	if (ci == 0 && cr == 0)
		return 0;
	if (n < m) {
		if ((m - n) > k / ci)
		return -1;
	}
	if (m < n) {
		if((n - m) > k / cr)
		return -1;
	}
	for (int i = 1; i <= m; ++i)
		mdpp[i] = ci * i;
	for (int i = 1; i <= n; ++i ) {
		mdps[0] = ci * i;
		for(int j = max(1, i - k); j <= min(m, i + k); ++j) {
			if (a[i - 1] == b[j - 1])
				mdps[j] = mdpp[j - 1];
			else if (j == max(1, i - k))
				mdps[j] = min(mdpp[j - 1] + cs, mdpp[j] + cr);
			else if (j == min(m, i + k))
				mdps[j] = min(mdpp[j - 1] + cs, mdps[j - 1] + ci);
			else
				mdps[j] = min(mdpp[j - 1] + cs, min(mdpp[j] + cr, mdps[j - 1] + ci));
		}
		for(int j = max(1, i - k); j <= min(m, i + k); ++j)
			mdpp[j] = mdps[j];
		mdpp[0] = mdps[0];
	}
	return mdps[m] > k? -1: mdps[m];
}
int min_edit(vector <int> &a, vector <int> &b, int ins = 1, int rmv = 1, int sub = 2, int k=5*MAX) {
	ci = ins; cr = rmv; cs = sub;
	int pp = conv_atob(a, b, k);
	if (pp == -1)
		pp = 5 * MAX;
	int qq = conv_atob(b, a, k);
	if (qq == -1)
		qq = 5*MAX;
	if (pp == 5 * MAX && qq == 5 * MAX)
		return -1;
	else
		return min(pp, qq); 
}