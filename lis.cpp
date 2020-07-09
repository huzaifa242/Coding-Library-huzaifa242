/**
 * Usage lis();
 * a has to be 1 based index
 * number of elements in longest increasing subsequence = total number of different non-increasing subsequence 
 * number of elements in longest decreasing subsequence = total number of different non-decreasing subsequence 
 * above two facts are used vice-versa
 */
int lis(vector <int> &a) {
	int inf = 2e9, n = a.size() - 1;
	vector <int> a, ls, ind, par, seq;
	//change initialization of ls
	//for non/- incresing/decreasing seq
	ls.assign(n + 1, inf);
	ind.assign(n + 1, 0);
	par.assign(n + 1, 0);
	ls[0] = -inf;
	int i,ans = 1;
	for (i = 1; i <= n; ++i) {
		int l = 1, r = n, pos;
		while (l <= r) {
			int m = (l + r) / 2;
			//change below for all modification
			//of non/- incresing/decreasing seq
			if (ls[m] > a[i]) {
				pos = m;
				r = m - 1;
			} else
				l = m + 1;
		}
		//change below for all modification
		//of non/- incresing/decreasing seq
		if (ls[pos - 1] < a[i] && a[i] < ls[pos]) {
			ls[pos] = a[i];
			ind[pos] = i;
			par[i] = ind[pos - 1];
			ans = max(ans, pos);
		}
	}
	if (ans == 1) {
		seq.push_back(a[1]);
		return 1;
	}
	i = ind[ans];
	while (i) {
		seq.push_back(a[i]);
		i = par[i];
	}
	reverse(seq.begin(), seq.end());
	return ans;
}