/**
 * dp[id][ls][sm] id represents the number of digits
 * ls represents the less flag ls=1 means less
 *  sm will be terminating condition on count of particular digit
 * Usage write 3rd parameter of dp. then solve(z), will give count from 0 to z
 * intstantiate like int dp[MAX][2][];
 */
vector <vector <vector <int> > > dp;
vector <int> digi;

int call(int id, int ls, int sm) {
	// failure of count condition
	if (sm> ) 
		return 0;
	//reached end of all digits
	if (id == digi.size())
		return 1;
	// answer cached
	if (dp[id][ls][sm] != -1)
		return dp[id][ls][sm];
	int dans = 0;
	if (!ls) {
		for(int i = 0; i <= digi[id]; ++i)
			dans += call(id + 1, ls | (i < digi[id]), sm + (i > 0));
	}else {
		for(int i = 0; i <= 9; ++i)
			dans += call(id + 1, ls, sm + (i > 0));	
	}
	return dp[id][ls][sm] = dans;
}

int solve(int z) {
	digi.clear();
	int sm = 0;
	while (z) {
		digi.push_back(z % 10);
		z/= 10;
	}
	dp.assign(digi.size(), vector <vector <int> >(2, vector <int>(/*3rd dimension*/, -1)));
	reverse(digi.begin(), digi.end());
	return call(0, 0, 0);
}